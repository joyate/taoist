#include "GuideOpInstance.h"
#include "IGuideOp.h"


template<>
ObjectInstanceMgr<IGuideOp>* ObjectInstanceMgr<IGuideOp>::m_s_instance = nullptr;


//////////////////////////////////////////////////////////////////////////


#ifndef IMPLEMENT_INSTANCE
#define IMPLEMENT_INSTANCE(_class)		\
	m_inst.insert(std::make_pair(_class::ID,new _class))

#endif




template<>
void ObjectInstanceMgr<IGuideOp>::init()
{
	IMPLEMENT_INSTANCE(GuideOpBase);
}