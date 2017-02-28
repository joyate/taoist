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

		// �������� ���
		CARDTIP_LVL_FMT			= 5,
		//CARDTIP_FE_FMT,
		CARDTIP_HP_FMT			= 7,
		
		//CARDTIP_MAG_CRI_FMT,

		// ��������
		CONST_FE_NAME_GOLD		= 12,

		// �޼���
		NONE_SKILL_TIP			= 17,
		STAGE_TITLE_FMT,							// %s��%d��
		FUNCTION_NOT_OPEN,							// ���ܻ�δ����


		STRENGTH_FMT			= 30,				// �������
		WISE_FMT,
		AGILITY_FMT,
		CONTROL_FMT,

		// ���������ʾ
		CARDTIP_PHYS_ATK_FMT	= 34,
		CARDTIP_MAG_ATK_FMT,
		CARDTIP_CRI_FMT,
		CARDTIP_PHYS_DEF_FMT,
		CARDTIP_MAG_DEF_FMT,
		
		SKILL_TIP_TARGET_SELF,						// ���ܲ��ܶ��Լ�ʹ��
		SKILL_TIP_CDING,							// ������ȴ��
		SKILL_COST_NOT_ENOUGH,						// ��ֵ����
		SKILL_STATE_WALK_CHECK,						// �ж��в����ͷż���

		BATTLE_POS_HAS_USED,						// λ���Ѿ�ʹ����
		BATTLE_NO_HERO,								// û��ѡ��Ӣ��
		BATTLE_PHYS_NOT_ENOUGH,						// ����������
		BATTLE_STAGE_REQ,							// ǰ�ùؿ�Ҫ��

		TIPS_HERO_REWARD_TITLE,						// ��ϲ����ȡһ��Ӣ�ۿ�


		//CN_WYC					= 101,			// �������ƣ���Դ��

	};


	static MsgManager& getInstance();



	/*
	 * @desc ��ȡ_msg_id��Ӧ���ַ�����Ϣ
	 * @param _msg_id ��Ϣid
	 * @return 
	 *	
	 */
	const char* getMsg(int _msg_id);

private:
	static MsgManager* s_mm;
};

