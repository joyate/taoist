#pragma once
#include "../GameDefine.h"
#include <vector>


class GameEntity;


/*
 * 伤害计算模型
 *
 */





class ISkillDamage
{
public:
	ISkillDamage(void);
	virtual ~ISkillDamage(void) = 0;


	enum
	{
		SD_BASE,
		// 通用伤害计算
		SD_HARM_BASE,
		// 基于因子来计算
		SD_SKILL_FACTOR,
		// 大僵尸，必杀技能
		SD_HARM_DEADLY,
	};


	enum
	{
		ID = SD_BASE,
	};


	void init(GameDefine::cfg_Skill_Info& sk_info)
	{
		m_skill_id = sk_info.id;
		//std::memcpy(m_val,sk_info.dt_vals,sizeof(float)*GameDefine::GD_SKILL_DAMAGE_VAR_MAX);
	}


	/*
	 * @desc 执行技能结算
	 * @param
	 * @return
	 *	
	 */
	virtual void handleDamage(GameEntity* _obj,std::vector<GameEntity*>& res) = 0;


protected:
	int m_skill_id;
	//float m_val[GameDefine::GD_SKILL_DAMAGE_VAR_MAX];


	/*
	 * @desc 辅助函数，给_obj附加受击特效
	 * @param _obj 被攻击者
	 * @return
	 *	
	 */
	void appandHitEffect(GameEntity* _obj);

};





class BaseSkillDamage : public ISkillDamage
{
public:
	virtual ~BaseSkillDamage() {}


	enum
	{
		ID = SD_HARM_BASE,
	};


	//
	virtual void handleDamage(GameEntity* _obj,std::vector<GameEntity*>& res);

};




// 致命伤害，大僵尸独有技能
class DeadlySkillDamage : public ISkillDamage
{
public:
	virtual ~DeadlySkillDamage() {}


	enum
	{
		ID = SD_HARM_DEADLY,
	};


	virtual void handleDamage(GameEntity* _obj,std::vector<GameEntity*>& res);
};

