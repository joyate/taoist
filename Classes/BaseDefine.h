#pragma once


// base variable definition

namespace BaseDefine
{
	// 默认速度
	const float DEFAULT_SPEED	= 15.0f;
	const float PI				= 3.1415926535897932384626433f;
	// 动画速度
	const float ANIM_SPEED		= 0.3f;
	//
	const float DEFAULT_MIN_DISTANCE = 0.2f;

	// 百分数基数
	const int HUNDRED_BASE = 100;

	// 攻速基准
	const float BASE_ATK_SPEED = 1.f;

	// 无效的ID
	const int INVALID_ID = -1;

	// 最大有效整数范围
	const int MAX_INT_RANGE = 200000000;

	// 对象类型
	enum Object_Type
	{
		OT_Monster = 1,
		OT_Item,
		OT_Effect,
	};


	// 动画类型
	enum AnimType
	{
		AT_IDLE = 1,
		AT_ARDER,
		AT_WALK,
		AT_ATK,
		AT_BEATK,
		AT_DEAD,
		AT_BORN,
		AT_NUM,
	};



	//---- 游戏通用数据设定 ----

	// 通用长度
	const int MIN_COMMON_LENGTH = 16;
	const int COMMON_LENGTH = 32;
	const int PATH_LENGTH = 96;
	const int MSG_LENGTH = 256;

	const int STRING_LENGTH = PATH_LENGTH;
}


