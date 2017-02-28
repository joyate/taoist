#pragma once
#include "../data/GameData.h"


class LootMgr
{
public:
	LootMgr(void);
	~LootMgr(void);


	static LootMgr& getInstance();
	


	/*
	 * @desc 掉落奖励
	 * @param drop_id 掉落id
	 * @return 实际掉落个数
	 *	
	 */
	int dropReward(int drop_id);



private:
	static LootMgr* s_loot_mgr;
};

