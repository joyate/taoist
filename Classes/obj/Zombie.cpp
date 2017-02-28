#include "Zombie.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"
#include "../ai/AIState.h"
#include "../ai/Telegram.h"
#include "../ai/MessageDispatcher.h"


#ifdef _DEBUG
#include "../frame/BattleScene.h"
#endif


using namespace GameDefine;
using namespace cocostudio;


Zombie::Zombie(void)
{
	m_type = OT_MONSTER | OT_OFFENSIVE;
	m_e_dir = DIR_L;
	m_think_intval = 0;

	if (_stateMechine)
	{
		_stateMechine->SetCurrentState(NpcIdleState::getInstance());
	}
}


Zombie::~Zombie(void)
{
}


bool Zombie::initCardId( int _cid )
{

	if (!GameEntity::initCardId(_cid))
	{
		return false;
	}

	// 老僵尸，大僵尸方向调整
	if (_cid != 200010 && _cid != 200003)
	{
		auto _body = m_char_root->getChildByTag(TAG_GNT_BODY);
		if (_body)
		{
			_body->setScaleX(_body->getScaleX() * -1);
		}
	}


	return true;
}



void Zombie::runTo( const Vec2& _dest )
{
	GameEntity::runTo(_dest);

	const Vec2 &curPos = getPosition();
	float dis = curPos.distance(_dest);

	MoveTo *moveTo = MoveTo::create(dis / m_attr.m_speed, _dest);
	Action *action = Sequence::createWithTwoActions(moveTo, CallFunc::create(CC_CALLBACK_0(Zombie::idleCallback,this)));

	if (!action)
	{
		CCLOG("action create failed");
		return;
	}

	this->stopAllActions();
	this->runAction(action);
}


#ifdef _DEBUG

void Zombie::draw( Renderer *renderer, const Mat4 &transform, uint32_t flags )
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(Zombie::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

void Zombie::onDraw( const Mat4 &transform, uint32_t flags )
{
	getGLProgram()->use();
	getGLProgram()->setUniformsForBuiltins(transform);


	Armature* armature = (Armature*)m_char_root->getChildByTag(TAG_GNT_BODY);
	Rect rect = RectApplyTransform(armature->getBoundingBox(),getNodeToParentTransform());
	BattleScene* bs = (BattleScene*)Director::getInstance()->getRunningScene();
	rect.origin += bs->getMapBeginPos();

	DrawPrimitives::setDrawColor4B(100, 100, 100, 255);
	DrawPrimitives::drawRect(rect.origin, Vec2(rect.getMaxX(), rect.getMaxY()));
}

#endif


void Zombie::onEnter()
{
	GameEntity::onEnter();

	//
	setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
}



void Zombie::update( float delta )
{
	GameEntity::update(delta);

	// 特殊更新
	

}

void Zombie::fixDir()
{
	if (m_e_dir != DIR_L)
	{
		auto _body = m_char_root->getChildByTag(TAG_GNT_BODY);
		if (!_body)
		{
			return;
		}

		_body->setScaleX(_body->getScaleX() * -1);
		m_e_dir = DIR_L;
	}
}



void Zombie::run_tick( float df )
{
	m_skillMgr.tick(df);

}

void Zombie::idle_tick( float dt )
{
	m_skillMgr.tick(dt);

	
	m_think_intval += dt;

	// 怪物思考的间隔，需要注意要大于攻击等待间隔
	if (m_think_intval > GameDefine::GD_NPC_THINK_INTERVAL)
	{

		GameDefine::state_attr sa;
		sa.mask = GameDefine::state_attr::SA_DEST_MASK;
		sa.dest = Vec2(0,this->getPosition().y);

		MessageDispatcher::Instance()->DispatchMsg(-1,this,this,M_RUN,(void*)&sa);
	}

}

bool Zombie::changeState( unsigned int mask, const Telegram& telegram )
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
			_stateMechine->ChangeState(NpcRunState::getInstance());

			bRet = true;
		}
		break;
	case M_REBORN:
	case M_IDLE:
		{
			_stateMechine->ChangeState(NpcIdleState::getInstance());
			bRet = true;
		}
		break;
	case M_ATK:
		{
			_stateMechine->ChangeState(NpcAttackState::getInstance());
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

GameDefine::Dir Zombie::flipDir( GameDefine::Dir _new_dir )
{
	CC_ASSERT(_new_dir >= GameDefine::DIR_L && _new_dir < GameDefine::DIR_MAX);
	switch(_new_dir)
	{
	case GameDefine::DIR_R:
		return (GameDefine::Dir)(_new_dir - m_e_dir - 1);
	default:
		return _new_dir;
	}
	return _new_dir;
}


