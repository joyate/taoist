#include "IGuideOp.h"
#include "MsgBox.h"
#include "GuideLayer.h"
#include "../data/LocalPlayer.h"
//#include "../game_ui/NoticeBoard.h"
#include "RewardShow.h"

IGuideOp::~IGuideOp(void)
{
}





void GuideOpBase::onExec( const GameDefine::cfg_Guide_Info& _cfg_gi )
{
	auto scene = Director::getInstance()->getRunningScene();

	auto mask = GuideLayer::create();
	mask->initConfig(_cfg_gi.id);
	mask->setTag(GuideLayer::TAG_GUIDE_NODE);
	scene->addChild(mask,GuideLayer::GUIDE_NODE_LAYER);
}

