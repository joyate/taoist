#include "GameWorldMap.h"
#include "cocostudio/CocoStudio.h"
#include "UICopySelect.h"
#include "../utility/StackLayerMgr.h"

using namespace cocostudio;

GameWorldMap::GameWorldMap(void)
{
}


GameWorldMap::~GameWorldMap(void)
{
}



bool GameWorldMap::init()
{
	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("WorldMap/WorldMap.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);


#ifndef IMPL_BTN_EVENT
#define IMPL_BTN_EVENT(_name)	\
	do{\
	Button* _name = (Button*)Helper::seekWidgetByName(m_layout,#_name); \
	_name->addTouchEventListener(CC_CALLBACK_2(GameWorldMap::touchEvent,this)); \
	}while(0)


	IMPL_BTN_EVENT(btn_close);
	IMPL_BTN_EVENT(btn_jz);

	// 用于上层辨识
	this->setTag(TAG_GAME_WORLD_MAP);

#undef IMPL_BTN_EVENT
#endif

	return true;
}

void GameWorldMap::touchEvent( Ref *pSender, Widget::TouchEventType type )
{
	Size win_size = Director::getInstance()->getWinSize();
	auto btn = (Button*)pSender;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			// 退出
			if (btn->getName() == "btn_close")
			{

				// 对应GameMain进入
				StackLayerMgr::getInstance()->popLayer();
				// 对应GameMain新建StackLayer
				//StackLayerMgr::getInstance()->endStackLayer();
				//this->removeFromParent();
			}
			else if(btn->getName() == "btn_jz")		// 剑冢
			{
				auto cs = UICopySelect::create();
				cs->setPosition(Vec2(win_size.width - cs->getContentSize().width,win_size.height - cs->getContentSize().height)/2);
				cs->setTag(UICopySelect::TAG_OWNER_LAYER);
				this->getParent()->addChild(cs);
				
				cs->applyCopyInfoWithRoleData(101);

				//		
				StackLayerMgr::getInstance()->pushLayer(cs);			
				//this->removeFromParent();
			}

		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
