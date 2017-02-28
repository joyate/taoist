#pragma once
#include "../GameDefine.h"

/*
 * 任务管理器
 * 任务的逻辑处理部分
 *  
 */



class TaskManager
{
public:
	TaskManager(void);
	~TaskManager(void);


	static TaskManager& getInstance();


	/*
	 * @desc 跟踪任务事件
	 * @param task_type 任务类型
	 * @param task_tar 触发任务的关键参数
	 * @return
	 *	
	 */
	void onEvent(int task_type,int task_tar = 0);




	// 更新任务状态，特别是有关时间的
	// 每小时调用下
	void update(float _dt);



	//
	GameDefine::tDailyTaskInfo* getTaskByTid(int _tid);


private:
	static TaskManager* s_tm;
};

