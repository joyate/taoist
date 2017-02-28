#include "GameEntity.h"
#include "cocostudio/CocoStudio.h"
#include <string>
#include "AIState.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "../data/GameData.h"

#include "../skill/ISkillExecBase.h"
#include "../skill/ITargetSelect.h"
#include "../skill/SkillInstance.h"
#include "../skill/SkillDamage.h"
#include "../skill/ObjectAction.h"

#include "../component/Effect.h"


using namespace cocostudio;




// 与AnimType对应
const char* ANIMATION_NAME_ARRAY[] = {
					nullptr,
					"idle",
					"idle2",
					"walk",
					"atk",
					"beatk",
					"dead",
					"born"
					};







GameEntity::GameEntity():
	m_id(0),
	m_target(nullptr),
	m_skillMgr(this),
	m_anger_val(0.0f),
	m_buffMgr(this)
	//_custom_event(nullptr)
{

	m_atk_speed = BaseDefine::BASE_ATK_SPEED;


	m_char_root = Node::create();
	m_char_root->retain();
	this->addChild(m_char_root);

	_stateMechine = new StateMachine<GameEntity>(this);
}


void GameEntity::playAnim( AnimType _at,int durationTo /*= -1*/,  int loop /*= -1*/ )
{
	int _size = sizeof(ANIMATION_NAME_ARRAY)/sizeof(ANIMATION_NAME_ARRAY[0]);

	if (_at > _size || _at < 0)
	{
		CCLOG("animation type invalid");
		return;
	}

	playAnim(ANIMATION_NAME_ARRAY[_at],durationTo,loop);
	
}

void GameEntity::playAnim( const char* act_name,int durationTo /*= -1*/, int loop /*= -1*/ )
{
	Node* _body = m_char_root->getChildByTag(TAG_GNT_BODY);
	if (!_body)
	{
		CCLOG("no body animation");
		return;
	}

	Armature* pAnim = static_cast<Armature*>(_body);
	pAnim->getAnimation()->play(act_name,durationTo,loop);
	pAnim->getAnimation()->setSpeedScale(m_atk_speed);

	// 设置回调
	pAnim->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(GameEntity::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	pAnim->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(GameEntity::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void GameEntity::stopAnim()
{
	if (m_char_root)
	{
		/*Node* pNode = m_char_root->getChildByTag(TAG_GNT_BODY);
		Armature* pAnim = dynamic_cast<Armature*>(pNode);*/

		m_char_root->stopAllActions();
	}

	this->stopAllActions();
}



void GameEntity::runTo( const Vec2& _dest )
{
	const Vec2 &curPos = getPosition();

	setDir(Vec2(_dest.x - curPos.x, _dest.y - curPos.y));
	GameDefine::Dir _new_dir = flipDir((GameDefine::Dir)getDir());

	if (m_e_dir != _new_dir)
	{
		Node* _body = m_char_root->getChildByTag(TAG_GNT_BODY);
		if (_body)
		{
			float scale_x = _body->getScaleX() * -1;
			_body->setScaleX(scale_x);
		}

		m_e_dir = _new_dir;
	}
}



bool GameEntity::changeState( unsigned int mask, const Telegram& telegram )
{
	switch(telegram.Msg)
	{
	case M_RUN:
		{
			
			return true;
		}
	case M_IDLE:
		{	
			
			return true;
		}
	case M_ATK:
		{
			//assert(telegram.ExtraInfo != NULL);
			//GameDefine::state_attr* info = (GameDefine::state_attr *)(telegram.ExtraInfo);
			
			return true;
		}
	case M_DEAD:
		{
			// 
			_stateMechine->ChangeState(ObjDeadState::getInstance());
			return true;
		}

	case M_BEATK:
		{
			_stateMechine->ChangeState(ObjBeAttackState::getInstance());
			return true;
		}
	default:
		CC_ASSERT(false && "invalid msg type");
		return false;
	}

	return true;
}

bool GameEntity::HandleMessage( const Telegram& msg )
{
	if(_stateMechine == NULL)
		return false;

	return _stateMechine->HandleMessage(msg);
}



//void GameEntity::idleCallback()
//{
//	CC_ASSERT(_stateMechine != NULL);
//
//	//Vec2 pos = getPosition();
//	//MessageDispatcher::Instance()->DispatchMsg(-1, this, this, M_IDLE, &pos);
//}



Rect GameEntity::getBoundingBox() const
{
	auto ani = m_char_root->getChildByTag(TAG_GNT_BODY);
	if (ani)
	{
		Rect rect = ani->getBoundingBox();
		rect = RectApplyTransform(rect,getNodeToParentTransform());
		return rect;
	}

	return Rect::ZERO;
}




void GameEntity::update( float delta )
{
	// 状态机刷新
	if (_stateMechine)
	{
		_stateMechine->Update(delta);
	}



	// 更新血
	if (memcmp(&m_attr,&m_attr_copy,sizeof(GameDefine::stGameEntityAttr)) != 0)
	{
		if (m_attr.m_hp != m_attr_copy.m_hp)
		{
			auto blood = (ProgressTimer*)m_char_root->getChildByTag(TAG_GNT_BLOOD_FG);
			if (blood)
			{
				float per = (float)m_attr.m_hp/m_attr.m_hp_max;
				per *= BaseDefine::HUNDRED_BASE;
				blood->setPercentage(per);
			}
			
		}

		m_attr_copy = m_attr;
	}


	// 血条的更新，树精出来的时候，血条位置是不对的,
	// 动态的血也不符合现实
	/*{
	auto blood = m_char_root->getChildByTag(TAG_GNT_BLOOD_FG);
	if (blood)
	{
	auto new_y = this->getBoundingBox().size.height;
	auto bd_pos = blood->getPosition();
	auto y_dis = new_y - bd_pos.y;
	auto abs_y_dis = MAX(-y_dis,y_dis);

	if (abs_y_dis > 5)
	{
	auto blood_bg = m_char_root->getChildByTag(TAG_GNT_BLOOD_BG);
	blood_bg->setPosition(Vec2(bd_pos.x,new_y));
	blood->setPosition(Vec2(bd_pos.x,new_y));
	}
	}
	}*/
	
	



	// buff 状态更新
	m_buffMgr.update(delta);
	
}

void GameEntity::onFrameEvent( cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex )
{
	//
	if (evt == "hit")
	{
		auto cur_skill = GetCurSkill();
		if (cur_skill)
		{
			// 看有没有特殊效果
			cur_skill->touchAffect(GameDefine::SAM_SHAKE);

			// 执行伤害计算
			auto skill_info = g_SkillInfoMgr.getObject(cur_skill->getID());
			if (skill_info)
			{
				auto sk_exec = ObjectInstanceMgr<ISkillExecBase>::getInstance()->getHandler(skill_info->sk_exec_type);
				if (sk_exec)
				{
					sk_exec->onExec(this,cur_skill);
				}
			}

		}

		cleanSkill();
	}
	else if(!evt.compare(0,3,"eff"))
	{
		auto eff = Effect::create();
		eff->createEffect(this);

		if (eff->attachGameObj(this,evt))
		{
			eff->playEffect(evt.c_str());
		}
	}
}



void GameEntity::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType == LOOP_COMPLETE || movementType == COMPLETE)
	{
		if (movementID == "atk" || !movementID.compare(0,4,"conj"))	// 攻击动作结束
		{

			//
			if (getType() & OT_OFFENSIVE)
			{
				auto cur_skill = GetCurSkill();
				if (cur_skill)
				{

					auto skill_info = g_SkillInfoMgr.getObject(cur_skill->getID());
					if (skill_info)
					{
						auto sk_exec = ObjectInstanceMgr<ISkillExecBase>::getInstance()->getHandler(skill_info->sk_exec_type);
						if (sk_exec)
						{
							sk_exec->onExec(this,cur_skill);
						}
					}

				}
				cleanSkill();
			}
	
			// 打完，idle状态
			MessageDispatcher::Instance()->DispatchMsg(-1,this,this,M_IDLE,nullptr);

		}
		else if (movementID == "dead")	// 死亡结束
		{
			onDeadEvent();
		}
		else if(movementID == "idle2" ||	// 休闲动作
			movementID == "born" ||		// 出现
			movementID == "beatk")			// 被击
		{
			revertPreState();
		}
		
		
	}
}


void GameEntity::bloodFlyCallback( Node* sender )
{
	if(sender)
		sender->removeFromParent();
}



void GameEntity::decreaseHp( int _hp )
{
	// 减血
	if (_hp > 0)
	{
		m_attr.m_hp = (m_attr.m_hp < _hp ? 0 : m_attr.m_hp - _hp);
		m_anger_val += _hp;
	}
	else // 加血
	{
		m_attr.m_hp = (m_attr.m_hp - _hp)%m_attr.m_hp_max;
	}

	if (m_attr.m_hp <= 0)
	{
		onDead();
	}
}

void GameEntity::onDead()
{
	// 做一些处理

	// 如果是动画速度为0的话，后面的动作没法执行了
	m_atk_speed = 1.0f;
	auto anim = (Armature*)m_char_root->getActionByTag(TAG_GNT_BODY);
	if (anim)
	{
		anim->getAnimation()->setSpeedScale(m_atk_speed);
	}

	// 通知
	MessageDispatcher::Instance()->DispatchMsg(-1,this,this,M_DEAD,nullptr);
}

void GameEntity::increateHp( int _hp )
{

	if (m_attr.m_hp + _hp <= m_attr.m_hp_max)
	{
		m_attr.m_hp += _hp;
	}
	else
	{
		m_attr.m_hp = m_attr.m_hp_max;
	}
}




//void GameEntity::onExit()
//{
//	/*if (_custom_event)
//	{
//		_eventDispatcher->removeEventListener(_custom_event);
//	}*/
//
//	Node::onExit();
//}

void GameEntity::pause()
{
	auto _body = (Armature*)m_char_root->getChildByTag(TAG_GNT_BODY);
	if (_body)
	{
		_body->getAnimation()->pause();
	}

	Node::pause();
}


void GameEntity::resume()
{
	auto _body = (Armature*)m_char_root->getChildByTag(TAG_GNT_BODY);
	if (_body)
	{
		_body->getAnimation()->resume();
	}

	Node::resume();
}





void GameEntity::playDeadFade(float _delay)
{
	auto ani = m_char_root->getChildByTag(TAG_GNT_BODY);
	if (ani)
	{
		ani->runAction(FadeOut::create(_delay));
	}

	//this->runAction(Sequence::create(DelayTime::create(0.5f),CallFunc::create( CC_CALLBACK_0(GameEntity::deadFadeCallback,this))));
}



GameDefine::Dir GameEntity::flipDir( GameDefine::Dir _new_dir )
{
	CC_ASSERT(false && "no implementation");
	return GameDefine::DIR_L;
}




bool GameEntity::initCardId( int _cid )
{
	auto item_info = (GameDefine::cfg_Card*)g_ItemInfoMgr.getObject(_cid);
	if (!item_info)
	{
		CCLOG("item id %d no data",_cid);
		return false;
	}


	auto pAttr = g_ObjInfoMgr.getObject(item_info->obj_id);
	if (!pAttr)
	{
		CCLOG("obj init failed since obj id invalid");
		return false;
	}

	m_attr.m_card_id = _cid;
	m_attr.m_obj_id = item_info->obj_id;
	m_attr.m_hp = pAttr->hp;
	m_attr.m_hp_max = m_attr.m_hp;
	m_attr.m_phy_atk = pAttr->phy_atk;
	m_attr.m_mag_atk = pAttr->mag_atk;
	m_attr.m_phy_def = pAttr->phy_def;
	m_attr.m_mag_def = pAttr->mag_def;
	m_attr.m_atk_cri = pAttr->atk_cri;
	m_attr.m_speed = pAttr->speed;


	m_attr_copy = m_attr;


	if(!m_skillMgr.init(*pAttr))
	{
		CCLOG("skill init failed");
		return false;
	}

	// 主体
	Armature* pAni = Armature::create(pAttr->path);
	pAni->setScale(pAttr->scale);
	m_char_root->addChild(pAni,TAG_GNT_BODY_LAYER_LVL,TAG_GNT_BODY);
	// 设置大小
	this->setContentSize(pAni->getContentSize()*pAttr->scale);

	// 血条
	Sprite* hp_bg = Sprite::create("ui/hp_bg.png");
	//hp_bg->setScale(pAttr->scale);
	float offset_y = pAni->getBoundingBox().size.height + GD_BLOOD_OFFSET_BODY_LEN;
	auto hp = Sprite::create("ui/hp.png");
	auto blood = ProgressTimer::create(hp);
	blood->setType(ProgressTimer::Type::BAR);
	blood->setMidpoint(Vec2(0, 0.5));
	blood->setBarChangeRate(Vec2(1, 0));
	//blood->setScale(pAttr->scale);
	hp_bg->setPosition(Vec2(0,offset_y));
	blood->setPosition(Vec2(0,offset_y));
	blood->setPercentage(BaseDefine::HUNDRED_BASE);
	m_char_root->addChild(hp_bg,TAG_GNT_HUD_LAYER_LVL,TAG_GNT_BLOOD_BG);
	m_char_root->addChild(blood,TAG_GNT_HUD_LAYER_LVL,TAG_GNT_BLOOD_FG);


	// 影子
	auto shadow = Sprite::create("ui/shadow.png");
	//shadow->setScale(pAttr->scale);
	shadow->setPosition(Vec2(0,0));
	m_char_root->addChild(shadow,TAG_GNT_SHADOW_LAYER_LVL,TAG_GNT_SHADOW);

	return true;
}



void GameEntity::OnReborth()
{
	// 血量回来
	m_attr.m_hp = m_attr.m_hp_max;


	// 隐藏了，显示出来
	auto ani = m_char_root->getChildByTag(TAG_GNT_BODY);
	if (ani)
	{
		ani->setVisible(true);
	}


	// 回到初始化状态
	MessageDispatcher::Instance()->DispatchMsg(-1,this,this,M_REBORN,nullptr);
	//update(0);
}



void GameEntity::onDeadEvent()
{
	// 消逝效果
	auto ce = CorpseEffect::create();
	ce->setDelay(0.5f);
	ce->retain();
	ce->go(this);

}



void GameEntity::attachCharAnim( Node* _anim, int _lvl, int _tag )
{
	if (!_anim || !m_char_root)
	{
		return;
	}

	m_char_root->addChild(_anim,_lvl,_tag);
}







