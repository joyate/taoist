#include "Summoner.h"
#include "../ai/AIState.h"
#include "../ai/MessageDispatcher.h"
#include "Defender.h"
#include "Zombie.h"


template<>
bool Summoner<Defender>::changeState( unsigned int mask, const Telegram& telegram )
{
	bool bRet = false;
	switch(telegram.Msg)
	{
	case M_BORN:
		{
			_stateMechine->ChangeState(SummonerBorthState::getInstance());
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


template<>
bool Summoner<Zombie>::changeState( unsigned int mask, const Telegram& telegram )
{
	bool bRet = false;
	switch(telegram.Msg)
	{
	case M_BORN:
		{
			_stateMechine->ChangeState(SummonerBorthState::getInstance());
			bRet = true;
		}
		break;
	default:
		break;
	}

	// 本处没处理，往上传递
	if (!bRet)
	{
		return Zombie::changeState(mask,telegram);
	}

	return true;
}



template<>
void Summoner<Defender>::idle_tick( float dt )
{
	m_skillMgr.tick(dt);
}


template<>
void Summoner<Zombie>::idle_tick(float dt)
{
	Zombie::idle_tick(dt);
}
