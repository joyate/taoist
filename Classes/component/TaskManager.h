#pragma once
#include "../GameDefine.h"

/*
 * ���������
 * ������߼�������
 *  
 */



class TaskManager
{
public:
	TaskManager(void);
	~TaskManager(void);


	static TaskManager& getInstance();


	/*
	 * @desc ���������¼�
	 * @param task_type ��������
	 * @param task_tar ��������Ĺؼ�����
	 * @return
	 *	
	 */
	void onEvent(int task_type,int task_tar = 0);




	// ��������״̬���ر����й�ʱ���
	// ÿСʱ������
	void update(float _dt);



	//
	GameDefine::tDailyTaskInfo* getTaskByTid(int _tid);


private:
	static TaskManager* s_tm;
};

