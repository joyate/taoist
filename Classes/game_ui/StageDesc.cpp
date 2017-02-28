#include "StageDesc.h"
#include "cocostudio/CocoStudio.h"
#include "UICopySelect.h"
#include "../utility/StackLayerMgr.h"
#include "../frame/LoadingScene.h"
#include "../data/GameData.h"
#include "Item.h"
#include "../data/LocalPlayer.h"
#include "../component/GuideLayer.h"
#include "../game_ui/CardTip.h"

using namespace cocostudio;




StageDesc::StageDesc(void):
	m_fe_type(GameDefine::CAT_METAL),
	m_army_type(ST_HERO),
	m_last_zorder(TOP_IMG_BTN_LAYER),
	m_cur_step(SST_COPY_DESC)
{
}


StageDesc::~StageDesc(void)
{
}



bool StageDesc::init()
{
	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("StageDesc/StageDesc.json");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);



#ifndef IMPL_BTN_EVENT
#define IMPL_BTN_EVENT(_root,_name)	\
	do{\
	Button* btn = (Button*)Helper::seekWidgetByName(_root,#_name); \
	btn->addTouchEventListener(CC_CALLBACK_2(StageDesc::btnTouchEvent,this)); \
	}while(0)


	auto pv = (PageView*)m_layout->getChildByName("pv_stage");
	if (pv)
	{
		auto panel = (Widget*)pv->getChildByName("pl_stage_sel");
		IMPL_BTN_EVENT(panel,btn_fight);

#ifndef IMPL_IMAGE_EVENT
#define IMPL_IMAGE_EVENT(root,_name)	\
	do{\
	Widget* _name = (Widget*)Helper::seekWidgetByName(root,#_name);		\
	_name->setTouchEnabled(true);											\
	_name->addTouchEventListener(CC_CALLBACK_2(StageDesc::imgTouchEvent,this)); \
	}while(0)

		//
		IMPL_IMAGE_EVENT(panel,img_wx_1);

		Widget* img_wx_1 = (Widget*)Helper::seekWidgetByName(panel,"img_wx_1");
		m_last_zorder = img_wx_1->getLocalZOrder();
		m_last_img_btn_name = img_wx_1->getName();

		IMPL_IMAGE_EVENT(panel,img_wx_2);
		IMPL_IMAGE_EVENT(panel,img_wx_3);
		IMPL_IMAGE_EVENT(panel,img_wx_4);
		IMPL_IMAGE_EVENT(panel,img_wx_5);

		//
		IMPL_IMAGE_EVENT(panel,img_hero_sel);
		IMPL_IMAGE_EVENT(panel,img_army_sel);

		m_last_amry_type_name = "img_hero_sel";

#undef IMPL_IMAGE_EVENT
#endif

		pv->addEventListener(CC_CALLBACK_2(StageDesc::pageViewEvent, this));

	}

	IMPL_BTN_EVENT(m_layout,btn_close);
	IMPL_BTN_EVENT(m_layout,btn_next);
	IMPL_BTN_EVENT(m_layout,btn_last);

#undef IMPL_BTN_EVENT
#endif


	updateItem(m_army_type,m_fe_type);
	LocalPlayer::getInstance()->m_temp_fight_info.reset();

	return true;
}



void StageDesc::btnTouchEvent( Ref *pSender, Widget::TouchEventType type )
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
			if (btn->getName() == "btn_close")
			{
				//this->removeFromParent();
				// 对应StageItem进入
				StackLayerMgr::getInstance()->popLayer();
			}
			else if(btn->getName() == "btn_next")
			{
				if(m_cur_step + 1 < SST_MAX)
				{
					auto pv_stage = (PageView*)m_layout->getChildByName("pv_stage");
					pv_stage->scrollToPage(++m_cur_step);
				}	
			}
			else if(btn->getName() == "btn_last")
			{
				if(m_cur_step - 1 >= 0)
				{
					auto pv_stage = (PageView*)m_layout->getChildByName("pv_stage");
					pv_stage->scrollToPage(--m_cur_step);
				}		
			}
			else if(btn->getName() == "btn_fight")
			{

				//StackLayerMgr::getInstance()->endStackLayer();
				const auto& fi = LocalPlayer::getInstance()->m_temp_fight_info;
				if (fi.army_inst_id[GameDefine::tTempFightInfo::ARMY_HERO_INDEX] == 0)
				{
					CCLOG("hero not selected");
					return;
				}


				const auto& stage_info = g_StageInfoMgr.getObject(this->getTag());
				if (!stage_info)
				{
					CCLOG("stage id %d no data",this->getTag());
					return;
				}

				auto& ba = LocalPlayer::getInstance()->m_base_attr;
				int phys_val = ba.m_data[GameDefine::tBaseAttr::BA_PHYSICAL];
				if (phys_val < stage_info->phys_cost)
				{
					CCLOG("phys not enough");
					return;
				}

				ba.m_data[GameDefine::tBaseAttr::BA_PHYSICAL] -= stage_info->phys_cost;

				// 选将阶段
				auto loading = LoadingScene::create();
				Director::getInstance()->pushScene(loading);
			}

		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}



bool StageDesc::initFromStageId( int stage_id )
{
	auto stage_info = g_StageInfoMgr.getObject(stage_id);
	
	if (!stage_info)
	{
		CCLOG("stage id %d no stage info",stage_id);
		return false;
	}

	
	auto pv_stage = m_layout->getChildByName("pv_stage");
	auto pl_stage_desc = pv_stage->getChildByName("pl_stage_desc");

	if (!pl_stage_desc)
	{
		CCLOG("page pl_stage_desc not found");
		return false;
	}

	LocalPlayer::getInstance()->m_temp_fight_info.curr_stage_id = stage_id;
	auto pl_evil = pl_stage_desc->getChildByName("pl_evil");
	auto lv_evil = (ListView*)pl_evil->getChildByName("lv_evil");

	if (lv_evil)
	{
		// 设置防守怪
		for (int i = 0; i < stage_info->monsters[0]; i++)
		{
			auto monster_info = g_ItemInfoMgr.getObject(stage_info->monsters[i+1]);
			if (monster_info)
			{
				auto item = Item::create();
				item->initFromItemTempId(monster_info->id);
				item->setTag(monster_info->id);

				item->setTouchEnabled(true);
				item->addTouchEventListener(CC_CALLBACK_2(StageDesc::showDetailTip,this));

				lv_evil->addChild(item);
			}	
		}


		// 设置掉落
		auto pl_drop = pl_stage_desc->getChildByName("pl_drop");
		auto lv_drop = (ListView*)pl_drop->getChildByName("lv_drop");
		for (int i = 0; i < stage_info->drops[0]; i++)
		{
			auto item_info = g_ItemInfoMgr.getObject(stage_info->drops[i+1]);
			if (item_info)
			{
				auto item = Item::create();
				item->initFromItemTempId(item_info->id);

				lv_drop->addChild(item);
			}

		}
	}


	// 消耗
	auto label_phys_cost = (TextBMFont*)pl_stage_desc->getChildByName("label_phys_cost");
	if (label_phys_cost)
	{
		label_phys_cost->setString(StringUtils::format("%d",stage_info->phys_cost));
	}

	return true;
}





void StageDesc::imgTouchEvent( Ref *pSender, Widget::TouchEventType type )
{
	auto img = (ImageView*)pSender;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			// 处理五行按钮事件
			if (!img->getName().compare(0,7,"img_wx_"))
			{
				if (img->getName().compare(m_last_img_btn_name) != 0)
				{
					if(img->getLocalZOrder() != m_last_zorder)
					{
						std::string img_path = StringUtils::format("StageDesc/%s_hl.png",img->getName().c_str());
						img->loadTexture(img_path);
						m_fe_type = img->getTag() - WX_BASE_TAG;

						auto last_img_btn = (ImageView*)img->getParent()->getChildByName(m_last_img_btn_name);
						if (last_img_btn)
						{
							std::string last_img_path = StringUtils::format("StageDesc/%s.png",m_last_img_btn_name.c_str());
							last_img_btn->loadTexture(last_img_path);
							last_img_btn->setLocalZOrder(m_last_zorder);
						}

						m_last_img_btn_name = img->getName();
						m_last_zorder = img->getLocalZOrder();
						img->setLocalZOrder(TOP_IMG_BTN_LAYER);

						updateItem(m_army_type,m_fe_type);
					}
				}
			}
			else
			{
				// 兵种选择类型
				if ( img->getName().compare(m_last_amry_type_name) != 0)
				{

					auto last_img_btn = (ImageView*)img->getParent()->getChildByName(m_last_amry_type_name);
					if (last_img_btn)
					{

						// 小兵
						if(!m_last_amry_type_name.compare(0,8,"img_hero"))
						{
							img->loadTexture("StageDesc/70D.png");
							last_img_btn->loadTexture("StageDesc/70A.png");
							m_army_type = ST_ARMY;
						}
						else
						{
							img->loadTexture("StageDesc/70B.png");
							last_img_btn->loadTexture("StageDesc/70C.png");
							m_army_type = ST_HERO;
						}
						
						// 交换Z
						int cur_z_order = img->getLocalZOrder();
						img->setLocalZOrder(last_img_btn->getLocalZOrder());
						last_img_btn->setLocalZOrder(cur_z_order);
						
						//
						m_last_amry_type_name = img->getName();
						
						updateItem(m_army_type,m_fe_type);
					}
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

void StageDesc::updateItem( int army_type,int wx_type )
{

	auto pv_stage = m_layout->getChildByName("pv_stage");
	auto pl_stage_sel = (Widget*)pv_stage->getChildByName("pl_stage_sel");

	if(!pl_stage_sel)
	{
		CCLOG("page pl_stage_sel not found");
		return;
	}

	auto lp = LocalPlayer::getInstance();
	const GameDefine::tBagInfo& bagInfo = lp->m_bag.getBagInfo();

	
	auto pl_heros = Helper::seekWidgetByName(pl_stage_sel,"pl_heros");
	auto lv_heros = (ListView*)Helper::seekWidgetByName(pl_heros,"lv_heros");
	lv_heros->removeAllItems();
	lv_heros->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(StageDesc::selectedItemEvent, this));
	//
	for (auto _iter = bagInfo.m_items.begin();
			_iter != bagInfo.m_items.end();
		)
	{

		auto layout = Layout::create();
		layout->setLayoutType(LayoutType::HORIZONTAL);
		layout->setClippingEnabled(true);
		layout->setContentSize(Size(400, 100));
		lv_heros->addChild(layout);

		for (int i = 0; i < BAG_ITEM_COL_MAX, _iter != bagInfo.m_items.end(); i++, _iter++)
		{
			// 物品类型过滤
			auto item_info = g_ItemInfoMgr.getObject(_iter->second->item_temp_id);
			if (!item_info || item_info->item_type != IT_CARD)
			{
				continue;
			}

			// 卡牌类型、五行过滤
			auto card_info = static_cast<cfg_Card*>(item_info);
			if (card_info->arm_type != army_type || card_info->cat != wx_type)
			{
				continue;
			}


			auto _item = Item::create();
			_item->initFromItemId(_iter->second->item_id);
			_item->setTag(_iter->second->item_id);

			_item->setLocalZOrder(lv_heros->getLocalZOrder()+1);
			_item->setTouchEnabled(true);
			_item->addTouchEventListener(CC_CALLBACK_2(StageDesc::cardTouchEvent,this));
			//_item->setStarLvl(_iter->second->)

			layout->addChild(_item);
		}

	}


}

void StageDesc::cardTouchEvent( Ref *pSender, Widget::TouchEventType type )
{
	auto item = (Item*)pSender;

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

			int sel_index = -1;
			
			auto inst_item_info = lp->m_bag.getItemById(cur_inst_item_id);
			auto cfg_item_info = (cfg_Card*)g_ItemInfoMgr.getObject(inst_item_info->item_temp_id);

			if (cfg_item_info->arm_type == AT_ARMY_HERO)
			{
				if(fsi.army_inst_id[tTempFightInfo::ARMY_HERO_INDEX] == 0)
				{
					fsi.army_inst_id[tTempFightInfo::ARMY_HERO_INDEX] = cur_inst_item_id;
					sel_index = tTempFightInfo::ARMY_HERO_INDEX;
				}
			}
			else
			{
				sel_index = fsi.addArmyId(cur_inst_item_id);
			}
						
			// 刷新
			if(sel_index >= 0)
				updateSelectedItem(sel_index);
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
	
}

void StageDesc::selectedItemEvent( Ref* pSender, ListView::EventType type )
{
	switch (type)
	{
	case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
		{
			ListView* listView = static_cast<ListView*>(pSender);
			CC_UNUSED_PARAM(listView); 
			CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
			break;
		}
	case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
		{
			ListView* listView = static_cast<ListView*>(pSender);
			CC_UNUSED_PARAM(listView);
			CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
			break;
		}
	default:
		break;
	}
}

void StageDesc::updateSelectedItem(int _sel_index)
{

	auto pv_stage = m_layout->getChildByName("pv_stage");
	auto pl_stage_sel = (Widget*)pv_stage->getChildByName("pl_stage_sel");

	if(!pl_stage_sel)
	{
		CCLOG("page pl_stage_sel not found");
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

		std::string node_name;
		if (_sel_index == tTempFightInfo::ARMY_HERO_INDEX)
		{
			node_name = "img_hero_pic";
		}
		else
		{
			node_name = StringUtils::format("img_army_%d",_sel_index);
		}

		auto img_item = (ImageView*)Helper::seekWidgetByName(pl_stage_sel,node_name);
		if (!img_item)
		{
			CCLOG("stage desc can't found %s widget",node_name.c_str());
			break;
		}


		auto _item = Item::create();
		_item->initFromItemId(fsi.army_inst_id[_sel_index]);
		_item->setTag(fsi.army_inst_id[_sel_index]);
		_item->setPosition(Vec2(img_item->getContentSize().width/2,img_item->getContentSize().height/2));

		// 点击事件
		_item->setTouchEnabled(true);
		_item->addTouchEventListener(CC_CALLBACK_2(StageDesc::cardSelCancelTouchEvent,this));
		

		img_item->addChild(_item);

	}while(false);
}

void StageDesc::cardSelCancelTouchEvent( Ref *pSender, Widget::TouchEventType type )
{
	auto _item = (Item*)pSender;
	int _cur_select_item_id = _item->getTag();

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

			if(fsi.removeArmyId(_cur_select_item_id))
			{
				_item->removeFromParent();
				//updateSelectedItem();
			}
			
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void StageDesc::pageViewEvent( Ref *pSender, PageView::EventType type )
{
	switch (type)
	{
	case PageView::EventType::TURNING:
		{
			PageView* pageView = dynamic_cast<PageView*>(pSender);
			auto gl = (GuideLayer*)Director::getInstance()->getRunningScene()->getChildByTag(GuideLayer::TAG_GUIDE_NODE);
			if (gl && pageView->getCurPageIndex() > 0)
			{
				gl->nextStep(GameDefine::cfg_Guide_Info::GEM_DONE);
			}
		}
		break;

	default:
		break;
	}
}


void StageDesc::showDetailTip( Ref *pSender, Widget::TouchEventType type )
{
	auto _item = (Item*)pSender;
	int _item_id = _item->getTag();

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		{
			auto card_tip = CardTip::create();
			card_tip->initFrom(_item_id);
			card_tip->setTag(TAG_TIP_NODE);

			Vec2 item_pos = _item->convertToWorldSpace(Vec2(0,0));
			Vec2 pos = this->convertToNodeSpace(item_pos);
			card_tip->setPosition(pos + Vec2(_item->getContentSize().width/2 + card_tip->getContentSize().width/2,-(card_tip->getContentSize().height/3)));

			this->addChild(card_tip);
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			auto card_tip = (CardTip*)this->getChildByTag(TAG_TIP_NODE);
			if (card_tip)
			{
				card_tip->removeFromParent();
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		{
			auto card_tip = (CardTip*)this->getChildByTag(TAG_TIP_NODE);
			if (card_tip)
			{
				card_tip->removeFromParent();
			}
		}
		break;
	default:
		break;
	}

}
