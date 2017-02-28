#include "DamageCalc.h"
#include "../ai/GameEntity.h"
#include "ObjectAction.h"
#include "../ai/MessageDispatcher.h"
#include "../data/LocalPlayer.h"
#include "../component/GuideFilterMgr.h"

void BaseDamageCalc::doDamage()
{
	std::vector<float> res;

	preCalc(res);
	onCalc(res);
	postCalc(res);
}

void BaseDamageCalc::onCalc( std::vector<float>& _res )
{
	if (_res.empty() || _res.size() < CALC_RES_MAX)
	{
		return;
	}

	float dmg = _res[DAMAGE_INDEX];
	if (dmg > 0)
	{
		// ��Ѫ
		m_tar->decreaseHp(dmg);

		// skill guide 
		if (m_tar->getType() & GameEntity::OT_HERO)
		{
			GuideFilterMgr::getInstance().checkGuideFilter(GuideFilterMgr::GFN_BATTLE_HERO_NORMAL_SKILL_USE);
		}

		// Ʈ��
		auto bf = BloodFly::create();
		bf->initialize(dmg);
		bf->fly(m_tar,_res[CRITICAL_INDEX] >= 0.9999f);

		//
		if (!m_tar->isAlive())
		{

			// ������
			if (m_tar->getMainType() & GameEntity::OT_DEFENDER)
			{
				auto& tfi = LocalPlayer::getInstance()->m_temp_fight_info;
				tfi.defender_dead_cnt++;
			}

			if (m_src->getSubType() & GameEntity::OT_HERO)
			{
				const auto obj_attr = g_ObjInfoMgr.getObject(m_tar->getObjId());
				if (obj_attr && obj_attr->ghost_drop > 0)
				{
					auto& tfi = LocalPlayer::getInstance()->m_temp_fight_info;
					tfi.hero_info.base_ghost += obj_attr->ghost_drop;

					// ����һ��
					Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GameDefine::BATTLE_HERO_INFO_UPDATE_EVENT);
				}
			}

			m_tar->onBuffEvent(BuffMgr::BEM_EVENT_DEAD);
			m_src->onBuffEvent(BuffMgr::BEM_EVENT_KILL);
			return;
		}

	}
}



void BaseDamageCalc::preCalc( std::vector<float>& _res )
{
	if (!m_tar || !m_src)
	{
		return;
	}

	auto cfg_sk_info = g_SkillInfoMgr.getObject(m_sk_id);


	float dmg = 0;
	if (cfg_sk_info->sk_dmg_type == GameDefine::SK_DMG_MAG)
	{
		dmg = MAX(1,m_src->m_attr.m_mag_atk + cfg_sk_info->sk_vals[SRC_SKILL_DMG_INDEX] - m_tar->m_attr.m_mag_def);
	}
	else
	{
		dmg = MAX(1,m_src->m_attr.m_phy_atk + cfg_sk_info->sk_vals[SRC_SKILL_DMG_INDEX] - m_tar->m_attr.m_phy_def);
	}

	
	
	float base_cri = BaseDefine::HUNDRED_BASE * CCRANDOM_0_1();
	if (m_src->m_attr.m_atk_cri > base_cri)
	{
		dmg *= 1.5;
		_res.push_back(1.0f);
	}
	else
	{
		_res.push_back(0.f);
	}

	_res.push_back(dmg);
}



void BaseDamageCalc::postCalc( std::vector<float>& _res )
{
	if (!m_tar)
	{
		return;
	}

	// ����buff
	// �е�buff��fade״̬�����ģ����п���������������£��е�buff
	//if (m_tar->isAlive())
	{
		auto sk_data = g_SkillInfoMgr.getObject(m_sk_id);
		if (sk_data && sk_data->buff_id > 0)
		{
			m_tar->m_buffMgr.handleGotBuff(sk_data->buff_id,m_src);
		}
	}
}



void DeadlyDamageCalc::onCalc( std::vector<float>& _res )
{
	if (!m_src || !m_tar)
	{
		return;
	}


	// ��Ѫ
	int dmg_hp = m_tar->m_attr.m_hp;
	m_tar->decreaseHp(dmg_hp);

	// Ʈ��
	auto bf = BloodFly::create();
	bf->initialize(dmg_hp);
	bf->fly(m_tar);

	// �¼�
	if (!m_tar->isAlive())
	{
		m_tar->onBuffEvent(BuffMgr::BEM_EVENT_DEAD);
		m_src->onBuffEvent(BuffMgr::BEM_EVENT_KILL);
	}

}




void CureCalc::onCalc( std::vector<float>& _res )
{
	if (!m_src || !m_tar)
	{
		return;
	}


	auto sk_data = g_SkillInfoMgr.getObject(m_sk_id);

}




void SelfMurderCalc::onCalc( std::vector<float>& _res )
{
	if (_res.empty() || _res.size() < CALC_RES_MAX)
	{
		return;
	}

	float dmg = _res[DAMAGE_INDEX];
	if (dmg > 0)
	{
		// ��Ѫ
		m_tar->decreaseHp(dmg);

		// Ʈ��
		auto bf = BloodFly::create();
		bf->initialize(dmg);
		bf->fly(m_tar,_res[CRITICAL_INDEX] >= 0.9999f);

		//
		if (!m_tar->isAlive())
		{
			m_tar->onBuffEvent(BuffMgr::BEM_EVENT_DEAD);
			m_src->onBuffEvent(BuffMgr::BEM_EVENT_KILL);
		}
	}


	// ��Ѫ
	int dmg_hp = m_src->m_attr.m_hp;
	m_src->decreaseHp(dmg_hp);

	// ����Ա��㲻�㱻ɱ������
	/*if (!m_src->isAlive())
	{
	m_src->onBuffEvent(BuffMgr::BEM_EVENT_DEAD);
	}*/

}
