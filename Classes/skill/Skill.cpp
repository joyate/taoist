#include "Skill.h"
#include "../ai/GameEntity.h"
#include "SkillInstance.h"
#include "../frame/MapManager.h"
#include "../frame/BattleScene.h"

Skill::Skill(int _id,int _lvl):
	m_skill_id(_id),
	m_skill_lvl(_lvl),
	m_atk_eclapse_time(0)
{	
}


Skill::~Skill(void)
{
}




bool Skill::tick(GameEntity* _owner, float _dt )
{
	if (!_owner)
	{
		CCLOG("[Skill::tick] _owner nullptr");
		return false;
	}

	auto sk_info = g_SkillInfoMgr.getObject(m_skill_id);
	if (!sk_info)
	{
		CCLOG("[Skill::tick] skill %d no data",m_skill_id);
		return false;
	}


	m_atk_eclapse_time += _dt;

	if (sk_info->req_ling > 0)
	{
		if ( _owner->getAnger() < sk_info->req_ling)
		{
			return false;
		}
	}


	if (sk_info->atk_interval > GameDefine::MIN_FLOAT_VALUE)
	{
		if (m_atk_eclapse_time < sk_info->atk_interval)
		{
			return false;
		}
	}

	if(beginSkill(_owner))
	{
		if (sk_info->req_ling > 0)
		{
			_owner->decreaseAnger(sk_info->req_ling);
		}

		if (sk_info->atk_interval > GameDefine::MIN_FLOAT_VALUE)
		{
			m_atk_eclapse_time = 0;
		}

		return true;
	}
	
	return false;
}



bool Skill::beginSkill(GameEntity* _owner)
{
	auto sk_info = g_SkillInfoMgr.getObject(m_skill_id);
	if (!sk_info)
	{
		CCLOG("[Skill::tick] skill %d no data");
		return false;
	}

	auto _ts = ObjectInstanceMgr<ITargetSelect>::getInstance()->getHandler(sk_info->tar_sel_type);
	if (!_ts)
	{
		return false;
	}

	// 看是否有聚气
	touchAffect(GameDefine::SAM_BULLET_TIME,_owner);

	if(_ts->handleSelect(_owner,this) <= 0)
	{
		return false;
	}

	return true;
}



void Skill::touchAffect(int mask, GameEntity* _target /*= nullptr*/)
{
	auto cfg_sk_info = g_SkillInfoMgr.getObject(m_skill_id);
	if (!cfg_sk_info)
	{
		CCLOG("skill id %d no config",m_skill_id);
		return;
	}


	if (cfg_sk_info->affect_mask & mask)
	{
		switch (mask)
		{
		case GameDefine::SAM_SHAKE:
			{
				auto bs = (BattleScene*)Director::getInstance()->getRunningScene();
				bs->getCurMapMgr().shakeAffect(0.2f,6,6);
			}
			break;
		case GameDefine::SAM_BULLET_TIME:
			{
				auto bs = (BattleScene*)Director::getInstance()->getRunningScene();
				bs->getCurMapMgr().screenTintAffect(0.4f,220,_target);
			}
			break;
		default:
			break;
		}
	}
	
}

