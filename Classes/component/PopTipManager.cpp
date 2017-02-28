#include "PopTipManager.h"
#include "../data/MsgManager.h"


PopTipManager* PopTipManager::s_ptMgr = nullptr;


PopTipManager::PopTipManager(void)
{
}


PopTipManager::~PopTipManager(void)
{
}

PopTipManager* PopTipManager::getInstance()
{
	if (!s_ptMgr)
	{
		s_ptMgr = new PopTipManager;
	}

	return s_ptMgr;
}


void PopTipManager::popTips( int _tid )
{

	auto msg = MsgManager::getInstance().getMsg(_tid);
	if (!msg)
	{
		CCLOG("msg id %d has no data",_tid);
		return;
	}

	Size win_size = Director::getInstance()->getWinSize();


	TTFConfig ttf;
	ttf.fontFilePath = "fzyh.ttf";
	ttf.fontSize = POP_TIPS_FONT_SIZE;
	auto tips = Label::create();
	tips->setTTFConfig(ttf);
	//tips->setDimensions(win_size.width*0.7,0);
	tips->setString(msg);

	// 要参考上一次
	float y_pos = win_size.height/2;
	if (!m_tips.empty())
	{
		Label* last_tips = m_tips.back();
		if (last_tips)
		{
			y_pos = last_tips->getPosition().y - last_tips->getContentSize().height/2 - tips->getContentSize().height/2;
		}
	}

	tips->setPosition(Vec2(win_size.width/2,y_pos));

	auto scene = Director::getInstance()->getRunningScene();
	if (scene)
	{
		tips->runAction(Sequence::create(DelayTime::create(0.3f),
			Spawn::create(MoveBy::create(0.5f,Vec2(0,POP_TIPS_MOVE_UP_SIZE)),FadeOut::create(0.5f),nullptr),
			CallFuncN::create( CC_CALLBACK_1(PopTipManager::deadCallback, this)),nullptr));
		scene->addChild(tips);

		m_tips.pushBack(tips);
	}
}



void PopTipManager::deadCallback( Node* sender )
{
	auto tips = (Label*)sender;

	tips->removeFromParent();
	m_tips.eraseObject(tips);
}


