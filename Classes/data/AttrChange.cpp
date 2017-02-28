#include "AttrChange.h"
#include "../ai/GameEntity.h"
#include "../ai/AIState.h"
#include "../ai/MessageDispatcher.h"
#include "../skill/ObjectAction.h"


void AttrChange::changeAttr( GameEntity* _ge,ATTR_TYPE _at,float _val )
{
	if (!_ge)
	{
		CCLOG("GameEntitiy nullptr");
		return;
	}


	switch (_at)
	{
	case AT_ATK_SPEED:
		{
			_ge->m_atk_speed = _val;

			auto anim = (Armature*)_ge->m_char_root->getChildByTag(GameEntity::TAG_GNT_BODY);
			if (anim)
			{
				if(anim->getAnimation()->getCurrentMovementID() == "atk")
				{
					anim->getAnimation()->setSpeedScale(_ge->m_atk_speed);
				}
			}
		}
		break;
	default:
		CC_ASSERT(false && "no implementation");
		break;
	}
}

void AttrChange::appendAttr( GameEntity* _ge,ATTR_TYPE _at,float _val )
{
	if (!_ge)
	{
		CCLOG("GameEntitiy nullptr");
		return;
	}


	switch (_at)
	{
	case AT_ATK_SPEED:
		{
			// 这里比较特殊
			_ge->m_atk_speed += _val;
			if (_ge->m_atk_speed < 0)
			{
				_ge->m_atk_speed = 0.1f;
			}

			auto anim = (Armature*)_ge->m_char_root->getChildByTag(GameEntity::TAG_GNT_BODY);
			if (anim)
			{
				if(anim->getAnimation()->getCurrentMovementID() == "atk")
				{
					anim->getAnimation()->setSpeedScale(_ge->m_atk_speed);
				}
			}
		}
		break;
	case AT_SPEED:
		{
			// 速度控制
			_ge->m_attr.m_speed += _val;
			if (_ge->m_attr.m_speed < 0)
			{
				_ge->m_attr.m_speed = 0;
			}

			// 当前状态就是行走
			if(_ge->_stateMechine->isInState(*HeroRunState::getInstance()) || 
				_ge->_stateMechine->isInState(*NpcRunState::getInstance()) )
			{
				GameDefine::state_attr sa;
				sa.mask = GameDefine::state_attr::SA_DEST_MASK;
				sa.dest = _ge->getDest();

				MessageDispatcher::Instance()->DispatchMsg(-1,_ge,_ge,M_RUN,(void*)&sa);
			}

		}
		break;
	case AT_HP:
		{
			_ge->increateHp(_val);

			int bf_type = _val > 0 ? BloodFly::GRN_HP_ADD : BloodFly::RED_HP_SUB;
			_val = _val > 0 ? _val : -_val;
			auto bf = BloodFly::create();
			bf->initialize(_val,bf_type);
			bf->fly(_ge);
		}
		break;
	default:
		break;
	}
}

void AttrChange::appendAttrPercent( GameEntity* _ge,ATTR_TYPE _at,float _val )
{

}
