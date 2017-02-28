#include "StageArmySel.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"
#include "../data/LocalPlayer.h"
#include "Item.h"
#include "HeroItem.h"
#include "HeroInfoPanel.h"
#include "../frame/LoadingScene.h"
#include "../component/TimeManager.h"
#include "../component/PopTipManager.h"
#include "../data/MsgManager.h"

using namespace cocostudio;



StageArmySel::StageArmySel(void):
	m_layout(nullptr),
	m_wx_type(GameDefine::CAT_METAL),
	m_stage_id(0)
{
}


StageArmySel::~StageArmySel(void)
{
}



bool StageArmySel::init()
{
	if (!Widget::init())
	{
		return false;
	}


	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("StageArmySel/StageArmySel.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);



#ifndef IMPL_BTN_EVENT
#define IMPL_BTN_EVENT(_root,_name)	\
	do{\
	Button* btn = (Button*)Helper::seekWidgetByName(_root,#_name); \
	btn->addTouchEventListener(CC_CALLBACK_2(StageArmySel::btnTouchEvent,this)); \
	}while(0)


	IMPL_BTN_EVENT(m_layout,btn_gold);
	IMPL_BTN_EVENT(m_layout,btn_wood);
	IMPL_BTN_EVENT(m_layout,btn_water);
	IMPL_BTN_EVENT(m_layout,btn_fire);
	IMPL_BTN_EVENT(m_layout,btn_earth);
	IMPL_BTN_EVENT(m_layout,btn_fight);

#endif

	updateHeroInfo();
	updateArmyInfo();

	return true;
}

void StageArmySel::updateHeroInfo()
{
	auto pl_army_info = m_layout->getChildByName("pl_army_info");
	if (!pl_army_info)
	{
		return;
	}

	auto pl_heros = pl_army_info->getChildByName("pl_heros");
	if (!pl_heros)
	{
		return;
	}


	auto lp = LocalPlayer::getInstance();
	const GameDefine::tBagInfo& bagInfo = lp->m_bag.getBagInfo();

	auto lv_heros = (ListView*)pl_heros->getChildByName("lv_heros");
	if (lv_heros)
	{
		lv_heros->removeAllChildren();

		for (auto _iter = bagInfo.m_items.begin();
			_iter != bagInfo.m_items.end();
			_iter++)
		{
			// 物品类型过滤
			auto item_info = g_ItemInfoMgr.getObject(_iter->second->item_temp_id);
			if (!item_info || item_info->item_type != IT_CARD)
			{
				continue;
			}

			// 卡牌类型、五行过滤
			auto card_info = static_cast<cfg_Card*>(item_info);
			if (card_info->arm_type != GameDefine::AT_ARMY_HERO)
			{
				continue;
			}


			auto _item = HeroInfoPanel::create();
			_item->initFromInstCardInfo(_iter->second);
			_item->setTag(_iter->second->item_id);

			//_item->setLocalZOrder(lv_armys->getLocalZOrder()+1);
			_item->setTouchEnabled(true);
			_item->addTouchEventListener(CC_CALLBACK_2(StageArmySel::heroCardTouchEvent,this));


			lv_heros->addChild(_item);
		}
	}
}



void StageArmySel::updateArmyInfo()
{
	auto pl_army_info = m_layout->getChildByName("pl_army_info");
	if (!pl_army_info)
	{
		return;
	}


	auto pl_armys = pl_army_info->getChildByName("pl_armys");
	if (!pl_armys)
	{
		return;
	}

	auto lp = LocalPlayer::getInstance();
	const GameDefine::tBagInfo& bagInfo = lp->m_bag.getBagInfo();

	auto lv_armys = (ListView*)pl_armys->getChildByName("lv_armys");
	if (lv_armys)
	{
		lv_armys->removeAllChildren();


		int act_cnt = 0;
		Layout* layout = nullptr;
		for (auto _iter = bagInfo.m_items.begin();
			_iter != bagInfo.m_items.end();
			_iter++)
		{
			// 物品类型过滤
			auto item_info = g_ItemInfoMgr.getObject(_iter->second->item_temp_id);
			if (!item_info || item_info->item_type != IT_CARD)
			{
				continue;
			}

			// 卡牌类型、五行过滤
			auto card_info = static_cast<cfg_Card*>(item_info);
			if (card_info->arm_type != GameDefine::AT_ARMY_SOLDIER || card_info->cat != m_wx_type)
			{
				continue;
			}

			if (act_cnt % BAG_ITEM_COL_MAX == 0)
			{
				layout = Layout::create();
				layout->setLayoutType(LayoutType::HORIZONTAL);
				//layout->setClippingEnabled(true);
				layout->setContentSize(Size(480, 110));
				lv_armys->addChild(layout);

				//
				LinearLayoutParameter* llp = LinearLayoutParameter::create();
				llp->setGravity(LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
				llp->setMargin(Margin(10.0f, 5.0f, 5.0f, 10.0f));
				layout->setLayoutParameter(llp);
			}


			auto _item = HeroItem::create();
			_item->initFromCfgItemInfo(card_info,HeroItem::HI_MASK_CTRL);
			_item->setTag(_iter->second->item_id);

			//_item->setLocalZOrder(lv_armys->getLocalZOrder()+1);
			_item->setTouchEnabled(true);
			_item->addTouchEventListener(CC_CALLBACK_2(StageArmySel::armyCardTouchEvent,this));
			//_item->setStarLvl(_iter->second->)

			layout->addChild(_item);
			act_cnt++;

		}

	}

}

void StageArmySel::btnTouchEvent( Ref *pSender, Widget::TouchEventType type )
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
			if(btn->getName() == "btn_fight")
			{
				const auto& fi = LocalPlayer::getInstance()->m_temp_fight_info;
				if (fi.army_inst_id[GameDefine::tTempFightInfo::ARMY_HERO_INDEX] == 0)
				{
					PopTipManager::getInstance()->popTips(MsgManager::BATTLE_NO_HERO);
					CCLOG("hero not selected");
					return;
				}


				const auto& stage_info = g_StageInfoMgr.getObject(m_stage_id);
				if (!stage_info)
				{
					CCLOG("stage id %d no data",this->getTag());
					return;
				}

				auto& ba = LocalPlayer::getInstance()->m_base_attr;
				int phys_val = ba.m_data[GameDefine::tBaseAttr::BA_PHYSICAL];
				if (phys_val < stage_info->phys_cost)
				{
					PopTipManager::getInstance()->popTips(MsgManager::BATTLE_PHYS_NOT_ENOUGH);
					CCLOG("phys not enough");
					return;
				}

				ba.m_data[GameDefine::tBaseAttr::BA_PHYSICAL] -= stage_info->phys_cost;
				// 这里是个小细节
				if(ba[GameDefine::tBaseAttr::BA_PHYSICAL_UPDATE] == 0)
					ba[GameDefine::tBaseAttr::BA_PHYSICAL_UPDATE] = TimeManager::getInstance().getTime();

				// 选将阶段
				auto loading = LoadingScene::create();
				Director::getInstance()->pushScene(loading);
			}
			else
			{
				int fe_type = btn->getTag() - BASE_FE_TYPE;
				if (fe_type != m_wx_type)
				{
					m_wx_type = fe_type;
					updateArmyInfo();
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

void StageArmySel::heroCardTouchEvent( Ref *pSender, Widget::TouchEventType type )
{

	auto item = (HeroInfoPanel*)pSender;
	int cur_inst_item_id = item->getTag();
	static bool btn_act = false;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		{
			btn_act = true;
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		{
			Vec2 dis = item->getTouchMovePosition() - item->getTouchBeganPosition();
			if(dis.lengthSquared() > DRAG_ACT_LENGTH)
			{
				btn_act = false;
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			if(btn_act)
			{
				auto lp = LocalPlayer::getInstance();
				tTempFightInfo& fsi = lp->m_temp_fight_info;


				if(fsi.army_inst_id[tTempFightInfo::ARMY_HERO_INDEX] != 0)
				{
					CCLOG("hero has been selected already");
					return;
				}

				fsi.army_inst_id[tTempFightInfo::ARMY_HERO_INDEX] = cur_inst_item_id;

				//
				auto pl_army_seled = m_layout->getChildByName("pl_army_seled");
				if (!pl_army_seled)
				{
					return;
				}

				auto pl_army_sel_root = pl_army_seled->getChildByName("pl_army_sel_root");
				if (!pl_army_sel_root)
				{
					return;
				}

				auto img_hero_sel = pl_army_sel_root->getChildByName("img_hero_sel");
				if (!img_hero_sel)
				{
					return;
				}


				auto _item = HeroItem::create();
				_item->initFromInstId(cur_inst_item_id);
				_item->setTag(cur_inst_item_id);
				_item->setPosition(Vec2(_item->getContentSize().width/2,_item->getContentSize().height/2));
				// 点击事件
				_item->setTouchEnabled(true);
				_item->addTouchEventListener(CC_CALLBACK_2(StageArmySel::heroCardCancelTouchEvent,this));

				img_hero_sel->addChild(_item);


				// 填充统治力
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}


	

}



void StageArmySel::armyCardTouchEvent( Ref *pSender, Widget::TouchEventType type )
{
	auto item = (HeroItem*)pSender;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			auto lp = LocalPlayer::getInstance();
			tTempFightInfo& fsi = lp->m_temp_fight_info;

			int cur_inst_item_id = item->getTag();
			int sel_index = fsi.addArmyId(cur_inst_item_id);

			if(sel_index >= 0)
			{
				appendArmy(sel_index);
			}	
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}



void StageArmySel::appendArmy( int _sel_index )
{

	auto pl_army_seled = m_layout->getChildByName("pl_army_seled");
	if (!pl_army_seled)
	{
		return;
	}


	auto pl_army_sel_root = pl_army_seled->getChildByName("pl_army_sel_root");
	if (!pl_army_sel_root)
	{
		return;
	}


	auto lv_armys_sel = (ListView*)pl_army_sel_root->getChildByName("lv_armys_sel");
	if (!lv_armys_sel)
	{
		return;
	}

	auto lp = LocalPlayer::getInstance();
	const tTempFightInfo& fsi = lp->m_temp_fight_info;
	do
	{
		CC_ASSERT(fsi.army_inst_id[_sel_index] > 0);
		if (fsi.army_inst_id[_sel_index] == 0)
		{
			break;
		}


		auto _item = HeroItem::create();
		_item->initFromInstId(fsi.army_inst_id[_sel_index]);
		_item->setTag(fsi.army_inst_id[_sel_index]);
		

		LinearLayoutParameter* llp = LinearLayoutParameter::create();
		_item->setLayoutParameter(llp);
		llp->setGravity(LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
		llp->setMargin(Margin(5.0f, 7.0f, 0.0f, 7.0f));


		// 点击事件
		_item->setTouchEnabled(true);
		_item->addTouchEventListener(CC_CALLBACK_2(StageArmySel::armyCardCancelTouchEvent,this));


		lv_armys_sel->addChild(_item);

	}while(false);
}

void StageArmySel::armyCardCancelTouchEvent( Ref *pSender, Widget::TouchEventType type )
{
	auto _item = (HeroItem*)pSender;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			int cur_inst_id = _item->getTag();

			auto pl_army_seled = m_layout->getChildByName("pl_army_seled");
			if (!pl_army_seled)
			{
				return;
			}

			auto pl_army_sel_root = pl_army_seled->getChildByName("pl_army_sel_root");
			if (!pl_army_sel_root)
			{
				return;
			}

			auto lv_armys_sel = (ListView*)pl_army_sel_root->getChildByName("lv_armys_sel");
			if (!lv_armys_sel)
			{
				return;
			}

			auto lp = LocalPlayer::getInstance();
			tTempFightInfo& fsi = lp->m_temp_fight_info;

			if(fsi.removeArmyId(cur_inst_id))
			{
				lv_armys_sel->removeChild(_item);
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}



void StageArmySel::heroCardCancelTouchEvent( Ref *pSender, Widget::TouchEventType type )
{
	auto _item = (HeroItem*)pSender;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			int cur_inst_id = _item->getTag();
			
			auto lp = LocalPlayer::getInstance();
			tTempFightInfo& fsi = lp->m_temp_fight_info;


			if(fsi.army_inst_id[tTempFightInfo::ARMY_HERO_INDEX] == 0)
			{
				CCLOG("hero has not been selected");
				return;
			}

			fsi.army_inst_id[tTempFightInfo::ARMY_HERO_INDEX] = 0;

			_item->removeFromParent();
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

}
