#include "LootMgr.h"
#include "../data/LocalPlayer.h"

LootMgr* LootMgr::s_loot_mgr = nullptr;


LootMgr::LootMgr(void)
{
}


LootMgr::~LootMgr(void)
{
}

LootMgr& LootMgr::getInstance()
{
	if (!s_loot_mgr)
	{
		s_loot_mgr = new LootMgr();
	}
	return *s_loot_mgr;
}



int LootMgr::dropReward(int drop_id )
{
	if (drop_id < 0)
	{
		CCLOG("[LootMgr::dropReward] invalid parameter");
		return 0;
	}


	auto drop_info = g_DropInfoMgr.getObject(drop_id);
	if (!drop_info)
	{
		CCLOG("drop id %d has no data",drop_id);
		return 0;
	}

	if (drop_info->lbounds > drop_info->ubounds)
	{
		CCLOG("drop info has error");
		return 0;
	}


	auto& fi = LocalPlayer::getInstance()->m_temp_fight_info;

	// 实际奖励个数
	int nCurRewardCnt = 0;
	
	// 防止死循环
	int nTryCnt = 0;
	int nTryMax = 50;

	do 
	{
		float cur = CCRANDOM_0_1();
		for (int i = 0; i < drop_info->drop_group_cnt; i++)
		{
			if (cur > 1 - drop_info->m_drop_items[i].drop_prob)
			{
				if(fi.addRewardId(drop_info->m_drop_items[i].drop_item_id) >= 0)
				{
					nCurRewardCnt++;
				}
				break;
			}
		}

		nTryCnt++;

	} while (nCurRewardCnt < drop_info->lbounds && nTryCnt < nTryMax);

	// 奖励金币
	fi.rewardGold += drop_info->reward_gold;

	return nCurRewardCnt;
}
