#pragma once
#include "cocos2d.h"


USING_NS_CC;


/*
 * ���������
 *
 */



class GuideFilterMgr
{
public:
	GuideFilterMgr(void);
	~GuideFilterMgr(void);


	enum GUIDE_FILTER_NODE
	{
		GFN_ROLE_INTRODUCE = 1,							// ��ɫ��������
		GFN_BATTLE_PRATICE,								// ս����ϰ
		GFN_BATTLE_HERO_MOVE,							// �ƶ�Ӣ��
		GFN_BATTLE_SOLDIER_SELECT,						// С��ѡ��
		GFN_BATTLE_HERO_NORMAL_SKILL_USE,				// ʹ�õ������
		
	};


	//
	static GuideFilterMgr& getInstance();




	// ����Ƿ��������ģʽ
	void checkGuideFilter(int _cur_guide_id);


private:
	static GuideFilterMgr* s_gf_mgr;
};






