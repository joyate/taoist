#pragma once
#include "cocos2d.h"


USING_NS_CC;


/*
 * 引导检查器
 *
 */



class GuideFilterMgr
{
public:
	GuideFilterMgr(void);
	~GuideFilterMgr(void);


	enum GUIDE_FILTER_NODE
	{
		GFN_ROLE_INTRODUCE = 1,							// 角色背包介绍
		GFN_BATTLE_PRATICE,								// 战斗练习
		GFN_BATTLE_HERO_MOVE,							// 移动英雄
		GFN_BATTLE_SOLDIER_SELECT,						// 小兵选择
		GFN_BATTLE_HERO_NORMAL_SKILL_USE,				// 使用点击技能
		
	};


	//
	static GuideFilterMgr& getInstance();




	// 检查是否进入引导模式
	void checkGuideFilter(int _cur_guide_id);


private:
	static GuideFilterMgr* s_gf_mgr;
};






