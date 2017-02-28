#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "GameMain.h"
#include "VisibleRect.h"
#include "../component/MsgBox.h"
#include "../game_ui/MainUI.h"
// 数据
//#include "../data/GameData.h"
#include "../data/LocalPlayer.h"
#include "../component/GuideFilterMgr.h"
#include "../game_ui/NoticeBoard.h"


using namespace cocostudio;



SceneMain::SceneMain(void)
{
}


SceneMain::~SceneMain(void)
{
}



bool SceneMain::init()
{

	//
	auto map_layer = GameMain::create();
	this->addChild(map_layer,MAP_LAYER,TAG_MAP_LAYER);


	// pop menu root
	auto pop_menu = Node::create();
	this->addChild(pop_menu,POP_MENU,TAG_POP_LAYER);



	auto key_listener = EventListenerKeyboard::create();
	key_listener->onKeyReleased = CC_CALLBACK_2(SceneMain::onKeyReleased, this);


	// 载入存档文件
	std::string path = FileUtils::getInstance()->getWritablePath() + ROLE_SAVE_FILE;
	if (FileUtils::getInstance()->isFileExist(path))
	{
		if(!LocalPlayer::getInstance()->load(GameDefine::ROLE_SAVE_FILE))
		{
			CCLOG("local player load failed: %s",ROLE_SAVE_FILE);
			__CCLOGWITHFUNCTION("local player load failed: %s",ROLE_SAVE_FILE);
			return false;
		}
		__CCLOGWITHFUNCTION("local player load ok: %s",ROLE_SAVE_FILE);
	}
	else
	{
		LocalPlayer::getInstance()->initDefaultLocalPlayer();
		LocalPlayer::getInstance()->save(GameDefine::ROLE_SAVE_FILE);
	}

	auto ui = MainUI::create();
	this->addChild(ui,UI_LAYER,TAG_UI_LAYER);


	auto win_size = Director::getInstance()->getWinSize();

	//
	auto _nb = NoticeBoard::create();
	_nb->setPosition(Vec2(win_size.width/2,win_size.height/2));
	this->addChild(_nb,POP_MENU);


	// 拖屏
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesMoved = CC_CALLBACK_2(SceneMain::onTouchesMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);



	// 退出游戏
	auto keyboard_listener = EventListenerKeyboard::create();
	keyboard_listener->onKeyReleased = CC_CALLBACK_2(SceneMain::onKeyReleased,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard_listener, this);


	return true;
}





void SceneMain::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
	auto winSize = VisibleRect::getVisibleRect().size;

	auto touch = touches[0];
	auto diff = touch->getDelta();
	auto node = getChildByTag(TAG_MAP_LAYER);
	auto currentPos = node->getPosition();

	//
	diff.y = 0.f;


	// 做下边界处理
	if (diff.x > 0 && currentPos.x <= 0)
	{
		diff.x = MIN(diff.x,-currentPos.x);
	}

	/*if (diff.y > 0 && currentPos.y <= 0)
	{
	diff.y = MIN(diff.y,-currentPos.y);
	}*/

	float dt = node->getBoundingBox().size.width - winSize.width;
	if (diff.x <= 0 && currentPos.x >= -dt)
	{	
		diff.x = MAX(diff.x,-dt - currentPos.x);
	}

	/*dt = node->getBoundingBox().size.width - winSize.height;
	if (diff.y <= 0 && currentPos.y >= -dt)
	{
	diff.y = MAX(diff.y,-dt - currentPos.y);
	}*/


	//
	node->setPosition(currentPos + diff);
}



void SceneMain::onKeyReleased( EventKeyboard::KeyCode keyCode, Event* event )
{

	CCLOG("on key released");
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_BACK:
		{
			auto pop_menu = this->getChildByTag(TAG_POP_MENU);
			if (pop_menu)
			{
				CCLOG("pop menu too many");
				return;
			}

			MsgBox* _mb = MsgBox::create();
			_mb->initMsg(1,1,1);
			//_mb->setPosition(VisibleRect::center() - Vec2(_mb->getContentSize()/2));
			addChild(_mb,POP_MENU,TAG_POP_MENU);
		}
		break;
	default:
		break;
	}
}





