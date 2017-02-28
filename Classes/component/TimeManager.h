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
		// 一天的时间长度
		DAY_LEN = 24*60*60,
		HOUR_LEN = 60*60,
		MIN_LEN = 60,
	};


	static TimeManager& getInstance();


	// 获取从1900年到现在逝去的秒数
	unsigned int getTime()
	{
		time_t timep;
		time(&timep);
		return timep;
	}



	// 判断_past_time距离现在是否有time_len秒了，有true，没有false
	bool checkTimeOver(unsigned int _past_time, int time_len = DAY_LEN);


	// 计算现在距离_past_time的长度
	int distTimeLength(unsigned int _past_time);
	


private:
	static TimeManager* s_tm_mgr;
	static unsigned int s_cur_time;
};

