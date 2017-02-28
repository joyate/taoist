#pragma once
#include "cocos2d.h"
#include "GameDefine.h"
#include "../component/Bag.h"
#include "../component/TaskTrigger.h"

USING_NS_CC;
using namespace GameDefine;


/*
 * 玩家数据管理类
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
		// 更新的间隔
		LP_UPDATE_INTERVAL = 3,
	};



	static LocalPlayer* getInstance();



	// 初始角色信息
	void initDefaultLocalPlayer();




	// 确认奖励，将临时数据转化为持久数据
	void conformReward();



	// 关注事件
	void touchTaskTrigger(int _t_mask);


	//////////////////////////////////////////////////////////////////////////
	// 通用接口
	//////////////////////////////////////////////////////////////////////////

	
	// 更新
	void update(float Delta);



	/*
	 * @desc 设置基本属性值
	 * @param
	 * @return
	 *	
	 */
	int addValue(GameDefine::tBaseAttr::BA_TYPE _ba_index,int _gold, unsigned int uLimits = BaseDefine::MAX_INT_RANGE);
	


	// 获取任务数据
	tDailyTaskInfo* getDailyTaskByTid(int _tid);



	//////////////////////////////////////////////////////////////////////////
	// 玩家数据序列化
	//////////////////////////////////////////////////////////////////////////

	void save(const char* _save_file);
	bool load(const char* _save_file);


protected:


	// 副本初始化
	void initStageInfo();

	// 每日任务初始化
	void initDailyTask();


public:


	//////////////////////////////////////////////////////////////////////////
	// 保存数据
	//////////////////////////////////////////////////////////////////////////

	tBaseAttr m_base_attr;
	Bag m_bag;
	tCopyInfo m_copy_info;
	// 引导数据
	tGuideInfo m_guide_info;
	// 日常任务
	std::vector<tDailyTaskInfo> m_daily_task;
	// 触发事件
	TaskTrigger m_task_tri;
	//////////////////////////////////////////////////////////////////////////

	// 临时的战斗选择信息
	tTempFightInfo m_temp_fight_info;


	// 辅助信息
	// 构造副本信息，记录每个主副本最后一个子副本的信息
	// map[main_stage_id] = sub_stage_id;
	std::map<int,int> m_last_stage_infos;
	std::map<int,int> m_stage_infos;

private:
	// 版本信息，存档文件头
	tGlobalData m_global;
	static LocalPlayer* g_spRoleData;
};


