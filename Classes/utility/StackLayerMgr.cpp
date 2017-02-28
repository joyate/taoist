#include "StackLayerMgr.h"
#include "StackLayer.h"

static StackLayerMgr* g_s_sl_instance = nullptr;

StackLayerMgr::StackLayerMgr(void)
{
}


StackLayerMgr::~StackLayerMgr(void)
{
}

StackLayerMgr* StackLayerMgr::getInstance()
{
	if (!g_s_sl_instance)
	{
		g_s_sl_instance = new StackLayerMgr;		
	}

	return g_s_sl_instance;
}

void StackLayerMgr::pushLayer( Node* _node )
{
	if (!_node)
	{
		return;
	}

	if (m_vec_sl.empty())
	{
		CC_ASSERT(false);
		CCLOG("stack layer empty");
		return;
	}

	auto sl = m_vec_sl.back();
	sl->pushNode(_node);
	
}



void StackLayerMgr::popLayer()
{
	if (m_vec_sl.empty())
	{
		CC_ASSERT(false);
		CCLOG("stack layer empty");
		return;
	}

	auto sl = m_vec_sl.back();
	sl->popNode();

	if (sl->empty())
	{
		endStackLayer();
	}

}

void StackLayerMgr::beginStackLayer()
{
	auto sl = StackLayer::create();
	m_vec_sl.pushBack(sl);
}


void StackLayerMgr::endStackLayer()
{
	m_vec_sl.popBack();
}










