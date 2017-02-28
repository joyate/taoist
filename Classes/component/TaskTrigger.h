#pragma once
#include "../GameDefine.h"


/*
 * 任务触发类型，仅仅触发一次
 * 其相对于是任务，但是目前游戏里还没有主线任务
 *
 */



class TaskTrigger
{
public:
	TaskTrigger(void);
	~TaskTrigger(void);


	enum TT_MASK_TYPE
	{
		TT_FIRST_ENTER_GAME = 1,				// 第一次进入游戏，送卡片
	};


	void serialize(TaoOStream& _stream)
	{
		_stream << m_task_data;
	}

	void unserialize(TaoIStream& _stream)
	{
		_stream >> m_task_data;
	}

	bool taskTest(int _t_mask)
	{
		return (m_task_data & (1 << (_t_mask-1))) != 0;
	}

	void setTaskMask(int _t_mask)
	{
		m_task_data |= (1 << (_t_mask - 1));
	}

	bool triggerTask(int _t_mask);

private:
	int m_task_data;
};

