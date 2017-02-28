#pragma once
#include "../ai/GameEntity.h"
#include "../ai/AIState.h"


/*
 * 防御召唤者
 */


template< typename SpecialBase >
class Summoner : public SpecialBase
{
public:
	Summoner(void):
		m_live_time(0.0f),
		m_owner_id(0)
	{
		SpecialBase::m_type = GameEntity::OT_SUMMONER;
	}


	virtual ~Summoner(void)
	{

	}



	//////////////////////////////////////////////////////////////////////////
	// 通用接口
	//////////////////////////////////////////////////////////////////////////

	//
	virtual void update(float delta) override
	{
		SpecialBase::update(delta);

		if (m_live_time > 0)
		{
			m_live_time -= delta;
			if (m_live_time < 0)
			{
				SpecialBase::onDead();
			}
		}
	}


	// 设置
	void setLifeTime(float _live_time)
	{
		m_live_time = _live_time;
	}



	//////////////////////////////////////////////////////////////////////////
	// 特色接口
	//////////////////////////////////////////////////////////////////////////


	// 获取主人id
	int getOwnerID() const	{ return m_owner_id;}




	// 
	virtual void idle_tick(float dt) override;
	
	

	void initFromObj(const GameEntity* _owner )
	{
		//
		SpecialBase::m_type |= _owner->getMainType();

		if (SpecialBase::m_type & GameEntity::OT_DEFENDER)
		{
			SpecialBase::m_e_dir = DIR_R;
			SpecialBase::m_type |= GameEntity::OT_DEFENDER;
			if (SpecialBase::_stateMechine)
			{
				SpecialBase::_stateMechine->SetCurrentState(DefenderIdleState::getInstance());
			}

		}else if(SpecialBase::m_type & GameEntity::OT_OFFENSIVE)
		{
			SpecialBase::m_e_dir = DIR_L;
			SpecialBase::m_type |= GameEntity::OT_OFFENSIVE;
			if (SpecialBase::_stateMechine)
			{
				SpecialBase::_stateMechine->SetCurrentState(NpcIdleState::getInstance());
			}
		}
	}


	virtual bool isBorning() override
	{
		if (SpecialBase::_stateMechine)
		{
			return SpecialBase::_stateMechine->isInState(*SummonerBorthState::getInstance());
		}
		return false;
	}



protected:


	virtual bool changeState( unsigned int mask, const Telegram& telegram ) override;



private:
	
	// 成长时间
	float m_live_time;
	int m_owner_id;

};




template<typename T>
Summoner<T>* createSummoner(const T* _owner)
{
	auto sum_obj = new Summoner<T>();
	if(sum_obj)
	{
		sum_obj->initFromObj(_owner);
		sum_obj->autorelease();
		return sum_obj;
	}

	return nullptr;
}
