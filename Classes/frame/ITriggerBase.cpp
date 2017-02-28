#include "ITriggerBase.h"
#include "MapManager.h"
#include "../utility/Utility.h"
#include "BattleScene.h"

ITriggerBase::~ITriggerBase(void)
{
}


//////////////////////////////////////////////////////////////////////////

GameLoseTrigger::~GameLoseTrigger()
{

}



void GameLoseTrigger::update(GameDefine::tTriggerInfo& _ti, float delta )
{

	if (_ti.nTrigType == GameDefine::tTriggerInfo::TMT_ONCE && _ti.nCount >= 1)
	{
		return;
	}

	auto bt_scene = (BattleScene*)Director::getInstance()->getRunningScene();
	MapManager& map = bt_scene->getCurMapMgr();

	std::vector<int> obj_ids;
	int nCount = map.getObjsInRect(_ti.m_rect,obj_ids);
	if (nCount > 0)
	{
		bt_scene->handleBattleResEvent(GameDefine::BR_LOSE);
	}
}



void GameWinTrigger::update( GameDefine::tTriggerInfo& _ti,float delta )
{

	if (_ti.nTrigType == GameDefine::tTriggerInfo::TMT_ONCE && _ti.nCount >= 1)
	{
		return;
	}

	auto bt_scene = (BattleScene*)Director::getInstance()->getRunningScene();
	MapManager& map = bt_scene->getCurMapMgr();

	if (map.getActiveObjCount(GameEntity::OT_OFFENSIVE) == 0)
	{
		bt_scene->handleBattleResEvent(GameDefine::BR_WIN);
	}

}
