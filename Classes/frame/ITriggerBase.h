#pragma once
#include "cocos2d.h"
#include "../GameDefine.h"

USING_NS_CC;

/*
 * ´¥·¢Æ÷Ïà¹Ø
 * 
 *
 */




class ITriggerBase
{
public:
	virtual ~ITriggerBase(void) = 0;


	enum
	{
		TRG_ID_NONE,
		TRG_ID_GAME_LOSE,
		TRG_ID_GAME_WIN,
	};


	enum
	{
		ID = TRG_ID_NONE,
	};


	virtual void update(GameDefine::tTriggerInfo& _ti,float delta) = 0;


protected:
	//
	//virtual void execute(Node* _obj) = 0;

};





class GameLoseTrigger : public ITriggerBase
{
public:
	~GameLoseTrigger();

	enum
	{
		ID = TRG_ID_GAME_LOSE,
	};
	

	//
	virtual void update(GameDefine::tTriggerInfo& _ti,float delta);

};




class GameWinTrigger : public ITriggerBase
{

public:
	~GameWinTrigger() {}

	enum
	{
		ID = TRG_ID_GAME_WIN,
	};


	//
	virtual void update(GameDefine::tTriggerInfo& _ti,float delta);

};





