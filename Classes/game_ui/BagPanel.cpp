#include "BagPanel.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"
#include "../data/LocalPlayer.h"
#include "Item.h"
#include "../component/GuideFilterMgr.h"

using namespace cocostudio;

BagPanel::BagPanel(void)
{
}


BagPanel::~BagPanel(void)
{
}


bool BagPanel::init()
{
	if (!Widget::init())
	{
		return false;
	}

	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("BagPanel/BagPanel.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);


#define IMPL_BTN_EVENT(root,_name)	\
	do{\
	Button* btn = (Button*)Helper::seekWidgetByName(root,#_name); \
	btn->addTouchEventListener(CC_CALLBACK_2(BagPanel::touchEvent,this)); \
	}while(0)

	//
	IMPL_BTN_EVENT(m_layout,btn_close);

	return true;
}




void BagPanel::touchEvent( Ref *pSender, Widget::TouchEventType type )
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
				GuideFilterMgr::getInstance().checkGuideFilter(GuideFilterMgr::GFN_BATTLE_PRATICE);
				this->removeFromParent();
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}



void BagPanel::initFromPlayer()
{
	auto& bagInfo = LocalPlayer::getInstance()->m_bag.getBagInfo();
	if (bagInfo.m_items.empty())
	{
		return;
	}


	auto pl_main = m_layout->getChildByName("pl_main");
	auto lv_items = (ListView*)pl_main->getChildByName("lv_items");
	if (!lv_items)
	{
		CCLOG("bag panel element %s not found",lv_items);
		return;
	}



	int cnt = 0;
	Layout* lo_line = nullptr;

	for (auto _iter : bagInfo.m_items)
	{

		// ¹ýÂË×°±¸
		auto cfg_item_info = g_ItemInfoMgr.getObject(_iter.second->item_temp_id);
		if (!cfg_item_info || cfg_item_info->item_type == GameDefine::IT_CARD)
		{
			continue;
		}

		if (cnt%ONELINE_ITEM_CNT_MAX == 0)
		{
			lo_line = Layout::create();
			lo_line->setLayoutType(Layout::Type::HORIZONTAL);
			lo_line->setContentSize(Size(770,110));


			auto llp = LinearLayoutParameter::create();
			llp->setGravity(LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
			llp->setMargin(Margin(5,3,5,3));

			lo_line->setLayoutParameter(llp);

			lv_items->addChild(lo_line);
		}


		auto item = UIItem::create();
		item->initFromItemId(_iter.first);
		item->setTag(_iter.first);
		item->setTouchEnabled(true);
		item->addTouchEventListener(CC_CALLBACK_2(BagPanel::itemTouchEvent,this));
		lo_line->addChild(item);
		cnt++;
	}

}

void BagPanel::itemTouchEvent( Ref *pSender, Widget::TouchEventType type )
{

	auto item = (UIItem*)pSender;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			int inst_item_id = item->getTag();

			CCLOG("touch item id %d",inst_item_id);
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

