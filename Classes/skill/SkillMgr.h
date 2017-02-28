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


	// ��ȡ��ǰʹ�ü���
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


	// ���ü���
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
	 * @desc ʹ��ĳָ������
	 * @param _sk_id ����id
	 * @return
	 *	
	 */
	Skill* applySkill(int _sk_id);


	/*
	 * @desc ʹ���׸���������
	 * @return
	 *	
	 */
	Skill* applyFirstSkill();



private:	
	GameEntity* m_owner;
	int m_cur_skill_index;

	// ����ļ���
	std::vector<Skill*> m_active_skills;
};

