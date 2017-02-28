#include "ReinforcePanel.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"
#include "../data/LocalPlayer.h"

using namespace cocostudio;


ReinforcePanel::ReinforcePanel(void):
	m_layout(nullptr)
{
}


ReinforcePanel::~ReinforcePanel(void)
{
}


bool ReinforcePanel::init()
{

	if (!Widget::init())
	{
		return false;
	}


	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("ReinforcePanel/ReinforcePanel.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);


#ifndef IMPL_BTN_EVENT
#define IMPL_BTN_EVENT(root,_name)	\
	do{\
	Button* btn = (Button*)Helper::seekWidgetByName(root,#_name); \
	btn->addTouchEventListener(CC_CALLBACK_2(ReinforcePanel::touchEvent,this)); \
	}while(0)



	auto _panel_root = (Layout*)m_layout->getChildByName("pl_info_root");
	if (!_panel_root)
	{
		return false;
	}


	IMPL_BTN_EVENT(_panel_root,btn_equip_sel);
	IMPL_BTN_EVENT(_panel_root,btn_hero_sel);
	IMPL_BTN_EVENT(_panel_root,btn_reinforce);
	IMPL_BTN_EVENT(m_layout,btn_close);


#endif

	return true;
}




void ReinforcePanel::touchEvent( Ref *pSender, Widget::TouchEventType type )
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
