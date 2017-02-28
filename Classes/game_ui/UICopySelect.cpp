#include "UICopySelect.h"
#include "cocostudio/CocoStudio.h"
#include "StageItem.h"
#include "Card.h"
#include "CopyShopItem.h"
#include "../utility/StackLayerMgr.h"
#include "../data/LocalPlayer.h"
#include "../data/GameData.h"
#include "../component/TimeManager.h"
#include "../data/MsgManager.h"
#include "../utility/Utility.h"


using namespace cocostudio;


UICopySelect::UICopySelect(void):
	m_cur_page_index(CS_COPY),
	m_layout(nullptr),
	m_copy_id(0)
{
}


UICopySelect::~UICopySelect(void)
{
}

bool UICopySelect::init()
{
	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("CopySelect/CopySelect.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);

#ifndef IMPL_IMAGE_EVENT
#define IMPL_IMAGE_EVENT(_root,_name)	\
	do{																					\
	Widget* _widget = (Widget*)Helper::seekWidgetByName(_root,#_name);					\
	_widget->setTouchEnabled(true);														\
	_widget->addTouchEventListener(CC_CALLBACK_2(UICopySelect::touchEvent,this));			\
	}while(0)

	
	auto pl_root = (Widget*)m_layout->getChildByName("pl_root");
	if (!pl_root)
	{
		return false;
	}

	IMPL_IMAGE_EVENT(pl_root,img_btn_stage);
	IMPL_IMAGE_EVENT(pl_root,img_btn_exchange);
	IMPL_IMAGE_EVENT(pl_root,img_btn_shop);
	
#undef IMPL_IMAGE_EVENT
#endif


#ifndef IMPL_BTN_EVENT
#define IMPL_BTN_EVENT(_name)	\
	do{																					\
	Widget* _widget = (Widget*)Helper::seekWidgetByName(m_layout,#_name);				\
	_widget->addTouchEventListener(CC_CALLBACK_2(UICopySelect::btnTouchEvent,this));	\
	}while(0)


	IMPL_BTN_EVENT(btn_close);

#undef IMPL_BTN_EVENT
#endif


	scheduleUpdate();

	return true;
}

void UICopySelect::touchEvent( Ref *pSender, Widget::TouchEventType type )
{
	auto img_btn = (ImageView*)pSender;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			int new_index = CS_COPY;
			if (img_btn->getName() == "img_btn_stage" )
			{
				img_btn->loadTexture("ui_copy_act.png",Widget::TextureResType::PLIST);
				new_index = CS_COPY;
			}
			else if(img_btn->getName() == "img_btn_exchange" )
			{
				img_btn->loadTexture("CopySelect/ui_exchange_act.png");
				new_index =  CS_HERO;
			}
			else if(img_btn->getName() == "img_btn_shop")
			{
				img_btn->loadTexture("CopySelect/ui_shop_act.png");
				new_index = CS_SHOP;
			}

			if(new_index != m_cur_page_index)
			{
				updatePageView(new_index);
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

bool UICopySelect::initCopySelect(int _copy_id)
{
	if (!m_layout)
	{
		return false;
	}


	auto panel_copy = (Widget*)Helper::seekWidgetByName(m_layout,"pl_copy");
	if (!panel_copy)
	{
		CCLOG("panel copy not found");
		return false;
	}


	auto lv_copy_info = (ListView*)Helper::seekWidgetByName(panel_copy,"lv_copy_info");
	if (!lv_copy_info)
	{
		CCLOG("listview copy not found");
		return false;
	}
	lv_copy_info->setVisible(true);

	// 设置一下间距
	lv_copy_info->setItemsMargin(6.f);

	auto copyInfo = (cfg_Copy*)g_CopyInfoMgr.getObject(_copy_id);
	for (size_t i = 0; i < copyInfo->_stages.size(); i++)
	{
		auto lv_item = StageItem::create();
		lv_item->setTag(copyInfo->_stages[i]);
		
		//
		lv_copy_info->addChild(lv_item);
	
		auto act = MoveBy::create(0.2f,Vec2(60.0f,0));
		lv_item->runAction(EaseBackOut::create(Sequence::create(DelayTime::create(0.1f*(5-i)),act,act->reverse(),nullptr)));
	}

	return true;
}

bool UICopySelect::initHeroSelect(int _copy_id)
{
	if (!m_layout)
	{
		return false;
	}


	auto panel_hero = (Widget*)Helper::seekWidgetByName(m_layout,"pl_hero");
	if (!panel_hero)
	{
		CCLOG("panel copy not found");
		return false;
	}




	auto lv_hero_info = (ListView*)Helper::seekWidgetByName(panel_hero,"lv_hero_info");
	if (!lv_hero_info)
	{
		CCLOG("listview copy not found");
		return false;
	}

	//lv_hero_info->setItemsMargin(12.0f);

	auto layout = Layout::create();
	layout->setLayoutType(LayoutType::HORIZONTAL);
	layout->setContentSize(Size(900,430));

	lv_hero_info->addChild(layout);
	
	auto copyInfo = (cfg_Copy*)g_CopyInfoMgr.getObject(_copy_id);
	for (size_t i = 0; i < copyInfo->_cards.size(); i++)
	{
		auto lv_item = UICard::create();
		lv_item->setTag(copyInfo->_cards[i]);


		auto llp = LinearLayoutParameter::create();
		llp->setGravity(LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
		llp->setMargin(Margin(12,5,2,5));
		lv_item->setLayoutParameter(llp);

		//
		layout->addChild(lv_item);
	}

	return true;
}



bool UICopySelect::initCopyShop(int _copy_id)
{
	if (!m_layout)
	{
		return false;
	}

	auto panel_shop = (Widget*)Helper::seekWidgetByName(m_layout,"pl_shop");
	if (!panel_shop)
	{
		CCLOG("panel copy not found");
		return false;
	}


	auto lv_shop_info = (ListView*)Helper::seekWidgetByName(panel_shop,"lv_shop_info");
	if (!lv_shop_info)
	{
		CCLOG("listview copy not found");
		return false;
	}

	// 先清理下
	lv_shop_info->removeAllChildren();

	auto copyInfo = (cfg_Copy*)g_CopyInfoMgr.getObject(_copy_id);
	int item_size = copyInfo->_shopitems.size();
	int i = 0;


	Layout *layer_item = Layout::create();
	layer_item->setContentSize(Size(lv_shop_info->getContentSize().width,235));
	layer_item->setLayoutType(LayoutType::HORIZONTAL);
	//layer_item->setClippingEnabled(true);
	lv_shop_info->addChild(layer_item);

	
	
	auto& copy_info = LocalPlayer::getInstance()->m_copy_info;
	if (copy_info.m_copy_shop_infos.find(_copy_id) != copy_info.m_copy_shop_infos.end() && 
		!TimeManager::getInstance().checkTimeOver(copy_info.m_copy_shop_infos[_copy_id].last_update_time,SHOP_ITEM_UPDATE_INTERVAL))
	{

		// 取自实际数据
		int show_cnt = copy_info.m_copy_shop_infos[_copy_id]._item_ids.size(); 
		m_left_update_time = SHOP_ITEM_UPDATE_INTERVAL - TimeManager::getInstance().distTimeLength(copy_info.m_copy_shop_infos[_copy_id].last_update_time);

		do 
		{
			for (int j = 0; j < CS_SHOP_COL && i < show_cnt; j++,i++)
			{
				auto item = CopyShopItem::create();
				item->setTouchEnabled(true);
				item->addTouchEventListener(CC_CALLBACK_2(UICopySelect::buyTouchEvent, this));
				item->setBoughtState(copy_info.m_copy_shop_infos[_copy_id].isBought(j));
				item->setItemIndex(j);
				item->setCopyId(m_copy_id);
				item->setTag(copy_info.m_copy_shop_infos[_copy_id]._item_ids[j]);
				layer_item->addChild(item);

			}

		}while(i < show_cnt);

	}
	else // 没有数据或者过期
	{

		// 取自配置表
		int show_cnt = item_size/2; // 只显示一半，仅用于测试
		CC_ASSERT(show_cnt <= item_size);
		m_left_update_time = SHOP_ITEM_UPDATE_INTERVAL;

	
	
		//
		copy_info.m_copy_shop_infos[_copy_id].last_update_time = TimeManager::getInstance().getTime();
		copy_info.m_copy_shop_infos[_copy_id].u_bought_mask = 0;
		copy_info.m_copy_shop_infos[_copy_id]._item_ids.clear();

		do 
		{
			for (int j = 0; j < CS_SHOP_COL && i < show_cnt;)
			{
				float cur = CCRANDOM_0_1();
				if (cur > 1 - copyInfo->_shopitems[i].prob)
				{
					auto item = CopyShopItem::create();
					item->setItemIndex(j);
					item->setCopyId(m_copy_id);
					item->setBoughtState(copy_info.m_copy_shop_infos[_copy_id].isBought(j));
					item->setTouchEnabled(true);
					item->addTouchEventListener(CC_CALLBACK_2(UICopySelect::buyTouchEvent, this));

					// 暂时不启用
					/*LinearLayoutParameter* lp1 = LinearLayoutParameter::create();
					item->setLayoutParameter(lp1);
					lp1->setGravity(LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
					lp1->setMargin(Margin(1.0f, 1.0f, 1.0f, 1.0f));*/

					// 记录下
					copy_info.m_copy_shop_infos[_copy_id]._item_ids.push_back(copyInfo->_shopitems[i].id);

					item->setTag(copyInfo->_shopitems[i].id);
					layer_item->addChild(item);
					
					// 选中物品后，递增
					i++;
					j++;
				}
			}

		}while(i < show_cnt);
	}
		
	return true;
}




void UICopySelect::updatePageView( int _new_page_index )
{

	auto pl_root = m_layout->getChildByName("pl_root");
	if (pl_root)
	{
		switch (m_cur_page_index)
		{
		case UICopySelect::CS_COPY:
			{
				auto btn = (ImageView*)pl_root->getChildByName("img_btn_stage");
				if(btn)
					btn->loadTexture("CopySelect/ui_copy_nor.png");
			}
			break;
		case UICopySelect::CS_HERO:
			{
				auto btn = (ImageView*)pl_root->getChildByName("img_btn_exchange");
				if(btn)
					btn->loadTexture("ui_exchange_nor.png",Widget::TextureResType::PLIST);
			}
			break;
		case UICopySelect::CS_SHOP:
			{
				auto btn = (ImageView*)pl_root->getChildByName("img_btn_shop");
				if(btn)
					btn->loadTexture("ui_shop_nor.png",Widget::TextureResType::PLIST);
			}
			break;
		default:
			break;
		}
	}


	auto panel = (Widget*)Helper::seekWidgetByName(m_layout,"pl_copy");
	if (panel)
	{
		panel->setVisible(_new_page_index == CS_COPY);

		if(_new_page_index == CS_COPY)
		{
			auto img = (ImageView*)Utility::findWidget(m_layout,"pl_root/img_btn_stage");
			if (img)
			{
				img->loadTexture("ui_copy_act.png",Widget::TextureResType::PLIST);
			}
		}
	}

	panel = (Widget*)Helper::seekWidgetByName(m_layout,"pl_hero");
	if (panel)
	{
		panel->setVisible(_new_page_index == CS_HERO);

		if(_new_page_index == CS_HERO)
		{
			auto img = (ImageView*)Utility::findWidget(m_layout,"pl_root/img_btn_exchange");
			if (img)
			{
				img->loadTexture("CopySelect/ui_exchange_act.png");
			}
		}
	}


	panel = (Widget*)Helper::seekWidgetByName(m_layout,"pl_shop");
	if (panel)
	{
		panel->setVisible(_new_page_index == CS_SHOP);

		if(_new_page_index == CS_SHOP)
		{
			auto img = (ImageView*)Utility::findWidget(m_layout,"pl_root/img_btn_shop");
			if (img)
			{
				img->loadTexture("CopySelect/ui_shop_act.png");
			}


			unsigned int now = TimeManager::getInstance().getTime();
			__CCLOGWITHFUNCTION("cur time:%d",now);

		}
	}

	m_cur_page_index = (CS_PAGE_INDEX)_new_page_index;
}

void UICopySelect::btnTouchEvent( Ref *pSender, Widget::TouchEventType type )
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			// 对应GameWorldMap进入
			//this->removeFromParent();
			StackLayerMgr::getInstance()->popLayer();
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void UICopySelect::buyTouchEvent( Ref *pSender, Widget::TouchEventType type )
{

}




bool UICopySelect::applyCopyInfoWithRoleData( int _copy_id)
{
	if (_copy_id <= 0)
	{
		CCLOG("copy id %d invalid",_copy_id);
		return false;
	}

	m_copy_id = _copy_id;


	if (!initCopySelect(_copy_id))
	{
		CCLOG("init copy select failed");
		return false;
	}


	if (!initHeroSelect(_copy_id))
	{
		CCLOG("init hero select failed");
		return false;
	}


	if (!initCopyShop(_copy_id))
	{
		CCLOG("init shop select failed");
		return false;
	}

	// 刷新一下页面
	updatePageView(m_cur_page_index);

	return true;
}




void UICopySelect::update( float delta )
{
	Layer::update(delta);

	// 商店的时候
	if (m_cur_page_index == CS_SHOP && m_left_update_time > 0)
	{
		timeUpdate(delta);
	}
}


void UICopySelect::timeUpdate(float delta)
{
	m_left_update_time -= delta;

	// 时间到了，该刷新了
	if (m_left_update_time <= 0)
	{
		initCopyShop(m_copy_id);
	}
	else
	{
		int hour = (int)m_left_update_time/TimeManager::HOUR_LEN;
		int sec = (int)m_left_update_time%TimeManager::MIN_LEN;
		int min = (int)m_left_update_time%TimeManager::HOUR_LEN/TimeManager::MIN_LEN;

		

		std::string str_time = StringUtils::format(MsgManager::getInstance().getMsg(MsgManager::HMS_TIME_FMT),hour,min,sec);
		auto bg = m_layout->getChildByName("bg");
		if (bg)
		{
			auto pres_ghost_val = bg->getChildByName("pres_ghost_val");
			if (pres_ghost_val)
			{
				auto label_tip = (TextBMFont*)pres_ghost_val->getChildByName("label_tip");
				if (label_tip)
				{
					label_tip->setString(str_time);
				}
			}
		}

	}
}





