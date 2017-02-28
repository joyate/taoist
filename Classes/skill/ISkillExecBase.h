#pragma once
#include "cocos2d.h"
#include "Skill.h"


USING_NS_CC;

class GameEntity;



/*
 * 技能执行模型
 *
 */




class ISkillExecBase
{
protected:
	virtual ~ISkillExecBase() = 0;

public:

	// 技能执行方式
	enum
	{
		SE_TYPE_BASE,
		SE_TYPE_NORMAL,			// 近身攻击，马上结算那种
		SE_TYPE_SHOOT,			// 发射攻击，子弹攻击，延后结算那种
		SE_TYPE_TAR_POS,		// 目标点选择技能
		SE_TYPE_ENERGY,			// 能量豆技能
		SE_TYPE_SUMMON,			// 召唤技能
		SE_TYPE_BUFF,			// 单纯释放buff
		SE_TYPE_POS_SUMMON,		// 木须肉定点召唤(恶心，由于历史原因)
		SE_TYPE_SELF_EXPLODE,	// 自爆技能，释放技能后，释放者死亡
	};


	enum
	{
		ID = SE_TYPE_BASE,
	};


	/*
	 * @desc 执行技能
	 * @param _ge 技能释放者
	 * @param _skill 技能信息
	 * @return
	 *	
	 */
	virtual void onExec(GameEntity* _ge,Skill* _skill) = 0;

};





// 普通攻击/技能攻击，以释放者为原点，行道为距离
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




// 发射型攻击
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

	// 获取发射点位置，以发射者为基准
	Vec2 getEmitPos(GameEntity* _ge);

};




// 选择目标点的技能(暂无)
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



// 能量豆技能，指使第三方释放技能
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




// 召唤技能
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
		SK_VAR_SUMMONER_ID_INDEX,			// 召唤生物id
		SK_VAR_LIVE_TIME_INDEX,				// 召唤生物生命周期
	};

	

	virtual void onExec(GameEntity* _ge,Skill* _skill);

};




// 被动技能，以buff形式呈现
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



// 定点召唤
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
		SK_VAR_SUMMONER_ID_INDEX,				// 召唤生物id
		SK_VAR_LIVE_TIME_INDEX,					// 召唤生物生命周期

		TS_VAR_TARGET_DISTANCE_INDEX = 0,		// 目标选择距离参数索引
	};


	virtual void onExec(GameEntity* _ge,Skill* _skill);
};


// 自爆技能
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