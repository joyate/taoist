#pragma once
#include "../data/GameData.h"


class LootMgr
{
public:
	LootMgr(void);
	~LootMgr(void);


	static LootMgr& getInstance();
	


	/*
	 * @desc ���佱��
	 * @param drop_id ����id
	 * @return ʵ�ʵ������
	 *	
	 */
	int dropReward(int drop_id);



private:
	static LootMgr* s_loot_mgr;
};

