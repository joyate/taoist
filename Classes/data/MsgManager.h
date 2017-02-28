#pragma once
#include "GameData.h"


class MsgManager
{
public:
	MsgManager(void);
	~MsgManager(void);



	enum MSG_ID
	{
		HMS_TIME_FMT			= 2,
		

		//
		BATTLE_ROUND_FMT		= 3,

		// 基本属性 相关
		CARDTIP_LVL_FMT			= 5,
		//CARDTIP_FE_FMT,
		CARDTIP_HP_FMT			= 7,
		
		//CARDTIP_MAG_CRI_FMT,

		// 五行名称
		CONST_FE_NAME_GOLD		= 12,

		// 无技能
		NONE_SKILL_TIP			= 17,
		STAGE_TITLE_FMT,							// %s第%d章
		FUNCTION_NOT_OPEN,							// 功能还未开放


		STRENGTH_FMT			= 30,				// 力量相关
		WISE_FMT,
		AGILITY_FMT,
		CONTROL_FMT,

		// 攻击相关提示
		CARDTIP_PHYS_ATK_FMT	= 34,
		CARDTIP_MAG_ATK_FMT,
		CARDTIP_CRI_FMT,
		CARDTIP_PHYS_DEF_FMT,
		CARDTIP_MAG_DEF_FMT,
		
		SKILL_TIP_TARGET_SELF,						// 技能不能对自己使用
		SKILL_TIP_CDING,							// 技能冷却中
		SKILL_COST_NOT_ENOUGH,						// 魂值不够
		SKILL_STATE_WALK_CHECK,						// 行动中不能释放技能

		BATTLE_POS_HAS_USED,						// 位置已经使用了
		BATTLE_NO_HERO,								// 没有选择英雄
		BATTLE_PHYS_NOT_ENOUGH,						// 体力不够了
		BATTLE_STAGE_REQ,							// 前置关卡要求

		TIPS_HERO_REWARD_TITLE,						// 恭喜您获取一张英雄卡


		//CN_WYC					= 101,			// 副本名称，仙源村

	};


	static MsgManager& getInstance();



	/*
	 * @desc 获取_msg_id对应的字符串信息
	 * @param _msg_id 信息id
	 * @return 
	 *	
	 */
	const char* getMsg(int _msg_id);

private:
	static MsgManager* s_mm;
};

