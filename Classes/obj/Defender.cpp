#include "Defender.h"
#include "../data/GameData.h"
#include "cocostudio/CocoStudio.h"
#include "../ai/AIState.h"
#include "../ai/MessageDispatcher.h"


using namespace GameDefine;
using namespace cocostudio;


Defender::Defender(void):
	m_rect_index(0)
{
	m_type = OT_DEFENDER|OT_SOLDIER;
	m_e_dir = DIR_R;
	m_arder_elapse_time = 0.0f;

	//
	if (_stateMechine)
	{
		_stateMechine->SetCurrentState(DefenderIdleState::getInstance());
	}

	//_custom_event = EventListenerCustom::create(ANIMATION_EVENT,CC_CALLBACK_1(Defender::animEventCallback,this));
	//_eventDispatcher->addEventListenerWithFixedPriority(_custom_event, 1);
}



Defender::~Defender(void)
{
}

bool Defender::initCardId( int _tid)
{

	if (!GameEntity::initCardId(_tid))
	{
		return false;
	}


	
	return true;
}


void Defender::fixDir()
{
	if (m_e_dir != DIR_R)
	{
		auto _body = m_char_root->getChildByTag(TAG_GNT_BODY);
		if (!_body)
		{
			return;
		}

		_body->setScaleX(_body->getScaleX() * -1);
		m_e_dir = DIR_R;
	}
}


void Defender::update( float delta )
{
	GameEntity::update(delta);

	// 特殊更新

}



void Defender::idle_tick( float dt )
{
	bool bRet = m_skillMgr.tick(dt);
	if (!bRet)
	{
		m_arder_elapse_time += dt;
		if (m_arder_elapse_time >= GameDefine::GD_ARDER_INTERVAL_TIME*5)
		{
			MessageDispatcher::Instance()->DispatchMsg(-1,this,this,M_ARDER,nullptr);
			m_arder_elapse_time = 0;
		}
	}
}



bool Defender::changeState( unsigned int mask, const Telegram& telegram )
{
	bool bRet = false;

	switch(telegram.Msg)
	{
	case M_RUN:
		{

		}
		break;
	case M_REBORN:
	case M_IDLE:
		{
			_stateMechine->ChangeState(DefenderIdleState::getInstance());
			bRet = true;
		}
		break;
	case M_ARDER:
		{
			_stateMechine->ChangeState(DefenderArderState::getInstance());
			bRet = true;
		}
		break;
	case M_ATK:
		{
			_stateMechine->ChangeState(ObjAttackState::getInstance());	
			bRet = true;
		}
		break;
	default:
		break;
	}

	// 本处没处理，往上传递
	if (!bRet)
	{
		return GameEntity::changeState(mask,telegram);
	}

	return true;
}



GameDefine::Dir Defender::flipDir( GameDefine::Dir _new_dir )
{
	CC_ASSERT(_new_dir >= GameDefine::DIR_L && _new_dir < GameDefine::DIR_MAX);
	switch(_new_dir)
	{
	case GameDefine::DIR_L:
		return (GameDefine::Dir)(_new_dir - m_e_dir - 1);
	default:
		return _new_dir;
	}
	return _new_dir;
}



void Defender::usePrivateSkill()
{
	auto skill = m_skillMgr.applyFirstSkill();
	if (skill)
	{
		skill->beginSkill(this);
	}
}


