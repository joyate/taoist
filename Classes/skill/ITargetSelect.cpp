#include "ITargetSelect.h"
#include "../frame/BattleScene.h"
#include "../frame/MapManager.h"


ITargetSelect::~ITargetSelect()
{

}




int ITargetSelect::handleSelect( GameEntity* _obj,Skill* _skill)
{
	std::vector<GameEntity*> _out;
	int nCnt = handleTargetSelectFilter(_obj,_skill,&_out);
	if (nCnt > 0)
	{
		for (int i = 0; i < nCnt; i++)
		{
			// 如果是召唤物，并且召唤物处于出场阶段
			if (_out[i]->getType() & GameEntity::OT_SUMMONER && _out[i]->isBorning())
			{
				continue;
			}

			_skill->pushTargetId(_out[i]->getID());
		}	
	}

	return nCnt;
}




int CommonSkillSelect::handleTargetSelectFilter(GameEntity* _obj,Skill* _skill,std::vector<GameEntity*>* _out)
{
	TargetSelectorFilter _tsf;

	// 选择目标类型
	if (_obj->getType() & GameEntity::OT_DEFENDER)
	{
		_tsf.select_mask = GameEntity::OT_OFFENSIVE;
	}
	else
	{
		_tsf.select_mask = GameEntity::OT_DEFENDER;
	}



	auto sk_info = g_SkillInfoMgr.getObject(_skill->getID());
	if (!sk_info)
	{
		CCLOG("skill %d has no info",_skill->getID());
		return -1;
	}


	_tsf.filter_dis = sk_info->ts_vals[TS_COMMON_SELECT_DIST_INDEX];
	_tsf.sel_num = sk_info->tar_num;


	//
	BattleScene* bs = (BattleScene*)Director::getInstance()->getRunningScene();
	MapManager& _map_mgr = bs->getCurMapMgr();
	
	return _map_mgr.getLineNearestObjs(_obj,_out,_tsf);

}


//////////////////////////////////////////////////////////////////////////

int SummonTargetSelect::handleTargetSelectFilter(GameEntity* _obj,Skill* _skill,std::vector<GameEntity*>* _out)
{

	BattleScene* bs = (BattleScene*)Director::getInstance()->getRunningScene();
	MapManager& _map_mgr = bs->getCurMapMgr();

	//
	TargetSelectorFilter tsf;	
	tsf.select_mask = (_obj->getMainType()|GameEntity::OT_SUMMONER);

	auto sk_info = g_SkillInfoMgr.getObject(_skill->getID());
	if (!sk_info)
	{
		CCLOG("skill %d has no info",_skill->getID());
		return false;
	}

	// 选择目标过滤器
	tsf.sel_num = sk_info->tar_num;

	return _map_mgr.getAllSummonObjs(_obj,_out,tsf);
}



int SelfTargetSelect::handleTargetSelectFilter( GameEntity* _obj,Skill* _skill,std::vector<GameEntity*>* _out )
{
	if (!_obj)
	{
		return 0;
	}

	_out->push_back(_obj);

	return 1;
}




//
int RectTargetSelect::handleTargetSelectFilter( GameEntity* _obj,Skill* _skill,std::vector<GameEntity*>* _out )
{
	TargetSelectorFilter _tsf;

	auto sk_info = g_SkillInfoMgr.getObject(_skill->getID());
	if (!sk_info)
	{
		CCLOG("skill %d has no info",_skill->getID());
		return -1;
	}

	_tsf.sel_num = sk_info->tar_num;

	Rect rect;
	// 选择目标类型
	if (_obj->getType() & GameEntity::OT_DEFENDER)
	{
		_tsf.select_mask = GameEntity::OT_OFFENSIVE;
		rect = Rect(_obj->getPosition().x,_obj->getPosition().y - MapManager::OBJ_POS_OFFSET_GRID_Y,
						sk_info->ts_vals[TS_RECT_SELECT_WIDTH_INDEX] * MapManager::GRID_WIDTH_LEN,
						sk_info->ts_vals[TS_RECT_SELECT_HEIGHT_INDEX] * MapManager::GRID_HEIGHT_LEN);
	}
	else
	{
		_tsf.select_mask = GameEntity::OT_DEFENDER;
		rect = Rect(_obj->getPosition().x - sk_info->ts_vals[TS_RECT_SELECT_WIDTH_INDEX] * MapManager::GRID_WIDTH_LEN,
			_obj->getPosition().y - MapManager::OBJ_POS_OFFSET_GRID_Y,
			sk_info->ts_vals[TS_RECT_SELECT_WIDTH_INDEX] * MapManager::GRID_WIDTH_LEN,
			sk_info->ts_vals[TS_RECT_SELECT_HEIGHT_INDEX] * MapManager::GRID_HEIGHT_LEN);
	}


	BattleScene* bs = (BattleScene*)Director::getInstance()->getRunningScene();
	MapManager& _map_mgr = bs->getCurMapMgr();
	return _map_mgr.getRectInObjs(rect,_out,_tsf);
}



int BulletTargetSelect::handleTargetSelectFilter( GameEntity* _obj,Skill* _skill,std::vector<GameEntity*>* _out )
{
	int mask = 0;
	if (_obj->getType() & GameEntity::OT_DEFENDER)
	{
		mask = GameEntity::OT_OFFENSIVE;
	}
	else
	{
		mask = GameEntity::OT_DEFENDER;
	}


	TargetSelectorFilter tsf;
	tsf.filter_dis = 0;
	tsf.sel_num = 1;
	tsf.bAdjustY = true;
	tsf.select_mask = mask;

	BattleScene* bs = (BattleScene*)Director::getInstance()->getRunningScene();
	MapManager& _map_mgr = bs->getCurMapMgr();
	return _map_mgr.getLineNearestObjs(_obj,_out,tsf);
}
