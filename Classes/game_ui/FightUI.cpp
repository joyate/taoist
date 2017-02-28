#include "FightUI.h"
#include "cocostudio/CocoStudio.h"
#include "../data/LocalPlayer.h"
#include "SideItem.h"
#include "../obj/Defender.h"
#include "../obj/Hero.h"
#include "../frame/BattleScene.h"
#include "SkillIcon.h"
#include "../game_ui/HeadUpInfo.h"
#include "../component/PopTipManager.h"
#include "../data/MsgManager.h"
#include "../component/PopTipManager.h"
#include "../utility/Utility.h"
#include "../ui_ext/SideItemListView.h"

using namespace cocostudio;


const float CARD_PIC_SCALE = 0.4f;



FightUI::FightUI(void):
	m_bShopShow(false),
	m_drag_sprite(nullptr),
	_mapMgr(nullptr),
	m_skill_icon(nullptr),
	m_sideitem_op_dir(DIR_SHOP_LIST_NONE)
{
}


FightUI::~FightUI(void)
{
	//
	if(m_reward_update_listener)
		_eventDispatcher->removeEventListener(m_reward_update_listener);

	if (m_hero_info_update_listener)
		_eventDispatcher->removeEventListener(m_hero_info_update_listener);

}





bool FightUI::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size win_size = Director::getInstance()->getWinSize();

	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("FightUI/FightUI.ExportJson");
	this->addChild(m_layout);

	// UI
	Button* shop_btn = Button::create("ui/shop.png");
	shop_btn->setPosition(Vec2(shop_btn->getContentSize().width/2,win_size.height - shop_btn->getContentSize().height/2));
	this->addChild(shop_btn,SHOP_BTN_LAYER,TAG_SHOP_BTN);
	//shop_btn->setTag(TAG_BS_SHOP_EVENT);
	shop_btn->addTouchEventListener(CC_CALLBACK_2(FightUI::touchShopEvent,this));



#ifndef IMPL_BTN_EVENT
#define IMPL_BTN_EVENT(_root,_name)	\
	do{\
	Button* btn = (Button*)Helper::seekWidgetByName(_root,#_name); \
	btn->addTouchEventListener(CC_CALLBACK_2(FightUI::moveItemEvent,this)); \
	}while(0)

	auto pl_side_item = (Widget*)m_layout->getChildByName("pl_side_item");
	if (pl_side_item)
	{
		//IMPL_BTN_EVENT(pl_side_item,btn_up);
		//IMPL_BTN_EVENT(pl_side_item,btn_down);
	}

#endif



	// 清理
	cleanUI();


	// FightUI界面事件
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(FightUI::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(FightUI::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(FightUI::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	// 奖励自定义刷新事件
	m_reward_update_listener = EventListenerCustom::create(GameDefine::REWARD_UPDATE_EVENT,
		[=](EventCustom* ec) {

			auto& fi = LocalPlayer::getInstance()->m_temp_fight_info;

			// 更新金币
			auto gold = (Widget*)m_layout->getChildByName("gold");
			if (gold)
			{
				auto img_gold = (ImageView*)gold->getChildByName("img_gold");	
				auto label_gold = (TextBMFont*)gold->getChildByName("label_gold");
				if (label_gold && img_gold)
				{
					std::string last_gold = label_gold->getString();
					std::string cur_gold = StringUtils::format("%d",fi.rewardGold);
					if (cur_gold != last_gold)
					{
						label_gold->setString(cur_gold);
						img_gold->runAction(Sequence::create(ScaleTo::create(0.2f,1.2f),ScaleTo::create(0.2f,1),nullptr));
					}
				}
			}

			// 更新箱子
			auto item = (Widget*)m_layout->getChildByName("item");
			if (item)
			{
				auto img_item = (ImageView*)item->getChildByName("img_item");	
				auto label_item = (TextBMFont*)item->getChildByName("label_item");

				std::string last_case_cnt = label_item->getString();
				std::string case_cnt = StringUtils::format("%d",fi.getRewardCnt());

				if (img_item && label_item)
				{
					if (last_case_cnt != case_cnt)
					{
						img_item->runAction(Sequence::create(ScaleTo::create(0.2f,1.2f),ScaleTo::create(0.2f,1),nullptr));
						label_item->setString(case_cnt);
					}
				}
			}

		});
	_eventDispatcher->addEventListenerWithFixedPriority(m_reward_update_listener,1);



	// 注册英雄信息更新事件
	m_hero_info_update_listener = EventListenerCustom::create(GameDefine::BATTLE_HERO_INFO_UPDATE_EVENT,
		[=](EventCustom* ec) {

			updateHeroInfo();
	});
	_eventDispatcher->addEventListenerWithFixedPriority(m_hero_info_update_listener,1);


	scheduleUpdate();

	// 初始化示例事件
	return initFromLocalPlayer();
}


bool FightUI::initFromLocalPlayer()
{
	const tTempFightInfo& fsi = LocalPlayer::getInstance()->m_temp_fight_info;

	auto pl_side_item = m_layout->getChildByName("pl_side_item");
	if (!pl_side_item)
	{
		return false;
	}


	if(!initHeroData(fsi.army_inst_id[tTempFightInfo::ARMY_HERO_INDEX]))
	{
		CCLOG("init hero failed");
		return false;
	}


	auto si_lv = SideItemListView::create();
	si_lv->initFromLocalPlayer(this);
	si_lv->setName("lv_side_item");
	si_lv->setPosition(Vec2(0,30));
	pl_side_item->addChild(si_lv);


	//// 初始化小兵池
	//auto side_lv = (ListView*)pl_side_item->getChildByName("lv_side_item");
	//if (!side_lv)
	//{
	//	return false;
	//}

	//for (int i = 0; i < GameDefine::GD_ARMY_ON_ROUND_NUM_MAX; i++)
	//{
	//	// 
	//	if (!fsi.army_inst_id[i])
	//	{
	//		continue;
	//	}


	//	// 排除英雄索引
	//	if (i == tTempFightInfo::ARMY_HERO_INDEX)
	//	{
	//		initHeroData(fsi.army_inst_id[i]);
	//	}
	//	else
	//	{
	//		// 兵种选择item
	//		auto si = SideItem::create();
	//		si->initFromCardInstance(fsi.army_inst_id[i]);
	//		si->setTag(fsi.army_inst_id[i]);
	//		si->setTouchEnabled(true);
	//		si->addTouchEventListener(CC_CALLBACK_2(FightUI::touchShopItemEvent,this));


	//		//
	//		auto lp = LinearLayoutParameter::create();
	//		lp->setMargin(Margin(1.0f, 10.0f, 1.0f, 10.0f));
	//		lp->setGravity(LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
	//		si->setLayoutParameter(lp);

	//		side_lv->addChild(si);
	//	}
	//}

	return true;
}

void FightUI::touchShopEvent( Ref *pSender, Widget::TouchEventType type )
{
	Button* pbtn = (Button*)pSender;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			int tag = pbtn->getTag();

			// 兵种选择
			if (tag == TAG_SHOP_BTN)
			{
				if (m_bShopShow)
				{
					// 当前隐藏，显示出来		
					auto pl_side_item = m_layout->getChildByName("pl_side_item");
					if (!pl_side_item)
					{
						return;
					}

					pl_side_item->runAction(MoveBy::create(0.5f,Vec2(-pl_side_item->getContentSize().width,0)));
					m_bShopShow = false;
				}
				else
				{
					// 当前隐藏，显示出来		
					auto pl_side_item = m_layout->getChildByName("pl_side_item");
					if (!pl_side_item)
					{
						return;
					}

					pl_side_item->runAction(MoveBy::create(0.5f,Vec2(pl_side_item->getContentSize().width,0)));
					m_bShopShow = true;
				}
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void FightUI::touchShopItemEvent( Ref *pSender, Widget::TouchEventType type )
{
	auto widget = static_cast<SideItem*>(pSender);
	CC_ASSERT(_mapMgr);
	if (!_mapMgr)
	{
		CCLOG("[FightUI::touchShopItemEvent] map manager invalid");
		return;
	}

	/*if (widget->isColddown())
	{
	return;
	}*/

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		{
			widget->runAction(EaseElasticInOut::create(ScaleTo::create(0.1f, 1.1f),0.2f));

			m_sideitem_op_dir = DIR_SHOP_LIST_NONE;

			auto si_lv = (SideItemListView*)Utility::findWidget(m_layout,"pl_side_item/lv_side_item");
			if (si_lv)
			{
				si_lv->setOpDir(SideItemListView::DIR_SHOP_LIST_NONE);
			}

			/*auto obj_info = g_ObjInfoMgr.getObject(widget->getObjId());
			if (!obj_info)
			{
				CCLOG("obj id %d has no data",widget->getObjId());
				return;
			}

			auto& hi = LocalPlayer::getInstance()->m_temp_fight_info.hero_info;
			if (hi.base_ghost < obj_info->ghost)
			{
				CCLOG("hero check ghost cost failed");
				return;
			}

			_mapMgr->ShowObjGrid();*/
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		{
			//CCLOG("touch moved");

			if (m_sideitem_op_dir == DIR_SHOP_LIST_NONE)
			{
				Vec2 diff = widget->getTouchMovePosition() - widget->getTouchBeganPosition();
				if (diff.length() < 16)
				{
					return;
				}


				diff.y = diff.y >= 0 ? diff.y : -diff.y;
				diff.x = diff.x >= 0 ? diff.x : -diff.x;

				if ( diff.y > diff.x)
				{
					m_sideitem_op_dir = DIR_SHOP_LIST_VERTICAL;
				}
				else
				{
					m_sideitem_op_dir = DIR_SHOP_LIST_HORIZONTAL;
				}

				auto si_lv = (SideItemListView*)Utility::findWidget(m_layout,"pl_side_item/lv_side_item");
				if (si_lv)
				{
					si_lv->setOpDir(m_sideitem_op_dir);
				}
			}
			

			if (m_sideitem_op_dir == DIR_SHOP_LIST_HORIZONTAL)
			{

				//if (m_bShopShow)
				//{
				//	auto pl_side_item = m_layout->getChildByName("pl_side_item");
				//	if (!pl_side_item)
				//	{
				//		return;
				//	}

				//	pl_side_item->runAction(MoveBy::create(0.5f,Vec2(-pl_side_item->getContentSize().width,0)));
				//	m_bShopShow = false;


				//	//
				//	auto shop_btn = this->getChildByTag(TAG_SHOP_BTN);
				//	if (shop_btn)
				//	{
				//		shop_btn->setVisible(!m_bShopShow);
				//	}
				//}


				if (widget->isColddown())
				{
					return;
				}

				if (!m_drag_sprite)
				{

					auto item_info = LocalPlayer::getInstance()->m_bag.getItemById(widget->getInstId());
					if (!item_info)
					{
						CCLOG("inst item with id %d not found",widget->getInstId());
						return;
					}

					auto cfg_item_info = (cfg_Card*)g_ItemInfoMgr.getObject(item_info->item_temp_id);
					if (!cfg_item_info)
					{
						CCLOG("item id %d no data",item_info->item_temp_id);
						return;
					}

					m_drag_sprite = Sprite::create(cfg_item_info->card_pic);
					m_drag_sprite->setScale(CARD_PIC_SCALE); // 缩放比例
					Node* map_root = this->getParent()->getChildByTag(BattleScene::TAG_MAP_LAYER);
					map_root->addChild(m_drag_sprite,ARMY_ICON_LAYER);

					// 显示网格
					_mapMgr->ShowObjGrid();
				}
				else
				{

					Vec2 pos = widget->getTouchMovePosition();

					// todo 这里要理解一下
					pos -= _mapMgr->getPosition();
					m_drag_sprite->setPosition(pos);

					int _gi_index = _mapMgr->getVec2Rect(pos);
					if (_gi_index >= 0)
					{
						_mapMgr->activeSelectBg(_gi_index);
					}

				}
			}
		}

		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			widget->runAction( EaseElasticInOut::create(ScaleTo::create(0.1f, 1.f), 0.2f));

			if (m_sideitem_op_dir == DIR_SHOP_LIST_HORIZONTAL)
			{
				if(m_drag_sprite != nullptr)
				{
					m_drag_sprite->removeFromParent();
					m_drag_sprite= nullptr;
				}

				_mapMgr->ShowObjGrid(false);
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		{
			widget->runAction(EaseElasticInOut::create(ScaleTo::create(0.1f, 1.0f),0.2f));
			
			
			if (m_sideitem_op_dir == DIR_SHOP_LIST_HORIZONTAL)
			{
				if(m_drag_sprite == NULL)
				{
					return;
				}

				m_drag_sprite->removeFromParent();
				m_drag_sprite= NULL;

				_mapMgr->ShowObjGrid(false);


				auto obj_info = g_ObjInfoMgr.getObject(widget->getObjId());
				if (!obj_info)
				{
					CCLOG("obj id %d has no data",widget->getObjId());
					return;
				}

				do 
				{
					auto& hi = LocalPlayer::getInstance()->m_temp_fight_info.hero_info;
					if (!hi.costGhost(obj_info->ghost,false))
					{
						PopTipManager::getInstance()->popTips(MsgManager::SKILL_COST_NOT_ENOUGH);
						break;
					}



					Vec2 pos = widget->getTouchMovePosition();
					pos -= _mapMgr->getPosition();
					CCLOG("pos:%f,%f",pos.x,pos.y);
					int _gi_index = _mapMgr->getVec2Rect(pos);
					// 负值表示非法
					if(_gi_index < 0)
					{
						if (_gi_index == -2)
						{
							PopTipManager::getInstance()->popTips(MsgManager::BATTLE_POS_HAS_USED);
						}

						break;
					}
					
					int inst_card_id = widget->getTag();
					auto inst_item_info = LocalPlayer::getInstance()->m_bag.getItemById(inst_card_id);


					Defender* _army = Defender::create();
					//
					_army->initCardId(inst_item_info->item_temp_id);
					_mapMgr->putObjectInGrid(_gi_index,_army);
					_army->setRectIndex(_gi_index);

					widget->onEnterColddown();
					hi.costGhost(obj_info->ghost);

					updateHeroInfo();

				} while (false);

			} // m_op == DIR
		}
		break;
	default:
		break;
	}
}



bool FightUI::onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* event )
{
	// 兵种面板 
	if (m_bShopShow)
	{
		auto pl_side_item = (ListView*)m_layout->getChildByName("pl_side_item");
		if (pl_side_item)
		{
			pl_side_item->runAction(MoveBy::create(0.5f,Vec2(-pl_side_item->getContentSize().width,0)));
			m_bShopShow = false;


			// 小兵商店按钮
			auto shop_btn = this->getChildByTag(TAG_SHOP_BTN);
			if (shop_btn)
			{
				shop_btn->setVisible(!m_bShopShow);
			}

		}
	}


	// 隐藏hui
	auto hui = this->getChildByTag(TAG_HUI_NODE);
	if (hui)
	{
		hui->removeFromParent();
	}

	// 隐藏card tip
	auto cardtip = this->getChildByTag(TAG_CARD_TIP_NODE);
	if (cardtip)
	{
		cardtip->removeFromParent();
	}

	return true;
}

void FightUI::onTouchMoved( cocos2d::Touch* touch, cocos2d::Event* event )
{

}

void FightUI::onTouchEnded( cocos2d::Touch* touch, cocos2d::Event* event )
{
	CC_ASSERT(_mapMgr);
	if (!_mapMgr)
	{
		CCLOG("[FightUI::onTouchEnded] map manager is invalid");
		return;
	}


	Vec2 pos = touch->getLocation();
	static int last_type = MapManager::OT_COMMON;
	int cur_type;
	GameEntity* _sel = _mapMgr->onTouch(pos,cur_type);

	switch (last_type)
	{
	case MapManager::OT_COMMON:
		{
			// 非英雄
			if (_sel && !(_sel->getSubType() & GameEntity::OT_HERO))
			{
				auto hui = HeadUpInfo::create();
				hui->setOwnerId(_sel->getCardId());

				Vec2 pos = _sel->getPosition() + _mapMgr->getPosition();
				pos.y += _sel->getBoundingBox().size.height + hui->getContentSize().height/2;

				hui->setPosition(pos);
				hui->setTag(TAG_HUI_NODE);
				this->addChild(hui);
			}
		}
		break;
	default:
		break;
	}
	
	last_type = cur_type;
}



bool FightUI::initHeroData( int _inst_card_id )
{
	if (_inst_card_id <= 0)
	{
		CCLOG("invalid instance card id:%d",_inst_card_id);
		return false;
	}

	auto lp = LocalPlayer::getInstance();
	auto item = lp->m_bag.getItemById(_inst_card_id);
	if (!item)
	{
		return false;
	}

	// 技能相关
	auto cfg_card_info = (cfg_Card*)g_ItemInfoMgr.getObject(item->item_temp_id);
	if (cfg_card_info && cfg_card_info->obj_id > 0)
	{
		auto obj_info = (GameDefine::cfg_Obj_Attr*)g_ObjInfoMgr.getObject(cfg_card_info->obj_id);

		for (int i = 0,j = 1; i < GameDefine::GD_SKILL_NUM_MAX; i++)
		{
			if (obj_info->skill_ids[i] > 0)
			{

				auto skill_info = g_SkillInfoMgr.getObject(obj_info->skill_ids[i]);
				if (!skill_info)
				{
					CCLOG("skill %d no skill data",obj_info->skill_ids[i]);
					continue;
				}

				if (skill_info->sk_type <= ST_AUTO)
				{
					continue;
				}

				int zorder = 0;
				auto fmt_skill = StringUtils::format("img_hero_data_bg/skill_%d",j++);
				auto skill_pl = Utility::findWidget(m_layout,fmt_skill);
				if (skill_pl)
				{
					auto skill_icon = SkillIcon::create(skill_info->szSkillIcon,skill_info->szSkillIcon);
					skill_icon->setTag(obj_info->skill_ids[i]);
					skill_icon->setTouchEnabled(true);
					skill_icon->addTouchEventListener(CC_CALLBACK_2(FightUI::touchSkillEvent,this));
					skill_icon->setPosition(Vec2(skill_pl->getContentSize().width/2,skill_pl->getContentSize().height/2));
					skill_icon->setPercent(100.0f);
					skill_pl->addChild(skill_icon);
					zorder = skill_icon->getLocalZOrder();
				}

				// 设置技能类型
				
				switch (skill_info->sk_type)
				{
				case ST_POSITIVE_DRAG:
					{
						fmt_skill += "/sk_drag";
						auto sk_type = (ImageView*)Utility::findWidget(m_layout,fmt_skill);
						if (sk_type)
						{
							sk_type->setVisible(true);
							sk_type->setLocalZOrder(zorder+1);
						}
					}
					break;
				case ST_POSITIVE_IM:
					{
						fmt_skill += "/sk_im";
						auto sk_type = (ImageView*)Utility::findWidget(m_layout,fmt_skill);
						if (sk_type)
						{
							sk_type->setVisible(true);
							sk_type->setLocalZOrder(zorder+1);
						}
					}
					break;
				default:
					break;
				}

			}
		}

		// 设置英雄战时数据
		auto& bi = lp->m_temp_fight_info;
		bi.hero_info.base_ghost = obj_info->ghost;
		bi.hero_info.ghost_base_speed = obj_info->ghost_speed;

		// 界面信息
		auto fbt_ghost = (TextBMFont*)Utility::findWidget(m_layout,"img_hero_data_bg/pl_ghost/fbt_ghost");
		if (fbt_ghost)
		{
			fbt_ghost->setString(StringUtils::format("%d",obj_info->ghost));
			m_base_ghost = obj_info->ghost;
		}

	}

	return true;
}

void FightUI::touchSkillEvent( Ref *pSender, Widget::TouchEventType type )
{
	auto skill_icon = dynamic_cast<SkillIcon*>(pSender);

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		{
			// 正在冷却
			if (skill_icon->isBusy())
			{
				break;
			}

			CC_ASSERT(!m_skill_icon);
			if (!m_skill_icon)
			{
				
				auto skill_info = g_SkillInfoMgr.getObject(skill_icon->getTag());
				if (!skill_info)
				{
					CCLOG("skill id %d no data",skill_icon->getTag());
					break;
				}

				if (skill_info->sk_type == ST_POSITIVE_DRAG)
				{
					m_skill_icon = Sprite::create(skill_info->szSkillIcon);
					m_skill_icon->setPosition(skill_icon->getTouchBeganPosition());

					// 放在map manager 中的TAG_MAP_LAYER
					Node* map_root = this->getParent()->getChildByTag(BattleScene::TAG_MAP_LAYER);
					if(map_root)
					{
						map_root->addChild(m_skill_icon,SKILL_ICON_LAYER);
					}
				}
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		{
			
			// 拖动技能
			if(m_skill_icon)
			{

				CCLOG("move pos:%f,%f",skill_icon->getTouchMovePosition().x,skill_icon->getTouchMovePosition().y);

				auto skill_info = g_SkillInfoMgr.getObject(skill_icon->getTag());
				if (!skill_info)
				{
					CCLOG("skill id %d no data",skill_icon->getTag());
					break;
				}

				if (skill_info->sk_type != ST_POSITIVE_DRAG)
				{
					CCLOG("[TouchEventType::MOVED] skill type invalid");
					break;
				}

				// todo 这里要理解一下
				Vec2 pos = skill_icon->getTouchMovePosition();
				pos -= _mapMgr->getPosition();
				m_skill_icon->setPosition(pos);
			}
			

		}
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			// 正在冷却
			if (skill_icon->isBusy())
			{
				break;
			}

			// 拖动技能
			if (m_skill_icon)
			{
				m_skill_icon->removeFromParent();
				m_skill_icon = nullptr;
			}

			auto _hero = (Hero*)_mapMgr->getHero();
			if (!_hero)
			{
				break;
			}

			// 行走时不能释放技能
			if (_hero->isWalking())
			{
				PopTipManager::getInstance()->popTips(MsgManager::SKILL_STATE_WALK_CHECK);
				break;
			}

			auto skill_info = g_SkillInfoMgr.getObject(skill_icon->getTag());
			if (!skill_info)
			{
				CCLOG("skill id %d no data",skill_icon->getTag());
				break;
			}

			if (skill_info->sk_type != ST_POSITIVE_IM)
			{
				CCLOG("[TouchEventType::ENDED] skill type invalid");
				break;
			}

			auto hero = (Hero*)_mapMgr->getHero();
			if(hero)
			{
				if (!hero->skillCost(skill_info,true))
				{
					PopTipManager::getInstance()->popTips(MsgManager::SKILL_COST_NOT_ENOUGH);
					break;
				}

				hero->useSkill(skill_info->id,1);
				skill_icon->onEnterColddown();
				updateHeroInfo();
			}
			
			

		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		{
			// 正在冷却
			if (skill_icon->isBusy())
			{
				break;
			}

			if (m_skill_icon)
			{

				do 
				{
					// 释放技能
					auto hero = (Hero*)_mapMgr->getHero();
					if (hero)
					{
						auto skill_info = g_SkillInfoMgr.getObject(skill_icon->getTag());
						if (!skill_info)
						{
							CCLOG("skill id %d no data",skill_icon->getTag());
							break;
						}


						if (skill_info->sk_type != ST_POSITIVE_DRAG)
						{
							CCLOG("[TouchEventType::CANCELED] skill type invalid");
							break;
						}


						// 真是恶心的设计
						auto target = _mapMgr->GetGameObjectByPos(m_skill_icon->getPosition());
						if (skill_info->sk_exec_type == 4)
						{
							// 没有目标
							if (!target)
							{
								break;
							}

							// 用到自己身上了
							if (target == hero)
							{
								PopTipManager::getInstance()->popTips(MsgManager::SKILL_TIP_TARGET_SELF);
								break;
							}

							if (!hero->skillCost(skill_info,true))
							{
								PopTipManager::getInstance()->popTips(MsgManager::SKILL_COST_NOT_ENOUGH);
								break;
							}

							//
							static_cast<Defender*>(target)->usePrivateSkill();
							skill_icon->onEnterColddown();
							
						}
						else
						{
							if (!hero->skillCost(skill_info,true))
							{
								PopTipManager::getInstance()->popTips(MsgManager::SKILL_COST_NOT_ENOUGH);
								break;
							}

							Skill* _skill = hero->useSkill(skill_info->id,1);
							if (_skill)
							{
								_skill->setTargetPos(m_skill_icon->getPosition());		
								if (target)
								{
									_skill->pushTargetId(target->getID());
								}

								skill_icon->onEnterColddown();
							}
						} // skill type

						// 更新ghost值
						updateHeroInfo();

					} // hero

				} while (false);

				m_skill_icon->removeFromParent();
				m_skill_icon = nullptr;

			}
		}
		break;
	default:
		break;
	}
}



void FightUI::initUI()
{
	auto gold = (Widget*)m_layout->getChildByName("gold");
	if (gold)
	{
		auto label_gold = (TextBMFont*)gold->getChildByName("label_gold");
		if (label_gold)
		{
			label_gold->setString("0");
		}
	}

	// 更新箱子
	auto item = (Widget*)m_layout->getChildByName("item");
	if (item)
	{
		auto label_item = (TextBMFont*)item->getChildByName("label_item");
		if ( label_item)
		{
			label_item->setString("0");			
		}
	}




}

void FightUI::updateHeroInfo()
{
	auto hero = (Hero*)_mapMgr->getHero();
	if (!hero)
	{
		return;
	}

	auto& hi = LocalPlayer::getInstance()->m_temp_fight_info.hero_info;
	hi.base_ghost += hi.ghost_base_speed;
	//
	auto fbt_ghost = (TextBMFont*)Utility::findWidget(m_layout,"img_hero_data_bg/pl_ghost/fbt_ghost");
	if (fbt_ghost)
	{
		fbt_ghost->setString(StringUtils::format("%d",hi.base_ghost));
	}

}



void FightUI::cleanUI()
{
	// 初始化，清理界面
	auto gold = (Widget*)m_layout->getChildByName("gold");
	if (gold)
	{	
		auto label_gold = (TextBMFont*)gold->getChildByName("label_gold");
		if (label_gold)
		{
			label_gold->setString("0");
		}
	}

	auto item = (Widget*)m_layout->getChildByName("item");
	if (item)
	{	
		auto label_item = (TextBMFont*)item->getChildByName("label_item");
		if (label_item)
		{
			label_item->setString("0");
		}
	}



	// 清理技能图标
	for (int i = 0; i < GameDefine::GD_SKILL_NUM_MAX; i++)
	{
		auto skill_icon = m_layout->getChildByName(StringUtils::format("skill_%d",i+1));
		if (skill_icon)
		{
			int nChildCount = skill_icon->getChildrenCount();
			if (nChildCount > 0)
			{
				skill_icon->removeAllChildrenWithCleanup(true);
			}
		}
	}
}

void FightUI::updateSideItemGhost()
{
	// 英雄死了也就不用刷了
	auto hero = _mapMgr->getHero();
	if (!hero || !hero->isAlive())
	{
		return;
	}

	auto pl_side_item = m_layout->getChildByName("pl_side_item");
	if (!pl_side_item)
	{
		return;
	}

	auto lv_side_items = (ListView*)pl_side_item->getChildByName("lv_side_item");	
	auto& hi = LocalPlayer::getInstance()->m_temp_fight_info.hero_info;
	for (auto _iter : lv_side_items->getChildren())
	{
		auto si = (SideItem*)_iter;
		si->updateGhostState(hi.base_ghost);
	}
}



void FightUI::moveItemEvent( Ref *pSender, Widget::TouchEventType type )
{

	auto btn = (Button*)pSender;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			auto pl_side_item = m_layout->getChildByName("pl_side_item");
			if (!pl_side_item)
			{
				return;
			}

			auto lv_side_items = (ListView*)pl_side_item->getChildByName("lv_side_item");
			if (!lv_side_items)
			{
				return;
			}

			if (btn->getName() == "btn_up")
			{
				lv_side_items->scrollToPercentVertical(0,0.3f,true);
			}
			else if(btn->getName() == "btn_down")
			{
				lv_side_items->scrollToPercentVertical(100,0.3f,true);
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void FightUI::update( float delta )
{
	static float last = 0;
	last += delta;
	if (m_bShopShow)
	{
		// 灵气刷新
		if(last > GHOST_UPDATE_INTERVAL)
		{
			// 刷新
			updateSideItemGhost();
			last = 0;
		}
	}
}


