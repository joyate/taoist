#include "Hero.h"
#include "../data/GameData.h"
#include "cocostudio/CocoStudio.h"
#include "../ai/Telegram.h"
#include "../ai/AIState.h"
#include "../ai/MessageDispatcher.h"
#include "../data/LocalPlayer.h"
#include "../component/PopTipManager.h"
#include "../data/MsgManager.h"



using namespace GameDefine;
using namespace cocostudio;



Hero::Hero(void)
{
	m_type = OT_HERO | OT_DEFENDER;

}


Hero::~Hero(void)
{
}



void Hero::runTo( const Vec2& _dest )
{
	GameEntity::runTo(_dest);

	const Vec2 &curPos = getPosition();
	float dis = curPos.distance(_dest);

	MoveTo *moveTo = MoveTo::create(dis / m_attr.m_speed, _dest);
	Action *action = Sequence::createWithTwoActions(moveTo, CallFunc::create(CC_CALLBACK_0(Hero::idleCallback,this)));

	if (!action)
	{
		CCLOG("action create failed");
		return;
	}

	this->stopAllActions();
	this->runAction(action);
}



void Hero::update( float delta )
{
	Defender::update(delta);

	// 特殊更新
	if (isAlive())
	{
		//
		ghostUpdate(delta);
	}

}

bool Hero::changeState( unsigned int mask, const Telegram& telegram )
{
	bool bRet = false;

	switch(telegram.Msg)
	{
	case M_RUN:
		{

			GameDefine::state_attr* info = (GameDefine::state_attr *)(telegram.ExtraInfo);

			CC_ASSERT(info->mask & (GameDefine::state_attr::SA_DEST_MASK));
			if (info->mask & GameDefine::state_attr::SA_DEST_MASK)
			{
				setDest(info->dest);
			}

			_stateMechine->ChangeState(HeroRunState::getInstance());	
			bRet = true;
		}
		break;
	default:
		break;
	}

	// 本处没处理，往上传递
	if (!bRet)
	{
		return Defender::changeState(mask,telegram);
	}

	return true;
}



void Hero::idleCallback()
{
	Vec2 pos = getPosition();
	MessageDispatcher::Instance()->DispatchMsg(-1, this, this, M_IDLE, &pos);
}




Skill* Hero::useSkill( int _sk_id,int _sk_lvl )
{

	auto skill = m_skillMgr.applySkill(_sk_id);
	if (skill)
	{
		skill->beginSkill(this);
	}
	
	return skill;
}




void Hero::ghostUpdate( float delta )
{
	static float sec_elapse_time = 0;
	sec_elapse_time += delta;
	if (sec_elapse_time > 1)
	{
		sec_elapse_time = 0;
		// 刷新hero info;
		_eventDispatcher->dispatchCustomEvent(GameDefine::BATTLE_HERO_INFO_UPDATE_EVENT,this);
	}
}


void Hero::onDead()
{
	// 刷新hero info;
	_eventDispatcher->dispatchCustomEvent(GameDefine::BATTLE_HERO_INFO_UPDATE_EVENT,this);

	//
	Defender::onDead();
}



bool Hero::skillCost( const GameDefine::cfg_Skill_Info* _sk_info,bool _bCost /*= false*/ )
{
	do 
	{
		auto& hi = LocalPlayer::getInstance()->m_temp_fight_info.hero_info;
		if (!hi.costGhost(_sk_info->req_ling,_bCost))
		{
			PopTipManager::getInstance()->popTips(MsgManager::SKILL_COST_NOT_ENOUGH);
			break;
		}

		return true;

	} while (false);

	return false;
}






