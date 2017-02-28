#include "ObjectAction.h"
#include "../ai/GameEntity.h"
#include "../frame/BattleScene.h"
#include "../frame/LootMgr.h"

BloodFly::BloodFly(void)
{
}


BloodFly::~BloodFly(void)
{
}



void BloodFly::initialize(int _hp, int _type /*= RED_HP_SUB*/)
{
	__String* str_hp = __String::createWithFormat("%d",_hp);
	
	switch (_type)
	{
	case RED_HP_SUB:
		{
			m_blood_label = Label::createWithBMFont("mhp_num.fnt", str_hp->getCString());
		}
		break;
	case GRN_HP_ADD:
		{
			m_blood_label = Label::createWithBMFont("mhp_num_g.fnt", str_hp->getCString());
		}
		break;
	default:
		break;
	}
}




void BloodFly::fly(GameEntity* _owner,bool bCritical /*= false*/)
{
	if (!m_blood_label)
	{
		CCLOG("blood label nullptr");
		return;
	}

	m_blood_label->setPosition(0,_owner->getContentSize().height/2);
	_owner->addChild(m_blood_label);


	ActionInterval* action = nullptr;

	if (bCritical)
	{
		auto scale_act = ScaleBy::create(0.4f,1.3f);
		action = Sequence::create(
			EaseQuarticActionIn::create(scale_act),
			EaseQuarticActionOut::create(scale_act->reverse()),
			CallFuncN::create( CC_CALLBACK_1(GameEntity::bloodFlyCallback, _owner)),
			nullptr);
	}
	else
	{
		action = Sequence::create(
			DelayTime::create(0.8f),
			CallFuncN::create( CC_CALLBACK_1(GameEntity::bloodFlyCallback, _owner)),
			nullptr);
	}
	

	auto act_spawn = Spawn::create(
		FadeOut::create(0.8f),
		MoveBy::create(0.8f,Vec2(0,50.0f)),
		action,
		nullptr);

	//auto actions = Sequence::create(act_spawn,CallFuncN::create( CC_CALLBACK_1(GameEntity::bloodFlyCallback, _owner)));

	m_blood_label->runAction(act_spawn);
}

//////////////////////////////////////////////////////////////////////////

CorpseEffect::CorpseEffect():
	m_owner(nullptr),
	m_delay(0.1f)
{

}

void CorpseEffect::go( GameEntity* _owner )
{
	if (!_owner)
	{
		CCLOG("[CorpseEffect::go] _owner nullptr");
		return;
	}

	m_owner = _owner;
	m_owner->playDeadFade(m_delay);
	_owner->runAction(Sequence::create(DelayTime::create(m_delay),CallFuncN::create( CC_CALLBACK_1(CorpseEffect::deadCallback, this)),nullptr));
}


void CorpseEffect::deadCallback( Node* sender )
{

	if (!m_owner)
	{
		CCLOG("[CorpseEffect::deadCallback] owner nullptr");
		return;
	}


	// µôÂä½±Àø
	auto obj_attr = g_ObjInfoMgr.getObject(m_owner->getObjId());
	if (obj_attr && obj_attr->drop_id > 0)
	{
		int nRewardCnt = LootMgr::getInstance().dropReward(obj_attr->drop_id);

		if (nRewardCnt > 0)
		{
			sttCustomEvent ce;
			ce.ce_type = sttCustomEvent::CE_BATTLE_REWARD_UPDATE;
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GameDefine::REWARD_UPDATE_EVENT,(void*)&ce);
		}
	}

	// ÏûÊÅbuff
	m_owner->onBuffEvent(BuffMgr::BEM_EVENT_FADE);
	
	//
	auto scene = (BattleScene*)Director::getInstance()->getRunningScene();
	scene->getCurMapMgr().exitMap(m_owner);


	this->release();
}


