#include "Effect.h"
#include "../data/GameData.h"
#include "../ai/GameEntity.h"





Effect::Effect(void):
	m_ani(nullptr)
{
}


Effect::~Effect(void)
{
}



bool Effect::attachGameObj( GameEntity* _tar, int nLayer )
{
	bool bRet = false;

	if (!_tar)
	{
		return bRet;
	}


	if (nLayer & EFF_LAYER_BACK || nLayer & EFF_LAYER_FRONT)
	{
		// GameEntity同级层
		auto layer = _tar->getParent()->getChildByTag(nLayer);
		if (layer)
		{
			this->setPosition(_tar->getPosition());
			layer->addChild(this);
			bRet = true;
		}
	}
	else
	{


		if (nLayer & EFF_GE_FRONT)
		{
			_tar->attachCharAnim(this,GameEntity::TAG_GNT_BEATK_EFFECT_LVL,GameEntity::TAG_GNT_BEATK_EFFECT);
			bRet = true;
		}
		else if (nLayer & EFF_GE_BACK)
		{
			_tar->attachCharAnim(this,GameEntity::TAG_GNT_GROUND_EFFECT_LVL,GameEntity::TAG_GNT_GROUND_EFFECT);
			bRet = true;
		}

		if (nLayer & EFF_GP_MID)
		{
			this->setPosition(Vec2(0,_tar->getBoundingBox().size.height/2));
		}
	}


	// 放缩控制
	auto item_info = (GameDefine::cfg_Card*)g_ItemInfoMgr.getObject(_tar->getCardId());
	if (!item_info)
	{
		CCLOG("item id %d no data",_tar->getCardId());
		return false;
	}


	auto pAttr = g_ObjInfoMgr.getObject(item_info->obj_id);
	if (!pAttr)
	{
		CCLOG("obj init failed since obj id invalid");
		return false;
	}

	if (m_ani)
	{
		float factor = pAttr->scale;
		// 这2个是原比例版
		if ( nLayer & (EFF_GE_BACK|EFF_GE_FRONT) )
		{
			if(item_info->id == 200012 || item_info->id == 200013 || item_info->id == 200011 || item_info->id == 200014 )
				factor *= 0.5f;
		}
		m_ani->setScale(factor);
	}

	return bRet;
}

bool Effect::attachGameObj( GameEntity* _tar,const std::string& frame_event )
{
	int tagLayer = 0;

	
	if (frame_event[PARAM_POS_BEGIN] == 'l') // 挂层
	{
		if (frame_event[PARAM_POS_BEGIN+1] == 'f')
		{
			tagLayer = EFF_LAYER_FRONT;
		}
		else if(frame_event[PARAM_POS_BEGIN+1] == 'g')
		{
			tagLayer = EFF_LAYER_BACK;
		}
	}
	else if(frame_event[PARAM_POS_BEGIN] == 'e') // 挂对象
	{
		for (int i = 1; i < PARAM_POS_LENGTH; i++)
		{
			switch (frame_event[PARAM_POS_BEGIN+i])
			{
			case 'f':
				tagLayer |= EFF_GE_FRONT;
				break;
			case 'g':
				tagLayer |= EFF_GE_BACK;
				break;
			case 'm':
				tagLayer |= EFF_GP_MID;
				break;
			case 'b':
				tagLayer |= EFF_GP_BTM;
				break;
			default:
				CC_ASSERT(false && "invalid frame event parameter");
				break;
			}
		}
	}

	if (tagLayer == 0)
	{
		CCLOG("invalid frame event: %s",frame_event.c_str());
		return false;
	}

	return attachGameObj(_tar,tagLayer);
}


void Effect::playEffect( const char* szName /*= nullptr*/,int loop /*= -1*/ )
{
	if (!m_ani)
	{
		return;
	}


	// 如果szName有效，并且不等于"null"
	if (szName && strcmp(szName,"null"))
	{
		static_cast<Armature*>(m_ani)->getAnimation()->play(szName,-1,loop);
	}
	else
	{
		static_cast<Armature*>(m_ani)->getAnimation()->playWithIndex(0,-1,loop);
	}

	// 设置回调
	static_cast<Armature*>(m_ani)->getAnimation()->setMovementEventCallFunc(
		CC_CALLBACK_0(Effect::animationEvent, 
		this, 
		std::placeholders::_1, 
		std::placeholders::_2, 
		std::placeholders::_3));
}

bool Effect::createEffect( GameEntity* _owner )
{
	if (!_owner)
	{
		return false;
	}


	auto item_info = (GameDefine::cfg_Card*)g_ItemInfoMgr.getObject(_owner->getCardId());
	if (!item_info)
	{
		CCLOG("item id %d no data",_owner->getCardId());
		return false;
	}


	auto pAttr = g_ObjInfoMgr.getObject(item_info->obj_id);
	if (!pAttr)
	{
		CCLOG("obj init failed since obj id invalid");
		return false;
	}

	m_ani = Armature::create(StringUtils::format("%s_effect",pAttr->path));
	//m_ani = Armature::create("wangdacui_effect");

	if(m_ani)
	{
		// 进攻方，特效反向
		if (_owner->getCardId() != 200010 && (_owner->getMainType() & GameEntity::OT_OFFENSIVE))
		{
			this->setScaleX(-1.f);
		}

		this->addChild(m_ani);
	}

	return m_ani != nullptr;
}



bool Effect::createEffect( const char* szName )
{
	if (!szName || !szName[0])
	{
		return false;
	}


	m_ani = Armature::create(szName);
	if (m_ani)
	{
		this->addChild(m_ani);
	}

	return m_ani != nullptr;
}



void Effect::animationEvent( Armature *armature, MovementEventType movementType, const std::string& movementID )
{
	if (/*movementType == LOOP_COMPLETE || */movementType == COMPLETE)
	{
		this->removeFromParent();
	}
}
