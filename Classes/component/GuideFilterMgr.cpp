#include "GuideFilterMgr.h"
#include "GuideOpInstance.h"
#include "../data/LocalPlayer.h"
#include "../data/GameData.h"


GuideFilterMgr* GuideFilterMgr::s_gf_mgr = nullptr;


GuideFilterMgr::GuideFilterMgr(void)
{
}


GuideFilterMgr::~GuideFilterMgr(void)
{
}


GuideFilterMgr& GuideFilterMgr::getInstance()
{
	if (!s_gf_mgr)
	{
		s_gf_mgr = new GuideFilterMgr();
	}

	return *s_gf_mgr;
}


void GuideFilterMgr::checkGuideFilter(int _cur_guide_id)
{
	auto& gi = LocalPlayer::getInstance()->m_guide_info;
	// 已经引导过
	if (gi.last_guide_id >= _cur_guide_id)
	{
		return;
	}

	const auto& cfg_gi = g_GuideInfoMgr.getObject(_cur_guide_id);
	if (!cfg_gi)
	{
		CCLOG("guide id %d has no data",_cur_guide_id);
		return;
	}

	// 判断一下
	if (cfg_gi->req_guide_id != 0 && cfg_gi->req_guide_id != gi.last_guide_id)
	{
		return;
	}

	auto handler = tGuideOpMgr::getInstance()->getHandler(cfg_gi->op_type);
	if (!handler)
	{
		CCLOG("guide op type %d not found",cfg_gi->op_type);
		return;
	}

	handler->onExec(*cfg_gi);

}


