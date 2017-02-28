#pragma once
#include "cocos2d.h"
#include "GameDefine.h"
#include "../component/Bag.h"
#include "../component/TaskTrigger.h"

USING_NS_CC;
using namespace GameDefine;


/*
 * ������ݹ�����
 *
 *
 */


class LocalPlayer
{
public:
	LocalPlayer(void);
	~LocalPlayer(void);

	friend class ObjFactory;


	enum
	{
		// ���µļ��
		LP_UPDATE_INTERVAL = 3,
	};



	static LocalPlayer* getInstance();



	// ��ʼ��ɫ��Ϣ
	void initDefaultLocalPlayer();




	// ȷ�Ͻ���������ʱ����ת��Ϊ�־�����
	void conformReward();



	// ��ע�¼�
	void touchTaskTrigger(int _t_mask);


	//////////////////////////////////////////////////////////////////////////
	// ͨ�ýӿ�
	//////////////////////////////////////////////////////////////////////////

	
	// ����
	void update(float Delta);



	/*
	 * @desc ���û�������ֵ
	 * @param
	 * @return
	 *	
	 */
	int addValue(GameDefine::tBaseAttr::BA_TYPE _ba_index,int _gold, unsigned int uLimits = BaseDefine::MAX_INT_RANGE);
	


	// ��ȡ��������
	tDailyTaskInfo* getDailyTaskByTid(int _tid);



	//////////////////////////////////////////////////////////////////////////
	// ����������л�
	//////////////////////////////////////////////////////////////////////////

	void save(const char* _save_file);
	bool load(const char* _save_file);


protected:


	// ������ʼ��
	void initStageInfo();

	// ÿ�������ʼ��
	void initDailyTask();


public:


	//////////////////////////////////////////////////////////////////////////
	// ��������
	//////////////////////////////////////////////////////////////////////////

	tBaseAttr m_base_attr;
	Bag m_bag;
	tCopyInfo m_copy_info;
	// ��������
	tGuideInfo m_guide_info;
	// �ճ�����
	std::vector<tDailyTaskInfo> m_daily_task;
	// �����¼�
	TaskTrigger m_task_tri;
	//////////////////////////////////////////////////////////////////////////

	// ��ʱ��ս��ѡ����Ϣ
	tTempFightInfo m_temp_fight_info;


	// ������Ϣ
	// ���츱����Ϣ����¼ÿ�����������һ���Ӹ�������Ϣ
	// map[main_stage_id] = sub_stage_id;
	std::map<int,int> m_last_stage_infos;
	std::map<int,int> m_stage_infos;

private:
	// �汾��Ϣ���浵�ļ�ͷ
	tGlobalData m_global;
	static LocalPlayer* g_spRoleData;
};


