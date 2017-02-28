#pragma once
#include "cocos2d.h"


USING_NS_CC;


class TimeManager
{
public:
	TimeManager(void);
	~TimeManager(void);


	enum
	{
		// һ���ʱ�䳤��
		DAY_LEN = 24*60*60,
		HOUR_LEN = 60*60,
		MIN_LEN = 60,
	};


	static TimeManager& getInstance();


	// ��ȡ��1900�굽������ȥ������
	unsigned int getTime()
	{
		time_t timep;
		time(&timep);
		return timep;
	}



	// �ж�_past_time���������Ƿ���time_len���ˣ���true��û��false
	bool checkTimeOver(unsigned int _past_time, int time_len = DAY_LEN);


	// �������ھ���_past_time�ĳ���
	int distTimeLength(unsigned int _past_time);
	


private:
	static TimeManager* s_tm_mgr;
	static unsigned int s_cur_time;
};

