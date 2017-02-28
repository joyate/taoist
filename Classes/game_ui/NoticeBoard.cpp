#include "NoticeBoard.h"
#include "cocostudio/CocoStudio.h"
#include "../component/GuideFilterMgr.h"
#include "../data/LocalPlayer.h"
#include "../data/MsgManager.h"

using namespace cocostudio;


NoticeBoard::NoticeBoard(void)
{

}


NoticeBoard::~NoticeBoard(void)
{
}

bool NoticeBoard::init()
{
	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("NoticeBoard/NoticeBoard.ExportJson");
	this->addChild(m_layout);
	m_layout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);


#define IMPL_BTN_EVENT(_name)	\
	do{\
	Button* _name = (Button*)Helper::seekWidgetByName(m_layout,#_name); \
	_name->addTouchEventListener(CC_CALLBACK_2(NoticeBoard::touchEvent,this)); \
	}while(0)


	IMPL_BTN_EVENT(btn_ok);

	//
	addString(MsgManager::getInstance().getMsg(NB_CONTENT_ID));

	return true;
}




void NoticeBoard::touchEvent( Ref *pSender, Widget::TouchEventType type )
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			LocalPlayer::getInstance()->touchTaskTrigger(TaskTrigger::TT_FIRST_ENTER_GAME);
			// ËÍÓ¢ÐÛ
			//GuideFilterMgr::getInstance().checkGuideFilter(GuideFilterMgr::GFN_REWARD_HERO);

			this->removeFromParent();
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void NoticeBoard::changeTitle( const std::string& _title_png )
{

}

void NoticeBoard::addString( const std::string& _content )
{
	ScrollView* sv = (ScrollView*)Helper::seekWidgetByName(m_layout,"sv_content");

	if (!sv)
	{
		CCLOG("notice-board has no scroll view");
		return;
	}

	auto text = Text::create(_content,"fzyh.ttf",20);
	text->setTextAreaSize(Size(390,0));
	text->setColor(Color3B(0,64,0));

	//Size txt_size = text->getContentSize();

	sv->addChild(text);
}
