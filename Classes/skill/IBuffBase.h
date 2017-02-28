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
		BT_ATTACK_SPEED_AFFECT,				// ����Ӱ��
		BT_SPEED_AFFECT,					// �ٶ�Ӱ��
		BT_REBORTH_AFFECT,					// ����
		BT_ATTR_AFFACT,						// ���Ըı�
		BT_DEADTH_BORN_AFFECT,				// �����ٻ�				
	};


	enum 
	{
		ID = BT_BASE,
	};

	
public:


	// ��ø�״̬ 
	virtual void onEnter(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) = 0;


	// ����Ƿ���Թ��ϱ�buff
	virtual int onCheck(GameEntity* _owner, GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) = 0;


	// 
	virtual int onActive(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) = 0;

	// ������״̬
	virtual void onExit(GameEntity* _owner, GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd);


protected:

	virtual void attachEffect(GameEntity* _owner,const GameDefine::cfg_Buff_Data& _bd);
	virtual void detachEffect(GameEntity* _owner,GameDefine::tBuffData& _buff);

};



// ʱ������buff
class TimeBuffBase : public IBuffBase
{
public:
	//
	virtual int onCheck(GameEntity* _owner, GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;

	//
	virtual int onActive(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;
};


// �¼�����buff
class EventBuffBase : public IBuffBase
{
public:


	virtual void onEnter(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override
	{

	}


	// �������ok
	virtual int onCheck(GameEntity* _owner, GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override
	{
		return GameDefine::ER_OK;
	}


	// ֻ����һ��
	virtual int onActive(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override
	{
		return GameDefine::ER_EXIT;
	}
};



// �����ٶ�Ӱ��
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
		SLOW_FACTOR_INDEX,			// ��������
	};


	// ��ø�״̬ 
	virtual void onEnter(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;

	
	// ʧȥ��״̬
	virtual void onExit(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;

};




// �ƶ��ٶ�Ӱ��
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
		SPEED_AFFECT_FACTOR_INDEX,			// �ٶ�Ӱ�����������
	};


	// ��ø�״̬ 
	virtual void onEnter(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;


	// ʧȥ��״̬
	virtual void onExit(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;

};



// ����buff
class ReborthAffect : public EventBuffBase
{
public:
	ReborthAffect() {}
	virtual ~ReborthAffect() {}


	enum
	{
		ID = BT_REBORTH_AFFECT,
	};



	// ֻ����һ��
	virtual int onActive(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;
	


};


// ���Ըı�
class AttrChangeAffect : public TimeBuffBase
{
public:

	AttrChangeAffect() {}
	virtual ~AttrChangeAffect() {}


	enum
	{
		ID = BT_ATTR_AFFACT,


		// ��������
		ACA_TYPE_PARAM_INDEX = 0,
		ACA_VALUE_PARAM_INDEX = 1,

	};


	// ��ø�״̬ 
	virtual void onEnter(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;


	// ֻ����һ��
	virtual int onActive(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;

	
	// ʧȥ��״̬
	virtual void onExit(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;
};



// �����ٻ����ڸ������˵ĵط��ٻ�����
class DeadthBornAffect : public EventBuffBase
{
public:
	DeadthBornAffect() {}
	~DeadthBornAffect() {}


	enum
	{
		ID = BT_DEADTH_BORN_AFFECT,
	};


	// �ٻ������������
	enum
	{
		SUMMONER_ID_INDEX
	};


	virtual int onActive(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd) override;

};



