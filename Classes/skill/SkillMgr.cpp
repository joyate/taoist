#include "SkillMgr.h"
#include "../ai/GameEntity.h"
#include "../ai/MessageDispatcher.h"
#include "SkillInstance.h"


SkillMgr::SkillMgr(GameEntity* _owner):
	m_owner(_owner),
	m_cur_skill_index(-1)
{
	m_active_skills.reserve(GD_SKILL_NUM_MAX);
}


SkillMgr::~SkillMgr(void)
{
	for (auto sk_iter: m_active_skills)
	{
		CC_SAFE_DELETE(sk_iter);
	}

	m_active_skills.clear();
}

bool SkillMgr::init( cfg_Obj_Attr& _cfg )
{
	if (_cfg.id == 0)
	{
		CCLOG("skill init since obj id invalid");
		return false;
	}


	for (int i = 0; i < GD_SKILL_NUM_MAX; i++)
	{
		int _sk_id = _cfg.skill_ids[i];
		if (_sk_id != 0)
		{

			auto sk_info = g_SkillInfoMgr.getObject(_sk_id);
			if (!sk_info)
			{
				CCLOG("[SkillMgr::init] skill %d no data",_sk_id);
				return false;
			}

			//
			Skill* pSkill = new Skill(_sk_id,1);
			if (sk_info->sk_type == ST_PASSIVE)
			{
				auto sk_exec = ObjectInstanceMgr<ISkillExecBase>::getInstance()->getHandler(sk_info->sk_exec_type);
				if (sk_exec)
				{
					sk_exec->onExec(m_owner,pSkill);
				}
			}

			m_active_skills.push_back(pSkill);
		}
	}

	return true;
}

bool SkillMgr::tick( float _dt )
{

	if (m_cur_skill_index > 0)
	{
		return false;
	}


	int sk_size = (int)m_active_skills.size();
	for (int i = 0; i < sk_size; i++)
	{
		Skill* pSkill = m_active_skills[i];
		if (pSkill)
		{

			auto sk_info = g_SkillInfoMgr.getObject(pSkill->getID());
			if (!sk_info)
			{
				CCLOG("[Skill::tick] skill %d no data",pSkill->getID());
				return false;
			}

			if (sk_info->sk_type != ST_AUTO)
			{
				continue;
			}

			// 当前没有
			if(pSkill->tick(m_owner,_dt))
			{
				m_cur_skill_index = i;

				// 技能动作了
				state_attr sa;
				sa.skill_id = pSkill->m_skill_id;
				sa.mask |= state_attr::SA_SKILL_MASK;

				MessageDispatcher::Instance()->DispatchMsg(-1,m_owner,m_owner,M_ATK,(void*)&sa);
				return true;
			}
		}
	}

	return false;
}



Skill* SkillMgr::applySkill( int _sk_id )
{
	int sk_index = -1;
	for (auto sk_iter: m_active_skills)
	{
		sk_index++;

		if(sk_iter->getID() == _sk_id)
			break;
	}

	if (sk_index == -1)
	{
		CCLOG("obj id %d don't has skill id %d",m_owner->getID(),_sk_id);
		return nullptr;
	}

	m_cur_skill_index = sk_index;

	state_attr sa;
	sa.skill_id = _sk_id;
	sa.mask |= state_attr::SA_SKILL_MASK;

	MessageDispatcher::Instance()->DispatchMsg(-1,m_owner,m_owner,M_ATK,(void*)&sa);

	return m_active_skills[m_cur_skill_index];
}



Skill* SkillMgr::applyFirstSkill()
{
	int sk_index = -1;
	for (auto sk_iter: m_active_skills)
	{
		sk_index++;

		auto sk_info = g_SkillInfoMgr.getObject(sk_iter->getID());
		if (!sk_info)
		{
			CCLOG("[Skill::tick] skill %d no data",sk_iter->getID());
			continue;
		}

		if (sk_info->sk_type != ST_POSITIVE_IM)
		{
			continue;
		}

		m_cur_skill_index = sk_index;

		state_attr sa;
		sa.skill_id = sk_iter->getID();
		sa.mask |= state_attr::SA_SKILL_MASK;

		MessageDispatcher::Instance()->DispatchMsg(-1,m_owner,m_owner,M_ATK,(void*)&sa);
		break;
	}

	return GetCurSkill();
}
