#pragma once
#include "Skill.h"
#include <vector>

class GameEntity;

class SkillMgr
{
public:
	SkillMgr(GameEntity* _owner);
	~SkillMgr(void);


	// 
	bool init(cfg_Obj_Attr& _cfg);


	// 获取当前使用技能
	Skill* GetCurSkill()
	{
		if (m_cur_skill_index > (int)m_active_skills.size() || m_cur_skill_index < 0)
		{
			return nullptr;
		}

		return m_active_skills[m_cur_skill_index];
	}


	// 
	bool tick(float _dt);


	// 重置技能
	void cleanSkill()
	{
		auto skill = GetCurSkill();
		if (skill)
		{
			skill->resetTargetIds();
		}
		m_cur_skill_index = -1;
	}



	/*
	 * @desc 使用某指定技能
	 * @param _sk_id 技能id
	 * @return
	 *	
	 */
	Skill* applySkill(int _sk_id);


	/*
	 * @desc 使用首个主动技能
	 * @return
	 *	
	 */
	Skill* applyFirstSkill();



private:	
	GameEntity* m_owner;
	int m_cur_skill_index;

	// 激活的技能
	std::vector<Skill*> m_active_skills;
};

