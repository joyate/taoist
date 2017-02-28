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


	// 按值改变
	static void changeAttr(GameEntity* _ge,ATTR_TYPE _at,float _val);


	// 按值附加
	static void appendAttr(GameEntity* _ge,ATTR_TYPE _at,float _val);


	// 按百分比附加
	static void appendAttrPercent(GameEntity* _ge,ATTR_TYPE _at,float _val);
};

