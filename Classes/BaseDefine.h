#pragma once


// base variable definition

namespace BaseDefine
{
	// Ĭ���ٶ�
	const float DEFAULT_SPEED	= 15.0f;
	const float PI				= 3.1415926535897932384626433f;
	// �����ٶ�
	const float ANIM_SPEED		= 0.3f;
	//
	const float DEFAULT_MIN_DISTANCE = 0.2f;

	// �ٷ�������
	const int HUNDRED_BASE = 100;

	// ���ٻ�׼
	const float BASE_ATK_SPEED = 1.f;

	// ��Ч��ID
	const int INVALID_ID = -1;

	// �����Ч������Χ
	const int MAX_INT_RANGE = 200000000;

	// ��������
	enum Object_Type
	{
		OT_Monster = 1,
		OT_Item,
		OT_Effect,
	};


	// ��������
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



	//---- ��Ϸͨ�������趨 ----

	// ͨ�ó���
	const int MIN_COMMON_LENGTH = 16;
	const int COMMON_LENGTH = 32;
	const int PATH_LENGTH = 96;
	const int MSG_LENGTH = 256;

	const int STRING_LENGTH = PATH_LENGTH;
}


