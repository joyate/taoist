#include "RewardShow.h"
#include "../GameDefine.h"
#include "../game_ui/Card.h"
#include "../data/MsgManager.h"

RewardShow::RewardShow(void):
	m_type(0),
	m_item_id(0)
{
}


RewardShow::~RewardShow(void)
{
}



bool RewardShow::init()
{
	if (!LayerColor::initWithColor(Color4B(0,0,0,220)))
	{
		return false;
	}


	// ±³¾°
	Size win_size = Director::getInstance()->getWinSize();
	auto bg = Sprite::create("Common/149.png");
	bg->setPosition(Vec2(win_size.width/2,win_size.height/2));
	this->addChild(bg);

	bg->runAction(RepeatForever::create(RotateBy::create(12.0f,360)));


	// title
	auto title = MsgManager::getInstance().getMsg(MsgManager::TIPS_HERO_REWARD_TITLE);
	if (title)
	{
		TTFConfig ttf;
		ttf.fontFilePath = "fzyh.ttf";
		ttf.fontSize = 28;
		auto lb_title = Label::createWithTTF(ttf,title);

		lb_title->setPosition(Vec2(win_size.width/2,win_size.height*0.85f));
		this->addChild(lb_title);
	}

	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(RewardShow::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}




void RewardShow::initReward(int rw_type, int _temp_item_id )
{
	auto _item = (Widget*)createWidget(rw_type);
	if (_item)
	{
		Size win_size = Director::getInstance()->getWinSize();

		_item->setTag(_temp_item_id);
		_item->setPosition(Vec2(win_size.width/2,win_size.height/2));
		this->addChild(_item);

		m_type = rw_type;
		m_item_id = _temp_item_id;
		
		_item->setScale(0.1f);
		_item->runAction(Spawn::create(ScaleTo::create(1.0f,1),RotateTo::create(1.0f,720),nullptr));

		_item->setTouchEnabled(true);
		_item->addTouchEventListener(CC_CALLBACK_2(RewardShow::touchEvent,this));
	}
}



bool RewardShow::onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* event )
{
	auto _item = this->getChildByTag(m_item_id);
	if (!_item)
	{
		CCLOG("item pointer null");
		return true;
	}


	_item->runAction(Sequence::create(
		Spawn::create(MoveTo::create(0.5f,Vec2(795,50)),ScaleTo::create(0.5f,0.1f),nullptr),
		 CallFunc::create( CC_CALLBACK_0(RewardShow::callback, this)),
		 nullptr
		));

	return true;
}


Widget* RewardShow::createWidget( int _type )
{
	Widget* ret = nullptr;
	switch (_type)
	{
	case RS_TYPE_CARD:
		ret = UICard::create();
		break;
	default:
		break;
	}

	return ret;
}

void RewardShow::callback()
{
	// main UI update event
	GameDefine::sttCustomEvent ce;
	ce.ce_type = GameDefine::sttCustomEvent::CE_MAIN_UI_UDPATE;
	ce._val[0] = 0;
	_eventDispatcher->dispatchCustomEvent(GameDefine::MAIN_UI_UPDATE_EVENT,&ce);

	this->removeFromParent();
}



void RewardShow::touchEvent( Ref *pSender, Widget::TouchEventType type )
{
	auto _item = (Widget*)pSender;
	if (!_item)
	{
		return;
	}

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			_item->runAction(Sequence::create(
				Spawn::create(MoveTo::create(0.5f,Vec2(795,50)),ScaleTo::create(0.5f,0.1f),nullptr),
				CallFunc::create( CC_CALLBACK_0(RewardShow::callback, this)),
				nullptr
				));
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

}





