#include "MsgManager.h"

MsgManager* MsgManager::s_mm = nullptr;


MsgManager::MsgManager(void)
{
}


MsgManager::~MsgManager(void)
{
}

MsgManager& MsgManager::getInstance()
{
	if (s_mm)
	{
		s_mm = new MsgManager();
	}

	return *s_mm;
}




const char* MsgManager::getMsg( int _msg_id )
{
	auto msg = g_MsgInfoMgr.getObject(_msg_id);
	if (msg)
	{
		return msg->msg;
	}

	return nullptr;
}


