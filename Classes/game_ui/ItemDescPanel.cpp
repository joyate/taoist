#include "ItemDescPanel.h"
#include "cocostudio/CocoStudio.h"
#include "../data/LocalPlayer.h"
#include "../data/GameData.h"
#include "../utility/Utility.h"

using namespace cocostudio;



ItemDescPanel::ItemDescPanel(void)
{
}


ItemDescPanel::~ItemDescPanel(void)
{
}

bool ItemDescPanel::init()
{
	if (!Widget::init())
	{
		return false;
	}

	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("ItemDescPanel/ItemDescPanel.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);


	Utility::registerTouchEvent(m_layout,"Panel_2/btn_sell",CC_CALLBACK_2(ItemDescPanel::touchEvent,this));
	Utility::registerTouchEvent(m_layout,"Panel_2/btn_detail",CC_CALLBACK_2(ItemDescPanel::touchEvent,this));


	return true;
}

void ItemDescPanel::touchEvent( Ref *pSender, Widget::TouchEventType type )
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
			if (btn->getName() == "btn_sell")
			{

			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}



void ItemDescPanel::initFromInstItemId( int _id )
{

}
