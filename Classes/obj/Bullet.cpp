#include "Bullet.h"
#include "../data/GameData.h"
#include "../ai/AIState.h"
#include "../ai/Telegram.h"
#include "../ai/MessageDispatcher.h"
#include "../frame/MapManager.h"
#include "../frame/BattleScene.h"

#include "../skill/ObjectAction.h"


#include "../skill/SkillInstance.h"
#include "../skill/SkillDamage.h"


Bullet::Bullet( void ):
	m_onwer_id(0),
	m_from_skill_id(0),
	m_body_type(BODY_TYPE_ARMATURE)
{
	m_type = OT_BULLET;

	if (_stateMechine)
	{
		_stateMechine->SetCurrentState(BulletRunState::getInstance());
	}
}

Bullet::~Bullet( void )
{

}


void Bullet::initObj( int _bid,int sk_id )
{
	if (_bid <= 0 || sk_id <= 0)
	{
		CCLOG("bullet init failed since invalid id");
		return;
	}


	auto bullet = g_BulletInfoMgr.getObject(_bid);
	if (!bullet)
	{
		CCLOG("bullet init failed as id %d",_bid);
		return;
	}

	// 有速度
	m_attr.m_hp = 1;
	m_attr.m_speed = bullet->speed;
	m_from_skill_id = sk_id;


	auto body = parseBody(bullet->path);
	if (!body)
	{
		return;
	}
	body->setScale(bullet->scale);
	m_char_root->addChild(body,TAG_GNT_BODY_LAYER_LVL,TAG_GNT_BODY);
}

bool Bullet::changeState( unsigned int mask, const Telegram& telegram )
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
			_stateMechine->ChangeState(BulletRunState::getInstance());
			bRet = true;
		}
		break;
	case M_ATK:
		{

		}
		break;
	default:
		break;
	}


	// 本层不处理，向上传递
	if (!bRet)
	{
		return GameEntity::changeState(mask,telegram);
	}

	return true;
}


void Bullet::run_tick( float dt )
{

	if (!isAlive())
	{
		return;
	}

	auto scene = (BattleScene*)Director::getInstance()->getRunningScene();
	MapManager& map = scene->getCurMapMgr();

	auto obj = map.GetGameObject(m_onwer_id);
	if (!obj)
	{
		CCLOG("bullet found no owner %d",m_onwer_id);
		return;
	}

	int mask = 0;
	if (obj->getType() & GameEntity::OT_DEFENDER)
	{
		mask = GameEntity::OT_OFFENSIVE;
	}
	else
	{
		mask = GameEntity::OT_DEFENDER;
	}


	TargetSelectorFilter tsf;
	tsf.filter_dis = 0;
	tsf.sel_num = 1;
	tsf.bAdjustY = true;
	tsf.select_mask = mask;

	std::vector<GameEntity*> _out;
	int nCount = map.getLineNearestObjs(this,&_out,tsf);
	if (nCount > 0)
	{
		filterBorningStatus(_out);
		if (_out.empty())
		{
			return;
		}
		
		//
		auto skill_info = g_SkillInfoMgr.getObject(m_from_skill_id);
		if (!skill_info)
		{
			CCLOG("skill %d has no data",m_from_skill_id);
			return;
		}

		auto dmg = ObjectInstanceMgr<ISkillDamage>::getInstance()->getHandler(skill_info->damage_type);

		if (!dmg)
		{
			CCLOG("skill %d has no damage type",skill_info->id);
			return;
		}

		dmg->init(*skill_info); // 这只有在单线程下有效
		dmg->handleDamage(obj,_out);

		// 销毁
		deadCallback();
	}
}



void Bullet::runTo( const Vec2& _dest )
{
	const Vec2 &curPos = getPosition();
	float dis = curPos.distance(_dest);

	MoveTo *moveTo = MoveTo::create(dis / m_attr.m_speed, _dest);
	Action *action = Sequence::createWithTwoActions(moveTo, CallFunc::create(CC_CALLBACK_0(Bullet::deadCallback,this)));

	if (!action)
	{
		CCLOG("action create failed");
		return;
	}

	this->stopAllActions();
	this->runAction(action);
}


void Bullet::deadCallback()
{
	m_attr.m_hp = 0;

	auto ce = CorpseEffect::create();
	ce->setDelay(0.2f);
	ce->retain();
	ce->go(this);
}



//Rect Bullet::getBoundingBox() const
//{
//	auto ani = m_char_root->getChildByTag(TAG_GNT_BODY);
//	if (ani)
//	{
//		Rect rect = ani->getBoundingBox();
//		rect = RectApplyAffineTransform(rect,getNodeToParentAffineTransform());
//		return rect;
//	}
//
//	return Rect::ZERO;
//}




Node* Bullet::parseBody( const std::string& _cfgNames )
{

	Node* ret = nullptr;
	if (_cfgNames.empty() || _cfgNames == "null")
	{
		CCLOG("Bullet::parseBody failed");
		return ret;
	}

	//
	int size = _cfgNames.size();
	if (!_cfgNames.compare(size - 3,3,"png"))
	{
		ret = Sprite::create(_cfgNames.c_str());
	}
	else
	{
		ret = Armature::create(_cfgNames.c_str());
		static_cast<Armature*>(ret)->getAnimation()->playWithIndex(0);
	}

	return ret;
}



void Bullet::filterBorningStatus( std::vector<GameEntity*>& _out )
{
	for (auto& _iter : _out)
	{
		if(_iter->isBorning())
			_iter = nullptr;
	}
}

