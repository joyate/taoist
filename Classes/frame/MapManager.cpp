#include "MapManager.h"
#include "ai/MessageDispatcher.h"
#include "../GameDefine.h"
#include "../utility/Utility.h"
#include "../obj/Zombie.h"
#include "TriggerInstance.h"
#include "../data/LocalPlayer.h"
#include "../obj/Hero.h"
#include "../ext_action/CCShake.h"
#include "../ext_action/ScreenTint.h"
#include "../obj/Bullet.h"
#include "../component/GuideFilterMgr.h"


const char* BOUND_TAG = "bounds";
const char* ENEMY_TAG = "enemy";
const char* TRIGG_TAG = "trigger";
const char* HINTS_TAG = "hints";




MapManager::MapManager(void):
	m_stage_id(0),
	m_enemys_cnt(0),
	m_map_owner(nullptr),
	m_sel_grid_index(-1),
	m_hero(nullptr),
	m_elapse_time(0.0f),
	_custom_listener(nullptr)
{
}


MapManager::~MapManager(void)
{
	if (m_map_owner)
	{
		m_map_owner->release();
	}

	if (_custom_listener)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_custom_listener);
	}
}



Node* MapManager::init(int _stage_id)
{

	if (_stage_id <= 0)
	{
		CCLOG("scene id %d invalid",_stage_id);
		return nullptr;
	}

	std::string _tmx_file = StringUtils::format("battle_scene/test/bs_%d.tmx",_stage_id);

	m_map_owner = /*experimental::*/TMXTiledMap::create(_tmx_file);
	//
	m_map_owner->setAnchorPoint(Vec2::ZERO);
	m_map_owner->setPosition(Vec2::ZERO);


	// 添加2个辅助层，用于放置特效
	// 层的大小默认是窗口大小，但是我们地图是超屏的，所以设置地图大小
	auto back_effect_layer = Layer::create();
	back_effect_layer->setContentSize(m_map_owner->getContentSize());
	m_map_owner->addChild(back_effect_layer,BACK_EFFECT_LAYER_LVL,TAG_BACK_EFFECT_LAYER);

	// 
	auto front_effect_layer = LayerColor::create(Color4B(0,0,0,0));
	front_effect_layer->setContentSize(m_map_owner->getContentSize());
	m_map_owner->addChild(front_effect_layer,FRONT_EFFECT_LAYER_LVL,TAG_FRONT_EFFECT_LAYER);


	if (!_analyseMap())
	{
		CCLOG("tmx map format has errors");
		return nullptr;
	}

	if (!_initEnemy())
	{
		CCLOG("enemy init error");
		return nullptr;
	}


	// 英雄
	if (!_initHero())
	{
		CCLOG("hero init error");
		return nullptr;
	}

	//---
	//auto test = Sprite::create("role_test.png");
	//test->setAnchorPoint(Vec2::ZERO);
	//m_map_owner->addChild(test);

	// 注册重生自定义事件
	_custom_listener = Director::getInstance()->getEventDispatcher()->addCustomEventListener("reborth",
		[=](EventCustom* _ec)
		{
			auto _obj = (GameEntity*)_ec->getUserData();
			_obj->OnReborth();
			enterMap(_obj);
		}
	);



	m_map_owner->retain();
	return m_map_owner;
}




bool MapManager::_analyseMap()
{

	if (!m_map_owner)
	{
		CCLOG("no map owner");
		return false;
	}

	// 可选区范围
	Rect bound_rect;

	TMXObjectGroup* obj_group = m_map_owner->getObjectGroup(BOUND_TAG);
	if (obj_group)
	{
		ValueMap vm = obj_group->getObject("lb");
		assert(!vm.empty());
		
		Vec2  lt(vm["x"].asInt(),vm["y"].asInt());
		stGridIdx grid_lt = _transVec2RectIndex(lt);

		// bound 左上起点位置
		bound_rect.origin.x = grid_lt.x*GRID_BASE_LEN;
		bound_rect.origin.y = grid_lt.y*GRID_BASE_LEN;


		vm = obj_group->getObject("rt");
		assert(!vm.empty());

		Vec2  rb(vm["x"].asInt(),vm["y"].asInt());
		stGridIdx grid_rb = _transVec2RectIndex(rb);


#define OFFSET(x,y) \
	(x >= y ? x - y + 1 : y - x + 1)

		int x_num = OFFSET(grid_rb.x,grid_lt.x)/GRID_FIXED_WIDTH_NUM;
		int y_num = OFFSET(grid_rb.y,grid_lt.y)/GRID_FIXED_HEIGHT_NUM;
		
		CCLOG("fight map has %d x grids and %d y grids",x_num,y_num);

#ifdef _DEBUG
		int x_scrap = OFFSET(grid_rb.x,grid_lt.x)%GRID_FIXED_WIDTH_NUM;
		int y_scrap = OFFSET(grid_rb.y,grid_lt.y)%GRID_FIXED_HEIGHT_NUM;

		if (x_scrap != 0 || y_scrap != 0)
		{
			CCLOG("warning: fight map format");
		}
#endif

		bound_rect.size.width = OFFSET(grid_rb.x,grid_lt.x) * GRID_BASE_LEN;
		bound_rect.size.height = OFFSET(grid_rb.y,grid_lt.y) * GRID_BASE_LEN;


		// 计算，提取所有的可选择格子区域数据
		for (float offset_y = 0;offset_y < bound_rect.size.height; offset_y += GRID_HEIGHT_LEN)
		{
			for (float offset_x = 0;offset_x < bound_rect.size.width;offset_x += GRID_WIDTH_LEN)
			{

				sttGridInfo gi;

				gi._rect.origin.x = bound_rect.origin.x + offset_x;
				gi._rect.origin.y = bound_rect.origin.y + offset_y;
				gi._rect.size.width = GRID_WIDTH_LEN;
				gi._rect.size.height = GRID_HEIGHT_LEN;

				gi._sel_bg = Sprite::create("select_box.png");

				Vec2 temp_pos(gi._rect.origin);
				OBJ_FIXED_POS(temp_pos);
				gi._sel_bg->setPosition(temp_pos);
				m_map_owner->addChild(gi._sel_bg,TAG_SELECT_GRID_LAYER);
				gi._sel_bg->setVisible(false);

				m_act_rect.push_back(gi);
			}
		}
	}

	// 
	m_bound_rect = bound_rect;


	// 触发器
	obj_group = m_map_owner->getObjectGroup(TRIGG_TAG);
	if (obj_group)
	{
		
		auto vec_objs = obj_group->getObjects();
		int obj_size = vec_objs.size();

		for (int i = 0; i < obj_size; i++)
		{
			auto obj = vec_objs[i].asValueMap();

			tTriggerInfo ti;
			ti.ti_id = obj["tid"].asInt();
			ti.nTrigType = (tTriggerInfo::TRIG_METHOD_TYPE)obj["trig_type"].asInt();
			ti.m_rect.origin.x = obj["x"].asFloat();
			ti.m_rect.origin.y = obj["y"].asFloat();
			ti.m_rect.size.width = obj["width"].asFloat();
			ti.m_rect.size.height = obj["height"].asFloat();

			m_triggers.push_back(ti);
		}

	}



	// 提示信息
	obj_group = m_map_owner->getObjectGroup(HINTS_TAG);
	if (obj_group)
	{

		ValueMap vm = obj_group->getObject("data");
		assert(!vm.empty());

		m_hints.round_num = vm["round_num"].asInt();
		for (int i = 0; i < m_hints.round_num; i++)
		{		
			std::string roundinfo = StringUtils::format("round_%d_offset",i+1);
			m_hints.round_offset[i] = vm[roundinfo.c_str()].asFloat();
		}
	}


	return true;
}



bool MapManager::_initEnemy()
{
	if (m_act_rect.empty())
	{
		CCLOG("tmx map initialize failed");
		return false;
	}

	
	TMXObjectGroup* obj_group = m_map_owner->getObjectGroup(ENEMY_TAG);
	if (obj_group)
	{
		int obj_id = 1;

		__String *str = __String::createWithFormat("e%02d", obj_id);
		ValueMap vm = obj_group->getObject(str->getCString());
		do
		{
			if (vm.empty())
			{
				break;
			}

			Vec2 pos;
			pos.x = vm["x"].asFloat();
			pos.y = vm["y"].asFloat();
			pos.x += vm["width"].asInt()/2;
			pos.y += vm["height"].asInt()/2;
			

			Vec2 obj_pos = _fixedMonsterPos(pos);
			if (obj_pos.equals(Vec2::ZERO))
			{
				CCLOG("enemy plant a invalid pos");
				continue;
			}


			// 怪物数据
			GameDefine::tEnemyObj enemy_obj;
			enemy_obj.id = vm["id"].asInt();
			enemy_obj.offset = vm["offset"].asInt();
			enemy_obj.pos = obj_pos;
			enemy_obj.round = vm["round"].asInt();


			m_enemys_cnt++;
			enemy_iter _iter = m_enemys.find(enemy_obj.round);
			if (_iter != m_enemys.end())
			{
				_iter->second.push_back(enemy_obj);
			}
			else
			{
				m_enemys.insert(std::make_pair(enemy_obj.round,std::vector<GameDefine::tEnemyObj>()));
				m_enemys[enemy_obj.round].push_back(enemy_obj);
			}
			
			//Zombie* _zb = Zombie::create();
			//_zb->initObj(vm["id"].asInt());
			//_zb->setPosition(obj_pos);

			//obj_pos.x = 0;
			////_zb->setDest(obj_pos);

			//enterMap(_zb);

			//state_attr sa;
			//sa.mask = state_attr::SA_DEST_MASK;
			//sa.dest = obj_pos;

			//MessageDispatcher::Instance()->DispatchMsg(-1,_zb,_zb,M_RUN,(void*)&sa);


			obj_id++;
			str = __String::createWithFormat("e%02d", obj_id);
			vm = obj_group->getObject(str->getCString());

		}while(!vm.empty());

	}



#ifdef _CJ
	auto test_spr = Sprite::create("test.png");
	test_spr->setPosition(test_spr->getContentSize()/2);
	test_spr->setScale(0.5);
	m_map_owner->addChild(test_spr,66);

#endif



	return true;
}

int MapManager::getVec2Rect( const Vec2& _pos, bool bCheck /*= true*/)
{
	if (m_act_rect.empty())
	{
		CCLOG("warning active rect empty");
		return -1;
	}

	int i = 0;
	for(rect_iter _iter = m_act_rect.begin(); _iter != m_act_rect.end(); _iter++, i++)
	{
		if(_iter->_rect.containsPoint(_pos))
		{
			if(bCheck && m_act_rect[i]._obj_id != 0)
				return -2;
			
			return i;
		}
	}

	return -1;
}

void MapManager::ShowObjGrid( bool bShow /*= true*/ )
{
	if (m_act_rect.empty())
	{
		return;
	}

	for (rect_iter _iter = m_act_rect.begin(); _iter != m_act_rect.end();_iter++)
	{
		if(_iter->_sel_bg && !_iter->_obj_id)
		{
			_iter->_sel_bg->setVisible(bShow);
		}
	}

	// 停止action
	if (m_sel_grid_index != -1)
	{
		if (m_act_rect[m_sel_grid_index]._sel_bg)
		{
			m_act_rect[m_sel_grid_index]._sel_bg->stopAllActions();
			m_act_rect[m_sel_grid_index]._sel_bg->setOpacity(100);
		}
		m_sel_grid_index = -1;
	}
	
}

bool MapManager::activeSelectBg( int _pos )
{
	assert(_pos >= 0 && _pos < (int)m_act_rect.size());

	if (_pos < 0 && _pos >= (int)m_act_rect.size())
	{
		CCLOG("active select bg pos invalid");
		return false;
	}

	// 已经选择过
	if (m_sel_grid_index != -1 && m_sel_grid_index == _pos)
	{
		CCLOG("already select");
		return true;
	}

	// 停止之前action
	if (m_sel_grid_index != -1 && m_act_rect[m_sel_grid_index]._sel_bg)
	{
		auto action1 = FadeIn::create(1.0f);
		m_act_rect[m_sel_grid_index]._sel_bg->stopAllActions();
		m_act_rect[m_sel_grid_index]._sel_bg->runAction(action1);
	}

	// 记录一下当前选择索引
	m_sel_grid_index = _pos;
	if(m_act_rect[_pos]._sel_bg)
	{
		auto action1 = FadeOut::create(1.0f);
		auto action1Back = action1->reverse();

		m_act_rect[_pos]._sel_bg->runAction(RepeatForever::create(Sequence::create( action1, action1Back, nullptr)));
	}

	return true;
}



bool MapManager::putObjectInGrid( int _pos,Node* _obj )
{
	assert(_pos >= 0 && _pos < (int)m_act_rect.size());
	if (_pos < 0 || _pos >= (int)m_act_rect.size())
	{
		CCLOG("put object pos invalid");
		return false;
	}


	Vec2 obj_pos(m_act_rect[_pos]._rect.origin);

	OBJ_FIXED_POS(obj_pos);
	_obj->setPosition(obj_pos);

	enterMap(_obj);

	// 占位
	auto _ge = (GameEntity*)_obj;
	if (_ge->getSubType() & GameEntity::OT_SOLDIER)
	{
		m_act_rect[_pos]._obj_id = _ge->getID();
	}

	// 默认idle状态
	MessageDispatcher::Instance()->DispatchMsg(-1,(GameEntity*)_obj,(GameEntity*)_obj,M_IDLE,(void*)&obj_pos);

	return true;
}

void MapManager::enterMap( Node* _obj )
{
	if (!_obj)
	{
		CCLOG("obj of entering map is null");
		return;
	}

	if (!m_map_owner)
	{
		CCLOG("map null");
		return;
	}

	// 托管下
	GameEntity* _ge = (GameEntity*)_obj;


	// 根据y值，处理zorder
	Size winSize = Director::getInstance()->getWinSize();
	Vec2 obj_pos = _obj->getPosition();
	// 如果是子弹，y值需要调整
	if (_ge->getType() & GameEntity::OT_BULLET)
	{
		auto _owner_id = static_cast<Bullet*>(_ge)->getOwnerId();
		auto _owner = this->GetGameObject(_owner_id);
		// 由于人物本身在y上有偏移，同一轨道上的子弹，要盖住本轨道上的其他怪，
		// 但是又要被下面轨道的怪物给覆盖，所以，y值要调整，不能用自己的位置
		// 来调整z_order
		if (_owner)
		{
			obj_pos = _owner->getPosition() - Vec2(0,10);
		}
	}
	int _z_order = winSize.height - (int)obj_pos.y;
	m_map_owner->addChild(_obj,_z_order);
	
	
	if(_ge->getType() & GameEntity::OT_BULLET)
	{
		m_vec_bullets.push_back(_ge);
		_ge->setID(GameDefine::GD_BULLET_OBJ_ID_BEGIN + m_vec_bullets.size());
	}
	else if (_ge->getType() & GameEntity::OT_OFFENSIVE)
	{
		m_vec_monsters.push_back(_ge);
		_ge->setID(GameDefine::GD_MONSTER_OBJ_ID_BEGIN + m_vec_monsters.size());
	}
	else if (_ge->getType() & GameEntity::OT_DEFENDER )
	{
		m_vec_defenders.push_back(_ge);
		_ge->setID((int)m_vec_defenders.size());
	}
	
}



void MapManager::exitMap( GameEntity* _obj)
{
	if (!_obj)
	{
		CCLOG("exitMap obj nullptr");
		return;
	}

	// base 1;
	int id = _obj->getID() - 1;



	// 取消托管
	// todo 换个更好的方式
	if (id >= GameDefine::GD_BULLET_OBJ_ID_BEGIN)
	{
		int _new_id = id - GameDefine::GD_BULLET_OBJ_ID_BEGIN;
		m_vec_bullets[_new_id] = nullptr;

	}
	else if (id >= GameDefine::GD_MONSTER_OBJ_ID_BEGIN)
	{
		m_enemys_cnt--;
		CC_ASSERT(m_enemys_cnt >= 0);
		int _new_id = id - GameDefine::GD_MONSTER_OBJ_ID_BEGIN;
		m_vec_monsters[_new_id] = nullptr;

	}else if(_obj->getType() & GameEntity::OT_DEFENDER)
	{
		// 清理一下rect数据, Hero不在占位，
		if (_obj->getSubType() & GameEntity::OT_SOLDIER)
		{
			auto _def = (Defender*)m_vec_defenders[id];
			int pos = _def->getRectIndex();
			CC_ASSERT(pos >= 0 && pos < m_act_rect.size());
			CC_ASSERT(m_act_rect[pos]._obj_id == _def->getID());
			if (pos >= 0 && pos < (int)m_act_rect.size())
			{
				if(m_act_rect[pos]._obj_id == _def->getID())
				{
					m_act_rect[pos]._obj_id = 0;
				}
			}
		}
		m_vec_defenders[id] = nullptr;
	}

	// 离开了地图了
	_obj->stopAllActions();
	_obj->removeFromParent();
}




/*
 * 这里有效率问题，需要重新设计
 * 	
 */
void MapManager::update( float delta )
{


	// 出怪
	m_elapse_time += delta;
	if (!m_hints.isOver())
	{
		Size win_size = Director::getInstance()->getWinSize();

		if (m_hints.round_offset[m_hints.cur_round] <= m_elapse_time)
		{
			// 小兵选择引导
			GuideFilterMgr::getInstance().checkGuideFilter(GuideFilterMgr::GFN_BATTLE_SOLDIER_SELECT);

			auto msg_info = g_MsgInfoMgr.getObject(TIP_ENEMY_BOUND_MSG_ID);
			if (msg_info)
			{
				// 提示
				TTFConfig ttfConf;
				ttfConf.fontFilePath = "fzyh.ttf";
				ttfConf.fontSize = 36;
				auto hints = Label::createWithTTF(ttfConf,StringUtils::format(msg_info->msg,m_hints.cur_round+1));
				hints->setPosition(win_size.width/2,win_size.height/2);
				m_map_owner->getParent()->addChild(hints);
				//
				hints->runAction(Sequence::create(DelayTime::create(2.0f),CallFuncN::create( CC_CALLBACK_1(MapManager::hintCallback, this)),nullptr));
			}

			//
			m_hints.cur_round++;
		}

	}


	enemy_iter _iter = m_enemys.find(m_hints.cur_round);
	if (_iter != m_enemys.end())
	{
		int size = _iter->second.size();
		for (int i = 0; i < size; i++)
		{
			std::vector<tEnemyObj>& ene_obj = _iter->second;
			if(!ene_obj[i].bDone && ene_obj[i].offset <= m_elapse_time)
			{
				Zombie* _zb = Zombie::create();
				_zb->initCardId(ene_obj[i].id);
				_zb->setPosition(ene_obj[i].pos);


				// 进入地图
				enterMap(_zb);

				// 通知事件
				Vec2 dest = ene_obj[i].pos;
				dest.x = 0;

				state_attr sa;
				sa.mask = state_attr::SA_DEST_MASK;
				sa.dest = dest;

				MessageDispatcher::Instance()->DispatchMsg(-1,_zb,_zb,M_RUN,(void*)&sa);
				ene_obj[i].bDone = true;
			}
		}
	}


	// 更新英雄
	for (obj_iter _iter = m_vec_defenders.begin(); _iter != m_vec_defenders.end(); _iter++)
	{
		if(*_iter)
			(*_iter)->update(delta);
	}


	// 更新怪物
	for (obj_iter _mon_iter = m_vec_monsters.begin(); _mon_iter != m_vec_monsters.end(); _mon_iter++)
	{
		if(*_mon_iter)
			(*_mon_iter)->update(delta);
	}


	// 更新子弹
	for (obj_iter _bullet_iter = m_vec_bullets.begin(); _bullet_iter != m_vec_bullets.end(); _bullet_iter++)
	{
		if(*_bullet_iter)
			(*_bullet_iter)->update(delta);
	}



	for (trig_iter _tri_iter = m_triggers.begin(); _tri_iter != m_triggers.end(); _tri_iter++ )
	{
		auto trig_base = ObjectInstanceMgr<ITriggerBase>::getInstance()->getHandler(_tri_iter->ti_id);
		if (trig_base)
		{
			trig_base->update(*_tri_iter,delta);
		}
	}


	
}


GameEntity* MapManager::onTouch( Vec2 _pos,int& _op)
{
	Vec2 _ends = m_map_owner->convertToNodeSpace(_pos);
	
	GameEntity* _sel = GetGameObjectByPos(_ends);

	// 之前选择过
	if(m_hero)
	{
		int sel_index = getVec2Rect(_ends,false);
		if (sel_index != -1)
		{

			//
			GameDefine::state_attr sa;
			sa.mask = GameDefine::state_attr::SA_DEST_MASK;
			sa.dest = Vec2(m_act_rect[sel_index]._rect.origin);

			OBJ_FIXED_POS(sa.dest);

			MessageDispatcher::Instance()->DispatchMsg(-1,(GameEntity*)m_hero,(GameEntity*)m_hero,M_RUN,(void*)&sa);
			
		}
		m_hero = nullptr;
		ShowObjGrid(false);
		_op = OT_COMMON;
	}
	else
	{
		do 
		{
			if(_sel)
			{
				if(_sel->getType() & GameEntity::OT_HERO)
				{
					if(!m_hero)
					{
						m_hero = _sel;
						ShowObjGrid();
						_op = OT_HERO_MOVE;
						break;
					}
				}
			}
			_op = OT_COMMON;

		} while (false);
	
	}

	return _sel;
}


int MapManager::getLineNearestObjs( GameEntity* _me,std::vector<GameEntity*>* _out,const TargetSelectorFilter& _filter )
{
	if (!_me)
	{
		return 0;
	}

	Vec2 me_pos = _me->getPosition();
	int num = 0;

	if (_filter.select_mask & GameEntity::OT_OFFENSIVE)
	{
		for (obj_iter _iter = m_vec_monsters.begin(); _iter != m_vec_monsters.end(); _iter++)
		{

			if (!(*_iter) || !(*_iter)->isAlive())
			{
				continue;
			}

			//
			if (me_pos.x > (*_iter)->getBoundingBox().getMaxX())
			{
				continue;
			}

			bool bGot = false;
			Vec2 tar_pos = (*_iter)->getPosition();
			do
			{
				
				if (!isInLine(me_pos.y,tar_pos.y,_filter.bAdjustY))
				{
					break;
				}
				

				if (_filter.filter_dis > 0.0001)
				{
					bGot = abs(me_pos.x - tar_pos.x) < _filter.filter_dis;
				}
				else
				{
					bGot = Utility::intersectsRect(_me->getBoundingBox(),(*_iter)->getBoundingBox(),Utility::SR_SHRINK);
				}

			}while(false);


			if (bGot)
			{
				if(_out)
				{
					_out->push_back(*_iter);
				}

				num++;
				if (_filter.sel_num > 0 && num >= _filter.sel_num)
				{
					break;
				}
			}

		}
	}
	

	if(_filter.select_mask & GameEntity::OT_DEFENDER)
	{
		for (obj_iter _iter = m_vec_defenders.begin(); _iter != m_vec_defenders.end(); _iter++)
		{

			if (!(*_iter) || !(*_iter)->isAlive())
			{
				continue;
			}

			if (me_pos.x < (*_iter)->getBoundingBox().getMinX())
			{
				continue;
			}

			bool bGot = false;
			Vec2 tar_pos = (*_iter)->getPosition();
			do
			{
				if (!isInLine(me_pos.y,tar_pos.y,_filter.bAdjustY))
				{
					break;
				}

				if (_filter.filter_dis > 0.0001)
				{
					bGot = abs(me_pos.x - tar_pos.x) < _filter.filter_dis;
				}
				else
				{
					bGot = Utility::intersectsRect(_me->getBoundingBox(),(*_iter)->getBoundingBox(),Utility::SR_SHRINK);
				}

			}while(false);

			if (bGot)
			{
				if(_out)
				{
					_out->push_back(*_iter);
				}

				num++;
				if (_filter.sel_num > 0 && num >= _filter.sel_num)
				{
					break;
				}
			}
		}
	}

	return num;
}


int MapManager::getPosNearestObjs( const Vec2& pos, std::vector<GameEntity*>* _out,const TargetSelectorFilter& _filter )
{
	int num = 0;

	if (_filter.select_mask & GameEntity::OT_OFFENSIVE)
	{
		for (obj_iter _iter = m_vec_monsters.begin(); _iter != m_vec_monsters.end(); _iter++)
		{

			if (!(*_iter) || !(*_iter)->isAlive())
			{
				continue;
			}

			bool bGot = false;

			CC_ASSERT(_filter.filter_dis > GameDefine::MIN_FLOAT_VALUE);
			Vec2 tar_pos = (*_iter)->getPosition();
			if(tar_pos.distance(pos) < _filter.filter_dis)
			{
				bGot = true;
			}


			if (bGot)
			{
				if(_out)
				{
					_out->push_back(*_iter);
				}

				num++;
				if (num >= _filter.sel_num)
				{
					break;
				}
			}
		}
	}


	if(_filter.select_mask & GameEntity::OT_DEFENDER)
	{
		for (obj_iter _iter = m_vec_defenders.begin(); _iter != m_vec_defenders.end(); _iter++)
		{

			if (!(*_iter) || !(*_iter)->isAlive())
			{
				continue;
			}


			bool bGot = false;
			CC_ASSERT(_filter.filter_dis > GameDefine::MIN_FLOAT_VALUE);
			Vec2 tar_pos = (*_iter)->getPosition();
			if(tar_pos.distance(pos) < _filter.filter_dis)
			{
				bGot = true;
			}

			if (bGot)
			{
				if(_out)
				{
					_out->push_back(*_iter);
				}

				num++;
				if (num >= _filter.sel_num)
				{
					break;
				}
			}
		}
	}

	return num;
}





GameEntity* MapManager::GetGameObject( int _id )
{
	if (_id > GameDefine::GD_BULLET_OBJ_ID_BEGIN)
	{
		int new_id = _id - GameDefine::GD_BULLET_OBJ_ID_BEGIN;
		assert(new_id <= (int)m_vec_bullets.size() && new_id > 0);

		if (new_id <= (int)m_vec_bullets.size() && new_id > 0)
		{
			return m_vec_bullets[new_id-1];
		}

		return nullptr;
	}
	else if (_id > GameDefine::GD_MONSTER_OBJ_ID_BEGIN)
	{
		int new_id = _id - GameDefine::GD_MONSTER_OBJ_ID_BEGIN;
		assert(new_id <= (int)m_vec_monsters.size() && new_id > 0);

		if (new_id <= (int)m_vec_monsters.size() && new_id > 0)
		{
			return m_vec_monsters[new_id-1];
		}

		return nullptr;
	}
	else
	{
		assert(_id <= (int)m_vec_defenders.size() && _id > 0);

		if(_id <= (int)m_vec_defenders.size() && _id > 0)
			return m_vec_defenders[_id-1];

		return nullptr;
	}

	return nullptr;
}




GameEntity* MapManager::GetGameObjectByPos( const Vec2& pos )
{
	for (auto _iter : m_vec_defenders)
	{
		if(_iter)
		{
			if(_iter->getBoundingBox().containsPoint(pos))
				return _iter;
		}
	}


	for (auto _iter : m_vec_monsters)
	{
		if(_iter)
		{
			if(_iter->getBoundingBox().containsPoint(pos))
				return _iter;
		}
	}

	return nullptr;
}




cocos2d::Vec2 MapManager::_fixedMonsterPos( const Vec2& _pos )
{
	// 转移为以lt点为基准
	Vec2 fixed_pos = _pos - m_bound_rect.origin;

	Size map_size = m_map_owner->getContentSize();
	if (_pos.x > map_size.width || _pos.y > map_size.height)
	{
		CCLOG("pos invalid");
		return Vec2::ZERO;
	}

	// 做一些规整，使其位置在格子正确的位置，0.2 * grid length 
	Vec2 ret_pos = Vec2( fixed_pos.x,
		(int)(fixed_pos.y / GRID_HEIGHT_LEN) * GRID_HEIGHT_LEN);

	ret_pos += m_bound_rect.origin;
	// 修正x坐标
	ret_pos.x = map_size.width;


	OBJ_FIXED_POS_Y(ret_pos);

	return ret_pos;
}

int MapManager::getObjsInRect( const Rect& _rect,std::vector<int>& _out )
{
	for (obj_iter _iter = m_vec_monsters.begin(); _iter != m_vec_monsters.end(); _iter++)
	{

		if (!(*_iter) || !(*_iter)->isAlive())
		{
			continue;
		}


		if (_rect.containsPoint((*_iter)->getPosition()))
		{
			_out.push_back((*_iter)->getID());
		}
	}

	return _out.size();
}

void MapManager::specialPause(int _id/*= BaseDefine::INVALID_ID*/)
{
	/*if(m_map_owner)
	m_map_owner->pause();*/
#ifndef ITERATOR_PAUSE_VECTOR
#define ITERATOR_PAUSE_VECTOR(_vector)											\
	do {																		\
		for (obj_iter _iter = _vector.begin(); _iter != _vector.end(); _iter++)	\
		{																		\
			if (!(*_iter) )														\
			{																	\
				continue;														\
			}																	\
			if (_id != BaseDefine::INVALID_ID && _id == (*_iter)->getID())		\
			{																	\
				continue;														\
			}																	\
			(*_iter)->pause();													\
		}																		\
	} while(false)


	ITERATOR_PAUSE_VECTOR(m_vec_monsters);
	ITERATOR_PAUSE_VECTOR(m_vec_defenders);
	ITERATOR_PAUSE_VECTOR(m_vec_bullets);
	
#endif
}

void MapManager::hintCallback( Node* sender )
{
	if (sender)
	{
		sender->removeFromParent();
	}
}




bool MapManager::_initHero()
{
	auto lp = LocalPlayer::getInstance();
	const auto tfi = lp->m_temp_fight_info;

	if (tfi.army_inst_id[GameDefine::tTempFightInfo::ARMY_HERO_INDEX] <= 0)
	{
		CCLOG("no hero");
		return false;
	}


	auto inst_item_info = lp->m_bag.getItemById(tfi.army_inst_id[GameDefine::tTempFightInfo::ARMY_HERO_INDEX]);
	if (!inst_item_info)
	{
		return false;
	}

	auto _hero = Hero::create();
	//
	_hero->initCardId(inst_item_info->item_temp_id);

	putObjectInGrid(20,_hero);

	return true;
}


GameEntity* MapManager::getHero()
{
	if(m_vec_defenders[0])
	{
		CC_ASSERT(m_vec_defenders[0]->getType() & GameEntity::OT_HERO);
		return m_vec_defenders[0];
	}
	return nullptr;
}



int MapManager::getActiveObjCount( int nObjType )
{
	int nCount = 0;
	if (nObjType == GameEntity::OT_OFFENSIVE)
	{
		nCount = m_enemys_cnt;
	}
	else if(nObjType == GameEntity::OT_DEFENDER)
	{

	}

	return nCount;
}




void MapManager::attachEffect( GameEntity* _owner,Node* _effect,int nLayer )
{
	if (!_owner || !_effect)
	{
		return;
	}


	auto layer = m_map_owner->getChildByTag(nLayer);
	if (!layer)
	{
		return;
	}

	_effect->setPosition(_owner->getPosition());
	layer->addChild(_effect);
}




void MapManager::shakeAffect( float _dt,float offset_x,float offset_y )
{
	auto shake = FallOffShake::createWithStrength(_dt,offset_x,offset_y);
	m_map_owner->runAction(shake);
}


void MapManager::specialResume()
{
#ifndef ITERATOR_RUSUME_VECTOR
#define ITERATOR_RUSUME_VECTOR(_vector)											\
	do {																		\
		for (obj_iter _iter = _vector.begin(); _iter != _vector.end(); _iter++)	\
		{																		\
			if (!(*_iter) )														\
			{																	\
				continue;														\
			}																	\
			(*_iter)->resume();													\
		}																		\
	} while(false)


	ITERATOR_RUSUME_VECTOR(m_vec_monsters);
	ITERATOR_RUSUME_VECTOR(m_vec_defenders);
	ITERATOR_RUSUME_VECTOR(m_vec_bullets);

#endif
}

void MapManager::screenTintAffect( float _dt,GLubyte opacity, GameEntity* _owner)
{
	auto front_eff_layer = m_map_owner->getChildByTag(TAG_FRONT_EFFECT_LAYER);
	if (front_eff_layer)
	{
		auto action = ScreenTint::create(_dt,opacity,_owner);
		front_eff_layer->runAction(action);
	}
}




int MapManager::getAllSummonObjs( GameEntity* _me,std::vector<GameEntity*>* _out,const TargetSelectorFilter& _filter )
{
	int nRetCnt = 0;
	if (!_me)
	{
		return nRetCnt;
	}

#ifndef ITERATOR_VECTOR_OBJS
#define ITERATOR_VECTOR_OBJS(_vec)											\
	do{																		\
		for(auto _def : _vec)												\
		{																	\
			if (_def && _def->getType() == _filter.select_mask)				\
			{																\
				if (_out)													\
				{															\
					_out->push_back(_def);									\
				}															\
				nRetCnt++;													\
				if (_filter.sel_num > 0 && nRetCnt >= _filter.sel_num)		\
				{															\
					break;													\
				}															\
			}																\
		}																	\
	}while(false)
	


	if (_me->getType() & GameEntity::OT_DEFENDER)
	{
		ITERATOR_VECTOR_OBJS(m_vec_defenders);
	}
	else if(_me->getType() & GameEntity::OT_OFFENSIVE)
	{
		ITERATOR_VECTOR_OBJS(m_vec_monsters);
	}
	
#endif

	return nRetCnt;
}




int MapManager::getRectInObjs( const Rect& _rect, std::vector<GameEntity*>* _out,const TargetSelectorFilter& _filter )
{
	int num = 0;
	if (_filter.select_mask & GameEntity::OT_OFFENSIVE)
	{
		for (obj_iter _iter = m_vec_monsters.begin(); _iter != m_vec_monsters.end(); _iter++)
		{

			if (!(*_iter) || !(*_iter)->isAlive())
			{
				continue;
			}

			//
			bool bGot = false;
			if (_rect.containsPoint((*_iter)->getPosition()))
			{
				bGot = true;
			}

			if (bGot)
			{
				if(_out)
				{
					_out->push_back(*_iter);
				}

				num++;
				if (num >= _filter.sel_num)
				{
					break;
				}
			}
		}
	}


	if(_filter.select_mask & GameEntity::OT_DEFENDER)
	{
		for (obj_iter _iter = m_vec_defenders.begin(); _iter != m_vec_defenders.end(); _iter++)
		{

			if (!(*_iter) || !(*_iter)->isAlive())
			{
				continue;
			}

			//
			bool bGot = false;
			if (_rect.containsPoint((*_iter)->getPosition()))
			{
				bGot = true;
			}

			if (bGot)
			{
				if(_out)
				{
					_out->push_back(*_iter);
				}

				num++;
				if (num >= _filter.sel_num)
				{
					break;
				}
			}
		}
	}

	return num;
}




