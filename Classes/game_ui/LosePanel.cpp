#include "LosePanel.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"
#include "../data/LocalPlayer.h"

using namespace cocostudio;



LosePanel::LosePanel(void)
{
}


LosePanel::~LosePanel(void)
{
}


bool LosePanel::init()
{
	if (!LayerColor::initWithColor(Color4B(33,33,33,222)))
	{
		return false;
	}

	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("LostPanel/LostPanel.ExportJson");
	this->addChild(m_layout);


#ifndef IMPL_BUTTON_EVENT
#define IMPL_BUTTON_EVENT(root,_name)										\
	do{																		\
	Widget* _wg = (Widget*)Helper::seekWidgetByName(root,#_name);			\
	_wg->setTouchEnabled(true);												\
	_wg->addTouchEventListener(CC_CALLBACK_2(LosePanel::touchEvent,this));	\
	}while(0)


	IMPL_BUTTON_EVENT(m_layout,btn_close);


#undef IMPL_BUTTON_EVENT
#endif


	auto lb_desc = (Text*)m_layout->getChildByName("lb_desc");
	if (lb_desc)
	{
		lb_desc->setFontName("fzyh.ttf");
	}
	



	return true;
}

void LosePanel::touchEvent( Ref *pSender, Widget::TouchEventType type )
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
				Director::getInstance()->popScene();
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
