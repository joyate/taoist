#pragma once
#include "../GameDefine.h"

class GameEntity;


class AttrChange
{
public:


	enum ATTR_TYPE
	{
		AT_NONE,
		AT_ATK_SPEED,
		AT_SPEED,
		AT_HP,
	};


	// ��ֵ�ı�
	static void changeAttr(GameEntity* _ge,ATTR_TYPE _at,float _val);


	// ��ֵ����
	static void appendAttr(GameEntity* _ge,ATTR_TYPE _at,float _val);


	// ���ٷֱȸ���
	static void appendAttrPercent(GameEntity* _ge,ATTR_TYPE _at,float _val);
};

