#include "TaskManager.h"
#include "../data/LocalPlayer.h"
#include "../data/GameData.h"
#include "TimeManager.h"

TaskManager* TaskManager::s_tm = nullptr;

TaskManager::TaskManager(void)
{
}


TaskManager::~TaskManager(void)
{
}



TaskManager& TaskManager::getInstance()
{
	if (!s_tm)
	{
		s_tm = new TaskManager;
	}

	return *s_tm;
}



void TaskManager::onEvent( int task_type,int task_tar/* = 0*/)
{
	bool bChanged = false;
	auto& daily_tasks = LocalPlayer::getInstance()->m_daily_task;
	int dt_cnt = daily_tasks.size();
	for (int i = 0; i < dt_cnt; i++)
	{
		auto cfg_task_info = g_DailyTaskMgr.getObject(daily_tasks[i].tid);
		if (!cfg_task_info)
		{
			CCLOG("task info %d no data",daily_tasks[i].tid);
			continue;
		}

		if (cfg_task_info->task_type & task_type)
		{

			if (cfg_task_info->task_target != 0 && cfg_task_info->task_target != task_tar)
			{
				continue;
			}

			daily_tasks[i].cur_num++;
			if (daily_tasks[i].cur_num >= cfg_task_info->task_num)
			{
				// 任务完成
				// 通知
			}
			// 记录时间
			daily_tasks[i].last_time = TimeManager::getInstance().getTime();
			bChanged = true;
		}
	}

	// 
	if (bChanged)
	{
		LocalPlayer::getInstance()->save(GameDefine::ROLE_SAVE_FILE);
	}
}



GameDefine::tDailyTaskInfo* TaskManager::getTaskByTid( int _tid )
{
	auto& daily_tasks = LocalPlayer::getInstance()->m_daily_task;
	int dt_cnt = daily_tasks.size();


	for (int i = 0; i < dt_cnt; i++)
	{
		if (daily_tasks[i].tid == _tid)
		{
			return &daily_tasks[i];
		}
	}

	return nullptr;
}



void TaskManager::update(float _dt)
{
	static float wait_time = 0;	
	if (wait_time > 0)
	{
		wait_time = MAX(0, wait_time - _dt);
		return;
	}

	bool bTaskUpdated = false;
	auto& daily_tasks = LocalPlayer::getInstance()->m_daily_task;
	int dt_cnt = daily_tasks.size();
	for (int i = 0; i < dt_cnt; i++)
	{
		auto& daily_task = daily_tasks[i];

		// 任务有效
		if (daily_task.ts != GameDefine::TS_INVALID)
		{
			if (TimeManager::getInstance().checkTimeOver(daily_task.last_time))
			{
				daily_task.ts = GameDefine::TS_DOING;
				daily_task.cur_num = 0;
				
				bTaskUpdated = true;
			}
		}
	}

	// 任务更新过，保存一下
	if (bTaskUpdated)
	{
		LocalPlayer::getInstance()->save(GameDefine::ROLE_SAVE_FILE);
	}

	//
	wait_time = TimeManager::HOUR_LEN - TimeManager::getInstance().getTime()%TimeManager::HOUR_LEN;
}


