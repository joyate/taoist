#include "BattleScene.h"
#include "cocostudio/CocoStudio.h"
#include "../obj/Hero.h"
#include "../obj/Defender.h"
#include "../VisibleRect.h"
#include "../game_ui/FightUI.h"
#include "../data/LocalPlayer.h"
#include "../game_ui/RewardLayer.h"
#include "../game_ui/LosePanel.h"
#include "../component/GuideFilterMgr.h"
#include "../component/GuideLayer.h"
#include "../component/TaskManager.h"

using namespace cocostudio;

BattleScene::BattleScene(void):
	m_shop_layout(nullptr)
{
}


BattleScene::~BattleScene(void)
{
}



bool BattleScene::init()
{
	
	auto _stage_id = LocalPlayer::getInstance()->m_temp_fight_info.curr_stage_id;
	if (_stage_id <= 0)
	{
		CCLOG("stage id %d is invalid",_stage_id);
		return false;
	}

	Node* _map_node = m_mapMgr.init(_stage_id);
	if (!_map_node)
	{
		CCLOG("tmx initialize failed");
		return false;
	}
	this->addChild(_map_node,0,TAG_MAP_LAYER);



	// 战斗UI
	auto ft_ui = FightUI::create();
	ft_ui->setMapManager(&m_mapMgr);
	this->addChild(ft_ui,FIGHT_UI_LAYER,TAG_FIGHT_UI);


	// 初始化战斗系统


	// EventListener
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(BattleScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(BattleScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(BattleScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	// 开启update
	scheduleUpdate();
	return true;
}


void BattleScene::update( float delta )
{


	// 地图update
	m_mapMgr.update(delta);
}

void BattleScene::onEnter()
{
	Scene::onEnter();

	// 引导
	GuideFilterMgr::getInstance().checkGuideFilter(GuideFilterMgr::GFN_BATTLE_HERO_MOVE);


	// 关注任务事件
	TaskManager::getInstance().onEvent(GameDefine::TT_ST_FIGHT_COPY);
}

void BattleScene::onExit()
{

	Scene::onExit();
}



bool BattleScene::onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* event )
{

	return true;
}

void BattleScene::onTouchMoved( cocos2d::Touch* touch, cocos2d::Event* event )
{
	auto winSize = Director::getInstance()->getWinSize();

	auto _delta = touch->getDelta();
	const Vec2 currentPos = m_mapMgr.getPosition();

	_delta.y = 0;

	// 拖动战斗地图的处理

	// 做下边界处理
	if (_delta.x > 0 && currentPos.x <= 0)
	{
		_delta.x = MIN(_delta.x,-currentPos.x);
	}

	float dt = m_mapMgr.getBoundingBox().size.width - winSize.width;
	if (_delta.x <= 0 && currentPos.x >= -dt)
	{	
		_delta.x = MAX(_delta.x,-dt - currentPos.x);
	}

	m_mapMgr.setPosition(currentPos + _delta);

	//
}

void BattleScene::onTouchEnded( cocos2d::Touch* touch, cocos2d::Event* event )
{
	/*Vec2 pos = touch->getLocation();
	m_mapMgr.onTouch(pos);*/
}



void BattleScene::handleBattleResEvent(int nRes)
{
	this->specialPause();

	// 清除guide
	auto guide_player = this->getChildByTag(GuideLayer::TAG_GUIDE_NODE);
	if (guide_player)
	{
		guide_player->removeFromParent();
	}

	if (nRes == GameDefine::BR_LOSE)
	{
		auto lost_panel = LosePanel::create();
		if (lost_panel)
		{
			this->addChild(lost_panel,REWARD_PANEL_LAYER);
		}
	}
	else
	{
		auto reward_panel = RewardLayer::create();
		reward_panel->initBattleResult(m_mapMgr.getStageId());
		this->addChild(reward_panel,REWARD_PANEL_LAYER);
	}

	
}



void BattleScene::specialPause( int _except_id /*= BaseDefine::INVALID_ID*/)
{
	this->pause();

	m_mapMgr.specialPause(_except_id);
}

void BattleScene::specialResume()
{
	this->resume();
	m_mapMgr.specialResume();
}






