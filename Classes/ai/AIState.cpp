#include "AIState.h"
#include "BaseDefine.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "../utility/Utility.h"


#include "../obj/Hero.h"
#include "../obj/Zombie.h"
#include "../obj/Bullet.h"


using namespace BaseDefine;


DefenderIdleState * DefenderIdleState::getInstance()
{
	static DefenderIdleState _dis;
	return &_dis;
}

bool DefenderIdleState::OnMessage( GameEntity* _ge, const Telegram& _msg)
{
	if (!_ge)
	{
		return false;
	}

	// 状态掩码，该状态下可以接受那些状态
	// M_IDLE 只应该在初始化才有
	int mask = M_ATK | M_RUN | M_IDLE | M_BEATK | M_DEAD | M_ARDER | M_BORN;
	if ( !(mask & _msg.Msg) )
	{
		CCLOG("idle state receive %d state msg",_msg.Msg);
		return false;
	}

	return _ge->changeState(M_IDLE,_msg);
}

void DefenderIdleState::Enter( GameEntity* _ge)
{
	if(!_ge)
	{
		return;
	}
	
	CCLOG("obj %d enter state: %d",_ge->getID(),M_IDLE);
	_ge->playAnim(AT_IDLE);

}

void DefenderIdleState::Execute( GameEntity* _ge, float _dt)
{
	if (!_ge)
	{
		return;
	}

	_ge->idle_tick(_dt);

}

void DefenderIdleState::Exit( GameEntity* _ge)
{
	if (!_ge)
	{
		return;
	}

	CCLOG("obj %d exit state: %d",_ge->getID(),M_IDLE);

	// 其他处理



	// 停止相关动作
	_ge->stopAnim();

}



NpcRunState * NpcRunState::getInstance()
{
	static NpcRunState _nrs;
	return &_nrs;
}

void NpcRunState::Enter( GameEntity* _ge)
{
	if (!_ge)
	{
		return;
	}

	CCLOG("obj %d enter state: %d",_ge->getID(),M_RUN);

	auto _zb = dynamic_cast<Zombie*>(_ge);
	if (_zb)
	{
		_zb->runTo(_zb->getDest());
		_zb->playAnim(AT_WALK);
	}

}

void NpcRunState::Execute( GameEntity* _ge, float _df )
{
	if (!_ge)
	{
		return;
	}

	//
	auto _zb = dynamic_cast<Zombie*>(_ge);
	if (_zb)
	{
		_zb->run_tick(_df);
	}

}

void NpcRunState::Exit( GameEntity* _ge)
{
	if(!_ge)
	{
		return;
	}

	CCLOG("obj %d exit state: %d",_ge->getID(),M_RUN);

	{
		_ge->stopAllActions();

		// 检查下朝向
		_ge->fixDir();
	}
}

bool NpcRunState::OnMessage( GameEntity* _npc, const Telegram& _msg)
{
	if (!_npc)
	{
		return false;
	}

	int mask = M_IDLE | M_ATK | M_RUN | M_DEAD;
	CC_ASSERT(mask & _msg.Msg);
	if ( !(mask & _msg.Msg) )
	{
		CCLOG(" NpcRunState receive state:%d",_msg.Msg);
		return false;
	}

	return _npc->changeState(M_RUN, _msg);
}

NpcAttackState * NpcAttackState::getInstance()
{
	static NpcAttackState _nas;
	return &_nas;
}

void NpcAttackState::Enter( GameEntity* _ge)
{
	if(!_ge)
	{
		CCLOG("game entity nullptr");
		return;
	}

	CCLOG("obj %d enter state: %d",_ge->getID(),M_ATK);

	_ge->setLocalZOrder(_ge->getLocalZOrder() + GameEntity::ATTACK_Z_OFFSET);

	// 施法动作
	const Skill* pSkill = _ge->GetCurSkill();
	if (pSkill)
	{
		auto cfg_skill_info = g_SkillInfoMgr.getObject(pSkill->getID());

		if (cfg_skill_info->src_act_name[0] != 0)
		{
			_ge->playAnim(cfg_skill_info->src_act_name,-1,1);
		}
	}

	
}

void NpcAttackState::Execute( GameEntity* _ge, float _df )
{
	if (!_ge)
	{
		CCLOG(" game entity nullptr");
		return;
	}


	auto _zb = dynamic_cast<Zombie*>(_ge);
	if (_zb)
	{

	}

}

void NpcAttackState::Exit( GameEntity* _ge)
{
	if (!_ge)
	{
		return;
	}
	CCLOG("obj %d exit state: %d",_ge->getID(),M_ATK);


	_ge->setLocalZOrder(_ge->getLocalZOrder() - GameEntity::ATTACK_Z_OFFSET);

	//
	auto _zb = dynamic_cast<Zombie*>(_ge);
	if (_zb)
	{
		//
		if (_zb->getTarget() != nullptr)
		{
			_zb->setTarget(nullptr);
		}

		_zb->stopAnim();
	}

}

bool NpcAttackState::OnMessage( GameEntity* _ge, const Telegram& _msg)
{
	// 这里处理排斥问题
	if (_msg.Msg == M_ATK)
	{
		CCLOG("reatk, now skill id: %d",_msg.Msg);
		return false;
	}

	int mask = M_DEAD | M_BEATK | M_RUN | M_IDLE;
	CC_ASSERT(mask & _msg.Msg);

	if ( !(mask & _msg.Msg) )
	{
		CCLOG("NpcAttackState receive state:%d",_msg.Msg);
		return false;
	}

	return _ge->changeState(M_ATK, _msg);
}


//////////////////////////////////////////////////////////////////////////

ObjDeadState * ObjDeadState::getInstance()
{
	static ObjDeadState _ods;
	return &_ods;
}

void ObjDeadState::Enter( GameEntity* _ge)
{
	if (!_ge)
	{
		return;
	}

	CCLOG("obj %d enter state: %d",_ge->getID(),M_DEAD);

	_ge->playAnim(AT_DEAD,-1,0);
}

bool ObjDeadState::OnMessage( GameEntity* _ge, const Telegram& _msg)
{
	// 死亡状态不接受其他状态
	CCLOG("dead state receive state msg:%d",_msg.Msg);

	int mask = M_REBORN;
	if( !(mask & _msg.Msg) )
	{
		return false;
	}

	// 死亡状态不能转移其他状态
	return _ge->changeState(M_DEAD, _msg);
}

void ObjDeadState::Exit( GameEntity* )
{

}

void ObjDeadState::Execute( GameEntity* _ge, float _df )
{
	//int opac = _ge->getOpacity();
	//opac = opac > 15 ? opac-15:0;
	//_ge->setOpacity(opac);
}


//////////////////////////////////////////////////////////////////////////

ObjAttackState * ObjAttackState::getInstance()
{
	static ObjAttackState _has;
	return &_has;
}

void ObjAttackState::Enter( GameEntity* _ge)
{
	if(!_ge)
	{
		CCLOG("game entity nullptr");
		return;
	}

	CCLOG("obj %d enter state: %d",_ge->getID(),M_ATK);

	_ge->setLocalZOrder(_ge->getLocalZOrder() + GameEntity::ATTACK_Z_OFFSET);

	// 施法动作
	const Skill* pSkill = _ge->GetCurSkill();
	if (pSkill)
	{
		auto cfg_skill_info = g_SkillInfoMgr.getObject(pSkill->getID());

		// 在json里，空字符串读出来后是null
		if (cfg_skill_info->src_act_name[0] != 0 && strcmp(cfg_skill_info->src_act_name,"null"))
		{
			_ge->playAnim(cfg_skill_info->src_act_name,-1,0);
		}

		// 目标特效
		if (cfg_skill_info->hit_effect[0] != 0 && strcmp(cfg_skill_info->hit_effect,"null"))
		{

		}
	}
	
}

void ObjAttackState::Execute( GameEntity* _ge, float _df )
{
	if(!_ge)
	{
		CCLOG("[ObjAttackState::Execute] game entity nullptr");
		return;
	}

	if (_ge)
	{
		_ge->attack_tick(_df);
	}

}

void ObjAttackState::Exit( GameEntity* _ge)
{
	if (!_ge)
	{
		return;
	}
	CCLOG("obj %d exit state: %d",_ge->getID(),M_ATK);

	//
	if (_ge->getTarget() != nullptr)
	{
		_ge->setTarget(nullptr);
	}

	_ge->setLocalZOrder(_ge->getLocalZOrder() - GameEntity::ATTACK_Z_OFFSET);

	_ge->stopAnim();
	
}

bool ObjAttackState::OnMessage( GameEntity* _ge, const Telegram& _msg)
{

	CCLOG("[HeroAttackState] obj %d receive msg :%d",_ge->getID(),_msg.Msg);
	// 这里处理排斥问题
	int mask = M_DEAD | M_RUN | M_IDLE | M_ATK;
	
	if ( !(mask & _msg.Msg) )
	{
		CCLOG("NpcAttackState receive state:%d",_msg.Msg);
		return false;
	}

	return _ge->changeState(M_ATK, _msg);
}


//////////////////////////////////////////////////////////////////////////

HeroRunState * HeroRunState::getInstance()
{
	static HeroRunState _ors;
	return &_ors;
}

void HeroRunState::Enter( GameEntity* _ge)
{
	if (!_ge)
	{
		return;
	}

	CCLOG("obj %d enter state: %d",_ge->getID(),M_RUN);

	auto _hero = dynamic_cast<Hero*>(_ge);
	if (_hero)
	{
		_hero->runTo(_ge->getDest());
		_hero->playAnim(AT_WALK);
	}

}

void HeroRunState::Execute( GameEntity* _ge, float _df )
{
	if (!_ge)
	{
		return;
	}

	static float last_y = _ge->getPosition().y;
	float cur_y = _ge->getPosition().y;
	if (abs(cur_y - last_y) >= 5.0f)
	{
		_ge->reOrder();
		last_y = cur_y;
	}
	
}

void HeroRunState::Exit( GameEntity* _ge)
{
	if (!_ge)
	{
		return;
	}

	_ge->stopAnim();

	//
	_ge->fixDir();
}


bool HeroRunState::OnMessage( GameEntity* _ge, const Telegram& _msg)
{

	if (!_ge)
	{
		return false;
	}

	int mask = M_IDLE | M_RUN | M_DEAD;
	CC_ASSERT(mask & _msg.Msg);
	if ( !(mask & _msg.Msg) )
	{
		CCLOG(" NpcRunState receive state:%d",_msg.Msg);
		return false;
	}

	return _ge->changeState(M_RUN, _msg);


	return true;
}


//////////////////////////////////////////////////////////////////////////


ObjBeAttackState * ObjBeAttackState::getInstance()
{
	static ObjBeAttackState _obs;
	return &_obs;
}

void ObjBeAttackState::Enter( GameEntity* _ge)
{

	CCLOG("obj %d enter state: %d",_ge->getID(),M_BEATK);
	if (_ge)
	{
		_ge->playAnim(AT_BEATK,-1,0);
	}
}

void ObjBeAttackState::Execute( GameEntity*, float )
{

}

void ObjBeAttackState::Exit( GameEntity* _ge)
{

}

bool ObjBeAttackState::OnMessage( GameEntity* _ge, const Telegram& _msg)
{
	int mask  = 0;
	if (mask & _msg.Msg)
	{
		return false;
	}

	return false;
}


//////////////////////////////////////////////////////////////////////////


NpcIdleState * NpcIdleState::getInstance()
{
	static NpcIdleState _nis;
	return &_nis;
}

bool NpcIdleState::OnMessage( GameEntity* _ge, const Telegram& _msg)
{
	if (!_ge)
	{
		return false;
	}

	// 状态掩码，该状态下可以接受那些状态
	// M_IDLE 只应该在初始化才有
	int mask = M_ATK | M_RUN | M_IDLE | M_BEATK | M_DEAD | M_BORN;
	if ( !(mask & _msg.Msg) )
	{
		CCLOG("idle state receive %d state msg",_msg.Msg);
		return false;
	}

	return _ge->changeState(M_IDLE,_msg);
}

void NpcIdleState::Enter( GameEntity* _ge)
{
	if(!_ge)
	{
		return;
	}

	CCLOG("obj %d enter state: %d",_ge->getID(),M_IDLE);

	auto _zb = dynamic_cast<Zombie*>(_ge);
	if (_zb)
	{
		// 清理思考时间
		_zb->clearThinkTime();

		// 播放动作
		_zb->playAnim(AT_IDLE);
	}

	

}

void NpcIdleState::Execute( GameEntity* _ge, float _dt)
{
	if (!_ge)
	{
		return;
	}

	_ge->idle_tick(_dt);

}

void NpcIdleState::Exit( GameEntity* _ge)
{
	if (!_ge)
	{
		return;
	}

	CCLOG("obj %d exit state: %d",_ge->getID(),M_IDLE);

	// 其他处理



	// 停止相关动作
	_ge->stopAnim();

}



//////////////////////////////////////////////////////////////////////////

BulletRunState * BulletRunState::getInstance()
{
	static BulletRunState _brs;
	return &_brs;
}

void BulletRunState::Enter( GameEntity* _ge)
{
	if (!_ge)
	{
		return;
	}

	CCLOG("obj %d enter state: %d",_ge->getID(),M_RUN);

	auto _bn = dynamic_cast<Bullet*>(_ge);
	if (_bn)
	{
		_bn->runTo(_bn->getDest());
	}
}

void BulletRunState::Execute( GameEntity* _ge, float _df )
{
	if (!_ge)
	{
		return;           
	}

	auto _bn = dynamic_cast<Bullet*>(_ge);
	if (_bn)
	{
		_bn->run_tick(_df);
	}
}

bool BulletRunState::OnMessage( GameEntity* _ge, const Telegram& _msg)
{
	if (!_ge)
	{
		return false;
	}

	int mask = M_RUN;
	CC_ASSERT(mask & _msg.Msg);
	if ( !(mask & _msg.Msg) )
	{
		CCLOG(" NpcRunState receive state:%d",_msg.Msg);
		return false;
	}

	return _ge->changeState(M_RUN, _msg);
}

void BulletRunState::Exit( GameEntity* _ge)
{
	if(!_ge)
	{
		return;
	}

	CCLOG("obj %d exit state: %d",_ge->getID(),M_RUN);

	_ge->stopAllActions();	
}



//////////////////////////////////////////////////////////////////////////

DefenderArderState* DefenderArderState::getInstance()
{
	static DefenderArderState _das;
	return &_das;
}



void DefenderArderState::Enter( GameEntity* _ge)
{
	if(!_ge)
	{
		return;
	}

	CCLOG("obj %d enter state: %d",_ge->getID(),M_IDLE);
	_ge->playAnim(AT_ARDER);
}



bool DefenderArderState::OnMessage( GameEntity* _ge, const Telegram& _msg)
{
	if (!_ge)
	{
		return false;
	}

	// 状态掩码，该状态下可以接受那些状态
	// M_IDLE 只应该在初始化才有
	int mask = M_ATK | M_IDLE | M_RUN | M_DEAD; 
	if ( !(mask & _msg.Msg) )
	{
		CCLOG("arder state receive %d state msg",_msg.Msg);
		return false;
	}

	return _ge->changeState(M_ARDER,_msg);
}

//////////////////////////////////////////////////////////////////////////
// 召唤物出生状态
//////////////////////////////////////////////////////////////////////////

SummonerBorthState* SummonerBorthState::getInstance()
{
	static SummonerBorthState sbs;
	return &sbs;
}

void SummonerBorthState::Enter( GameEntity* _ge)
{
	if(!_ge)
	{
		return;
	}

	CCLOG("obj %d enter state: %d",_ge->getID(),M_BORN);
	_ge->playAnim(AT_BORN);
}

bool SummonerBorthState::OnMessage( GameEntity* _ge, const Telegram& _msg)
{
	int mask = M_IDLE;

	if (!(mask & _msg.Msg))
	{
		CCLOG("borth state recieved a state %d",_msg.Msg);
		return false;
	}

	return _ge->changeState(M_BORN,_msg);
}
