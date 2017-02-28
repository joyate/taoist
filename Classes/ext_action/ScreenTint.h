#pragma once
#include "cocos2d.h"


USING_NS_CC;

/*
 * ��ĻЧ��
 * 
 *
 */

class GameEntity;

class ScreenTint : public ActionInterval
{
public:
	ScreenTint(void);

	static ScreenTint* create(float _interval,GLubyte _op,GameEntity* _owner);

	// һ��������layer��
	virtual void startWithTarget(Node *pTarget) override;
	
	//
	virtual ScreenTint* clone() const override;
	virtual ScreenTint* reverse(void) const override;

	virtual void stop() override;

protected:
	
	bool initWithDuration(float duration,GLubyte _op, GameEntity* _owner);
	virtual void update(float time) override;

protected:
	GLubyte m_op;
	GameEntity* m_owner;
	int m_owner_z;
};

