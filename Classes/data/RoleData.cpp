#include "RoleData.h"



RoleData& RoleData::getInstance()
{
	static RoleData s_rd;
	return s_rd;
}


bool RoleData::load( const char* buff,int _len )
{
	return false;
}


