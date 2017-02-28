#include "TimeManager.h"


TimeManager* TimeManager::s_tm_mgr = nullptr;
unsigned int TimeManager::s_cur_time = 0;

TimeManager::TimeManager(void)
{
}


TimeManager::~TimeManager(void)
{
}



TimeManager& TimeManager::getInstance()
{
	if (!s_tm_mgr)
	{
		s_tm_mgr = new TimeManager();
	}

	return *s_tm_mgr;
}



bool TimeManager::checkTimeOver( unsigned int _past_time, int time_len /*= DAY_TIME_LENGTH*/ )
{
	unsigned int cur_time = getTime();
	int time_dis = cur_time - _past_time;
	if ( time_dis >= time_len)
	{
		return true;
	}

	return false;
}

int TimeManager::distTimeLength( unsigned int _past_time )
{
	unsigned int cur_time = getTime();
	CC_ASSERT(cur_time > _past_time);
	return cur_time - _past_time;
}








