#pragma once
#include "GameEntity.h"
#include "State.h"

/*
*	AI ÊµÀý
*
*
*/


class DefenderIdleState : public State<GameEntity>
{
public:

	static DefenderIdleState *getInstance();
	virtual void Enter(GameEntity*);
	virtual void Execute(GameEntity*, float);
	virtual void Exit(GameEntity*);
	virtual bool OnMessage(GameEntity*, const Telegram&);

};



// ÐÝÏÐ×´Ì¬
class DefenderArderState : public State<GameEntity>
{
public:

	static DefenderArderState* getInstance();


	virtual void Enter(GameEntity*);
	virtual void Execute(GameEntity*, float) {}
	virtual void Exit(GameEntity*) {}
	virtual bool OnMessage(GameEntity*, const Telegram&);
};





class NpcIdleState : public State<GameEntity>
{
public:

	static NpcIdleState *getInstance();
	virtual void Enter(GameEntity*);
	virtual void Execute(GameEntity*, float);
	virtual void Exit(GameEntity*);
	virtual bool OnMessage(GameEntity*, const Telegram&);

};




class ObjBeAttackState : public State<GameEntity>
{
public:

	static ObjBeAttackState *getInstance();
	virtual void Enter(GameEntity*);
	virtual void Execute(GameEntity*, float);
	virtual void Exit(GameEntity*);
	virtual bool OnMessage(GameEntity*, const Telegram&);
};



class NpcRunState : public State<GameEntity>
{
public:
	static NpcRunState *getInstance();
	virtual void Enter(GameEntity*);
	virtual void Execute(GameEntity*, float _df);
	virtual void Exit(GameEntity*);
	virtual bool OnMessage(GameEntity*, const Telegram&);

};


// ÌØÊâ
class HeroRunState : public State<GameEntity>
{
public:
	static HeroRunState *getInstance();
	virtual void Enter(GameEntity*);
	virtual void Execute(GameEntity*, float _df);
	virtual void Exit(GameEntity*);
	virtual bool OnMessage(GameEntity*, const Telegram&);

};



class NpcAttackState : public State<GameEntity>
{
public:

	static NpcAttackState *getInstance();
	virtual void Enter(GameEntity*);
	virtual void Execute(GameEntity*, float _df);
	virtual void Exit(GameEntity*);
	virtual bool OnMessage(GameEntity*, const Telegram&);
};



class ObjAttackState : public State<GameEntity>
{
public:

	static ObjAttackState *getInstance();
	virtual void Enter(GameEntity*);
	virtual void Execute(GameEntity*, float _df);
	virtual void Exit(GameEntity*);
	virtual bool OnMessage(GameEntity*, const Telegram&);

};








class ObjDeadState : public State<GameEntity>
{
public:
	static ObjDeadState *getInstance();
	virtual void Enter(GameEntity*);
	virtual void Execute(GameEntity*, float _df);
	virtual void Exit(GameEntity*);
	virtual bool OnMessage(GameEntity*, const Telegram&);

};




class BulletRunState : public State<GameEntity>
{
public:
	static BulletRunState *getInstance();
	virtual void Enter(GameEntity*);
	virtual void Execute(GameEntity*, float _df);
	virtual void Exit(GameEntity*);
	virtual bool OnMessage(GameEntity*, const Telegram&);
};


// ÕÙ»½Îï³öÀ´×´Ì¬
class SummonerBorthState : public State<GameEntity>
{
public:
	static SummonerBorthState* getInstance();

	virtual void Enter(GameEntity*);
	virtual void Execute(GameEntity*, float _df) {}
	virtual void Exit(GameEntity*) {}
	virtual bool OnMessage(GameEntity*, const Telegram&);
};