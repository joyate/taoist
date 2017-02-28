#include "SkillInstance.h"


template<>
ObjectInstanceMgr<ITargetSelect>* ObjectInstanceMgr<ITargetSelect>::m_s_instance = nullptr;

template<>
ObjectInstanceMgr<ISkillDamage>* ObjectInstanceMgr<ISkillDamage>::m_s_instance = nullptr;


template<>
ObjectInstanceMgr<IBuffBase>* ObjectInstanceMgr<IBuffBase>::m_s_instance = nullptr;


template<>
ObjectInstanceMgr<ISkillExecBase>* ObjectInstanceMgr<ISkillExecBase>::m_s_instance = nullptr;


//////////////////////////////////////////////////////////////////////////

#ifndef IMPLEMENT_INSTANCE
#define IMPLEMENT_INSTANCE(_class)		\
	m_inst.insert(std::make_pair(_class::ID,new _class))

#endif




template<>
void ObjectInstanceMgr<ITargetSelect>::init()
{

	IMPLEMENT_INSTANCE(CommonSkillSelect);
	IMPLEMENT_INSTANCE(SummonTargetSelect);
	IMPLEMENT_INSTANCE(SelfTargetSelect);
	IMPLEMENT_INSTANCE(RectTargetSelect);

}



template<>
void ObjectInstanceMgr<ISkillDamage>::init()
{

	IMPLEMENT_INSTANCE(BaseSkillDamage);
	IMPLEMENT_INSTANCE(DeadlySkillDamage);

}



template<>
void ObjectInstanceMgr<IBuffBase>::init()
{

	IMPLEMENT_INSTANCE(AttackSpeedAffect);
	IMPLEMENT_INSTANCE(SpeedAffect);
	IMPLEMENT_INSTANCE(ReborthAffect);
	IMPLEMENT_INSTANCE(DeadthBornAffect);
	IMPLEMENT_INSTANCE(AttrChangeAffect);
}




template<>
void ObjectInstanceMgr<ISkillExecBase>::init()
{

	IMPLEMENT_INSTANCE(NormalSkillExec);
	IMPLEMENT_INSTANCE(ShootSkillExec);
	IMPLEMENT_INSTANCE(TargetPosSkillExec);
	IMPLEMENT_INSTANCE(EnergyDouSkillExec);
	IMPLEMENT_INSTANCE(SummonSkillExec);
	IMPLEMENT_INSTANCE(BuffSkillExec);
	IMPLEMENT_INSTANCE(PosSummonSkillExec);
	IMPLEMENT_INSTANCE(SelfExplodeSkillExec);

}




