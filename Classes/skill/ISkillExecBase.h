#pragma once
#include "cocos2d.h"
#include "Skill.h"


USING_NS_CC;

class GameEntity;



/*
 * ����ִ��ģ��
 *
 */




class ISkillExecBase
{
protected:
	virtual ~ISkillExecBase() = 0;

public:

	// ����ִ�з�ʽ
	enum
	{
		SE_TYPE_BASE,
		SE_TYPE_NORMAL,			// �����������Ͻ�������
		SE_TYPE_SHOOT,			// ���乥�����ӵ��������Ӻ��������
		SE_TYPE_TAR_POS,		// Ŀ���ѡ����
		SE_TYPE_ENERGY,			// ����������
		SE_TYPE_SUMMON,			// �ٻ�����
		SE_TYPE_BUFF,			// �����ͷ�buff
		SE_TYPE_POS_SUMMON,		// ľ���ⶨ���ٻ�(���ģ�������ʷԭ��)
		SE_TYPE_SELF_EXPLODE,	// �Ա����ܣ��ͷż��ܺ��ͷ�������
	};


	enum
	{
		ID = SE_TYPE_BASE,
	};


	/*
	 * @desc ִ�м���
	 * @param _ge �����ͷ���
	 * @param _skill ������Ϣ
	 * @return
	 *	
	 */
	virtual void onExec(GameEntity* _ge,Skill* _skill) = 0;

};





// ��ͨ����/���ܹ��������ͷ���Ϊԭ�㣬�е�Ϊ����
class NormalSkillExec : public ISkillExecBase
{
public:
	~NormalSkillExec() {}


	enum
	{
		ID = SE_TYPE_NORMAL,
	};


	virtual void onExec(GameEntity* _ge,Skill* _skill);

};




// �����͹���
class ShootSkillExec : public ISkillExecBase
{
public:
	~ShootSkillExec() {}


	enum
	{
		ID = SE_TYPE_SHOOT,
	};


	virtual void onExec(GameEntity* _ge,Skill* _skill);


protected:

	// ��ȡ�����λ�ã��Է�����Ϊ��׼
	Vec2 getEmitPos(GameEntity* _ge);

};




// ѡ��Ŀ���ļ���(����)
class TargetPosSkillExec : public ISkillExecBase
{
public:
	~TargetPosSkillExec() {}


	enum
	{
		ID = SE_TYPE_TAR_POS,
	};


	virtual void onExec(GameEntity* _ge,Skill* _skill);

};



// ���������ܣ�ָʹ�������ͷż���
class EnergyDouSkillExec : public ISkillExecBase
{
public:
	~EnergyDouSkillExec() {}

	enum
	{
		ID = SE_TYPE_ENERGY,
	};
	

	virtual void onExec(GameEntity* _ge,Skill* _skill);
};




// �ٻ�����
class SummonSkillExec : public ISkillExecBase
{
public:
	virtual ~SummonSkillExec()	{}

	enum
	{
		ID = SE_TYPE_SUMMON,
	};



	enum
	{
		SK_VAR_SUMMONER_ID_INDEX,			// �ٻ�����id
		SK_VAR_LIVE_TIME_INDEX,				// �ٻ�������������
	};

	

	virtual void onExec(GameEntity* _ge,Skill* _skill);

};




// �������ܣ���buff��ʽ����
class BuffSkillExec : public ISkillExecBase
{
public:
	virtual ~BuffSkillExec()	{}


	enum
	{
		ID = SE_TYPE_BUFF,
	};


	virtual void onExec(GameEntity* _ge,Skill* _skill);

};



// �����ٻ�
class PosSummonSkillExec : public ISkillExecBase
{
public:
	virtual ~PosSummonSkillExec(){}


	enum 
	{
		ID = SE_TYPE_POS_SUMMON,
	};


	enum
	{
		SK_VAR_SUMMONER_ID_INDEX,				// �ٻ�����id
		SK_VAR_LIVE_TIME_INDEX,					// �ٻ�������������

		TS_VAR_TARGET_DISTANCE_INDEX = 0,		// Ŀ��ѡ������������
	};


	virtual void onExec(GameEntity* _ge,Skill* _skill);
};


// �Ա�����
class SelfExplodeSkillExec : public ISkillExecBase
{
public:
	virtual ~SelfExplodeSkillExec(){}

	enum 
	{
		ID = SE_TYPE_SELF_EXPLODE,
	};

	virtual void onExec(GameEntity* _ge,Skill* _skill);
};