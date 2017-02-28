#include "TaskTrigger.h"
#include "../data/LocalPlayer.h"
#include "../data/GameData.h"
#include "RewardShow.h"

//
const int REWARD_HERO_ID = 200009;


TaskTrigger::TaskTrigger(void):
	m_task_data(0)
{
}


TaskTrigger::~TaskTrigger(void)
{
}


bool TaskTrigger::triggerTask( int _t_mask )
{
	bool bRet = false;

	if (!taskTest(_t_mask))
	{
		switch (_t_mask)
		{
		case TT_FIRST_ENTER_GAME:
			{
				auto scene = Director::getInstance()->getRunningScene();

				//
				auto& bag = LocalPlayer::getInstance()->m_bag;
				bag.addTempItem(REWARD_HERO_ID);


				auto reward_show = RewardShow::create();
				reward_show->initReward(RewardShow::RS_TYPE_CARD,REWARD_HERO_ID);
				scene->addChild(reward_show,155);

				setTaskMask(_t_mask);
				bRet = true;
			}
			break;
		default:
			break;
		}
	}

	return bRet;
}


