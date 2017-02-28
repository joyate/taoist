#pragma once
#include <assert.h>
#include "../GameDefine.h"



struct stt_stage
{
	char m_stage_data[GameDefine::GD_STAGE_NUM_MAX];


	stt_stage()
	{
		memset(this,0,sizeof(stt_stage));
	}

	bool isDone(int _lvl)
	{
		assert(_lvl > 0 && _lvl <= GameDefine::GD_STAGE_NUM_MAX);
		return m_stage_data[_lvl - 1] >= GameDefine::E_STAGE_LVL_ONE && m_stage_data[_lvl - 1] <= GameDefine::E_STAGE_LVL_THREE;
	}
};




// 主角数据
class RoleData
{
public:
	

	static RoleData& getInstance();


	// 载入数据 
	bool load(const char* buff,int _len);


	char m_szName[BaseDefine::COMMON_LENGTH];	// 昵称
	unsigned short m_ulvl;						// 等级
	stt_stage m_stage_data;						// 关卡数据
};

