#pragma once
#include "cocos2d.h"
#include "Defender.h"
#include "../skill/SkillMgr.h"
#include "../ai/AIState.h"

class Hero : public Defender
{
public:
	Hero(void);
	virtual ~Hero(void);


	//////////////////////////////////////////////////////////////////////////
	// 通用行为
	//////////////////////////////////////////////////////////////////////////

	virtual void update(float delta);


	//////////////////////////////////////////////////////////////////////////
	// 个性行为
	//////////////////////////////////////////////////////////////////////////
	
	// 走向
	virtual void runTo( const Vec2& _dest );



	// 死亡
	virtual void onDead() override;


	// 是否是行走状态
	virtual bool isWalking() override
	{
		if (_stateMechine)
		{
			return _stateMechine->isInState(*HeroRunState::getInstance());
		}
		return false;
	}


	
	/*
	 * @desc 技能消耗
	 * @param _sk_info 技能配置数据
	 * @param _bCost 是否扣值
	 * @return 检查/扣值成功 返回true
	 *	
	 */
	bool skillCost(const GameDefine::cfg_Skill_Info* _sk_info,bool _bCost = false);

	/*
	 * @desc 使用技能
	 * @param _sk_id 技能id，
	 * @param _sk_lvl 技能等级
	 * @return 当前使用的技能
	 *	
	 */
	Skill* useSkill(int _sk_id,int _sk_lvl);


	// 
	CREATE_FUNC(Hero);

protected:


	// 灵气更新
	void ghostUpdate(float delta);


	//
	virtual bool changeState( unsigned int mask, const Telegram& telegram ) override;


	// 闲置回调
	/*virtual */void idleCallback();


private:



};

