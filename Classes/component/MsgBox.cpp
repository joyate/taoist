#include "MsgBox.h"
#include "cocostudio/CocoStudio.h"
#include "VisibleRect.h"
#include "../data/LocalPlayer.h"
#include "../data/GameData.h"

using namespace cocostudio;



MsgBox::MsgBox(void):
	m_node(nullptr)
{
}


MsgBox::~MsgBox(void)
{
}

bool MsgBox::initMsg(int _msg_type_id, int _msg_title_id,int _msg_content_id,bool bModel /*= true*/ )
{
	
	if(!initWithColor(Color4B(0,0,0,180)))
	{
		CCLOG("msgbox initwithcolor failed");
		return false;
	}

	m_type = _msg_type_id;
	m_node = dynamic_cast<ui::Layout*>(GUIReader::getInstance()->widgetFromJsonFile("MsgBox/MsgBox.ExportJson"));
	if (!m_node)
	{
		CCLOG("msg load failed");
		return false;
	}

	m_node->setPosition(VisibleRect::center() - Vec2(m_node->getContentSize()/2));
	addChild(m_node);

#define IMPL_BTN_EVENT(_name)	\
	do{\
	Button* _name = (Button*)Helper::seekWidgetByName(m_node,#_name); \
	_name->addTouchEventListener(CC_CALLBACK_2(MsgBox::touchEvent,this)); \
	}while(0)

	IMPL_BTN_EVENT(btn_ok);
	IMPL_BTN_EVENT(btn_cancel);

	// 内容
	auto msg_info = g_MsgInfoMgr.getObject(_msg_content_id);
	auto msg = (Text*)m_node->getChildByName("msg");
	if (msg_info && msg)
	{
		msg->setString(msg_info->msg);
		msg->setContentSize(Size(400,200));
		msg->setFontName("fzyh.ttf");
		msg->setFontSize(24);
	}

	//
	auto touchListener =  EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(bModel);
	touchListener->onTouchBegan = CC_CALLBACK_2(MsgBox::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	return true; 
}

void MsgBox::touchEvent( Ref *pSender, Widget::TouchEventType type )
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			Button* pObj = (Button*)pSender;

			std::string name = pObj->getName();
			if (name == "btn_cancel")
			{
				this->removeFromParentAndCleanup(true);
			}
			else if(name == "btn_ok")
			{
				// 退出游戏
				if (m_type == MB_TYPE_EXIT_GAME)
				{

					// 保存先
					LocalPlayer::getInstance()->save(GameDefine::ROLE_SAVE_FILE);

					//通知导演结束游戏
					CCDirector::getInstance()->end();
					//判断当当前平台为ios平台时，退出程序（ios平台较为特殊，程序只有使用exit(0);方法才能控制程序的结束）
#if (CC_TARGET_PLATFORM== CC_PLATFORM_IOS)
					exit(0);
#endif
				}
				else if(m_type == MB_TYPE_TIP)
				{




					this->removeFromParent();
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
