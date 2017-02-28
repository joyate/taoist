#include "ScreenTint.h"
#include "../frame/BattleScene.h"

ScreenTint::ScreenTint(void):
	m_op(0),
	m_owner(nullptr)
{
}

ScreenTint* ScreenTint::clone() const 
{
	return nullptr;
}

ScreenTint* ScreenTint::reverse( void ) const 
{
	return nullptr;
}

void ScreenTint::startWithTarget( Node *pTarget )
{
	ActionInterval::startWithTarget(pTarget);
	if (!pTarget || !m_owner)
	{
		return;
	}

	pTarget->setOpacity(m_op);
	m_owner->setLocalZOrder(pTarget->getLocalZOrder()+1);

	auto bs = (BattleScene*)Director::getInstance()->getRunningScene();
	bs->specialPause(m_owner->getID());
}

ScreenTint* ScreenTint::create( float _interval,GLubyte _op, GameEntity* _owner )
{
	auto action = new ScreenTint();
	if(!action->initWithDuration(_interval,_op,_owner))
	{
		CC_SAFE_DELETE(action);
		return nullptr;
	}
	action->autorelease();
	return action;
}

bool ScreenTint::initWithDuration( float duration,GLubyte _op,GameEntity* _owner )
{
	if (!_owner)
	{
		return false;
	}

	ActionInterval::initWithDuration(duration);
	m_op = _op;
	m_owner = _owner;
	m_owner_z = _owner->getLocalZOrder();
	return true;
}

void ScreenTint::update( float time )
{
	if (_target)
	{
		_target->setOpacity(m_op*(1-tweenfunc::circEaseIn(time)));
	}
}

void ScreenTint::stop()
{
	ActionInterval::stop();

	if(m_owner)
	{
		m_owner->setLocalZOrder(m_owner_z);
	}

	auto bs = (BattleScene*)Director::getInstance()->getRunningScene();
	bs->specialResume();
}

