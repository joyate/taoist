#include "SkillDamage.h"
#include "DamageCalc.h"
//#include "../ai/GameEntity.h"
#include "../data/GameData.h"
#include "../component/Effect.h"
#include "../utility/Utility.h"

ISkillDamage::ISkillDamage(void):
	m_skill_id(0)
{
	//memset(m_val,0,sizeof(float)*GameDefine::GD_SKILL_DAMAGE_VAR_MAX);
}


ISkillDamage::~ISkillDamage(void)
{

}



void ISkillDamage::appandHitEffect( GameEntity* _obj )
{
	if (!_obj)
	{
		CCLOG("[appandHitEffect] obj null");
		return;
	}


	auto cfg_sk_info = g_SkillInfoMgr.getObject(m_skill_id);
	if (!cfg_sk_info)
	{
		CCLOG("skill id %d no data",m_skill_id);
		return;
	}

	// ÓÐhit_effectÅäÖÃ
	if (strcmp(cfg_sk_info->hit_effect,"null"))
	{

		std::vector<std::string> out;
		if(Utility::parseEffect(cfg_sk_info->hit_effect,out))
		{
			auto eff = Effect::create();
			eff->createEffect(out[0].c_str());
			eff->attachGameObj(_obj,out[1]);
			eff->playEffect(out[1].c_str());
		}
	}

}


void BaseSkillDamage::handleDamage( GameEntity* _obj,std::vector<GameEntity*>& res)
{
	if (res.empty())
	{
		CCLOG("[handleDamage] has no target");
		return;
	}


	int size = (int)res.size();
	for (int i = 0; i < size; i++)
	{
		GameEntity* _target = res[i];
		if (!_target)
		{
			continue;
		}

		appandHitEffect(_target);

		BaseDamageCalc dc(_obj,_target,m_skill_id);
		dc.doDamage();

	}


}



void DeadlySkillDamage::handleDamage( GameEntity* _obj,std::vector<GameEntity*>& res )
{
	if (res.empty())
	{
		CCLOG("[handleDamage] has no target");
		return;
	}


	int size = (int)res.size();
	for (int i = 0; i < size; i++)
	{
		GameEntity* _target = res[i];
		if (!_target)
		{
			continue;
		}

		//
		appandHitEffect(_target);

		//
		DeadlyDamageCalc ddc(_obj,_target,m_skill_id);
		ddc.doDamage();

	}

}
