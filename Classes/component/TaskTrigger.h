#pragma once
#include "../GameDefine.h"


/*
 * ���񴥷����ͣ���������һ��
 * ������������񣬵���Ŀǰ��Ϸ�ﻹû����������
 *
 */



class TaskTrigger
{
public:
	TaskTrigger(void);
	~TaskTrigger(void);


	enum TT_MASK_TYPE
	{
		TT_FIRST_ENTER_GAME = 1,				// ��һ�ν�����Ϸ���Ϳ�Ƭ
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

