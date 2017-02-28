#pragma once
#include "../GameDefine.h"



class GameEntity;

class IBuffBase
{
protected:
	virtual ~IBuffBase();


public:

	// buff type id
	enum 
	{
		BT_BASE,
		BT_ATTACK_SPEED_AFFECT,				// 攻速影响
		BT_SPEED_AFFECT,					// 速度影响
		BT_REBORTH_AFFECT,					// 重生
		BT_ATTR_AFFACT,						// 属性改变
		BT_DEADTH_BORN_AFFECT,				// 死亡召唤				
	};


	enum 
	{
		ID = BT_BASE,
	};

	
public:


	// 获得该状态 
	virtual void onEnter(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) = 0;


	// 检查是否可以挂上本buff
	virtual int onCheck(GameEntity* _owner, GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) = 0;


	// 
	virtual int onActive(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) = 0;

	// 清理下状态
	virtual void onExit(GameEntity* _owner, GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd);


protected:

	virtual void attachEffect(GameEntity* _owner,const GameDefine::cfg_Buff_Data& _bd);
	virtual void detachEffect(GameEntity* _owner,GameDefine::tBuffData& _buff);

};



// 时间类型buff
class TimeBuffBase : public IBuffBase
{
public:
	//
	virtual int onCheck(GameEntity* _owner, GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;

	//
	virtual int onActive(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;
};


// 事件类型buff
class EventBuffBase : public IBuffBase
{
public:


	virtual void onEnter(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override
	{

	}


	// 检查总是ok
	virtual int onCheck(GameEntity* _owner, GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override
	{
		return GameDefine::ER_OK;
	}


	// 只作用一次
	virtual int onActive(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override
	{
		return GameDefine::ER_EXIT;
	}
};



// 攻击速度影响
class AttackSpeedAffect : public TimeBuffBase
{
public:
	AttackSpeedAffect() {}
	virtual ~AttackSpeedAffect() {}


	enum
	{
		ID = BT_ATTACK_SPEED_AFFECT,
	};


	enum
	{
		SLOW_FACTOR_INDEX,			// 减速因子
	};


	// 获得该状态 
	virtual void onEnter(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;

	
	// 失去该状态
	virtual void onExit(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;

};




// 移动速度影响
class SpeedAffect : public TimeBuffBase
{
public:
	SpeedAffect() {}
	virtual ~SpeedAffect() {}



	enum
	{
		ID = BT_SPEED_AFFECT,
	};


	enum
	{
		SPEED_AFFECT_FACTOR_INDEX,			// 速度影响参数索引，
	};


	// 获得该状态 
	virtual void onEnter(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;


	// 失去该状态
	virtual void onExit(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;

};



// 重生buff
class ReborthAffect : public EventBuffBase
{
public:
	ReborthAffect() {}
	virtual ~ReborthAffect() {}


	enum
	{
		ID = BT_REBORTH_AFFECT,
	};



	// 只作用一次
	virtual int onActive(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;
	


};


// 属性改变
class AttrChangeAffect : public TimeBuffBase
{
public:

	AttrChangeAffect() {}
	virtual ~AttrChangeAffect() {}


	enum
	{
		ID = BT_ATTR_AFFACT,


		// 参数解释
		ACA_TYPE_PARAM_INDEX = 0,
		ACA_VALUE_PARAM_INDEX = 1,

	};


	// 获得该状态 
	virtual void onEnter(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;


	// 只作用一次
	virtual int onActive(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;

	
	// 失去该状态
	virtual void onExit(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;
};



// 死亡召唤，在干死敌人的地方召唤生物
class DeadthBornAffect : public EventBuffBase
{
public:
	DeadthBornAffect() {}
	~DeadthBornAffect() {}


	enum
	{
		ID = BT_DEADTH_BORN_AFFECT,
	};


	// 召唤生物参数索引
	enum
	{
		SUMMONER_ID_INDEX
	};


	virtual int onActive(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;

};



