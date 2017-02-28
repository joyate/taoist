#include "TriggerInstance.h"



template<>
ObjectInstanceMgr<ITriggerBase>* ObjectInstanceMgr<ITriggerBase>::m_s_instance = nullptr;





template<>
void ObjectInstanceMgr<ITriggerBase>::init()
{

#define IMPLEMENT_INSTANCE(target_sel)		\
	m_inst.insert(std::make_pair(target_sel::ID,new target_sel))


	IMPLEMENT_INSTANCE(GameLoseTrigger);
	IMPLEMENT_INSTANCE(GameWinTrigger);
}