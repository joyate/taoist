#include "IBuffBase.h"
#include "cocos2d.h"
#include "../ai/GameEntity.h"
#include "../data/AttrChange.h"
#include "../frame/BattleScene.h"
#include "../frame/MapManager.h"
#include "../obj/Summoner.h"
#include "../obj/Defender.h"
#include "../obj/Zombie.h"
#include "../ai/MessageDispatcher.h"
#include "../component/Effect.h"
#include "../utility/Utility.h"

USING_NS_CC;

IBuffBase::~IBuffBase()
{

}




void IBuffBase::onExit(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd)
{
	// ����Ч
	if(_bd.eff_name[0])
	{
		detachEffect(_owner,_bd);
	}
	
	_buff.reset();
}

void IBuffBase::attachEffect( GameEntity* _owner,const GameDefine::cfg_Buff_Data& _bd )
{
	// ����Ч
	if (_bd.eff_name[0])
	{
		std::vector<std::string> out;
		if(Utility::parseEffect(_bd.eff_name,out))
		{
			auto eff = Effect::create();
			eff->createEffect(out[0].c_str());
			eff->attachGameObj(_owner,out[1]);
			eff->playEffect(out[1].c_str());
		}
	}
}

void IBuffBase::detachEffect( GameEntity* _owner,GameDefine::tBuffData& _buff )
{
	/*if (_buff)
	{

	}*/
}


//////////////////////////////////////////////////////////////////////////
// ����Ӱ��
//////////////////////////////////////////////////////////////////////////

void AttackSpeedAffect::onEnter(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd)
{
	AttrChange::appendAttr(_owner,AttrChange::AT_ATK_SPEED,_bd.bd_vals[SLOW_FACTOR_INDEX]);
}

void AttackSpeedAffect::onExit(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd)
{

	AttrChange::appendAttr(_owner,AttrChange::AT_ATK_SPEED,-_bd.bd_vals[SLOW_FACTOR_INDEX]);

	// ������״̬
	TimeBuffBase::onExit(_owner,_tar,_buff,_bd);
}


//////////////////////////////////////////////////////////////////////////
// �ٶ�Ӱ��buff
//////////////////////////////////////////////////////////////////////////

void SpeedAffect::onEnter(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd)
{
	AttrChange::appendAttr(_owner,AttrChange::AT_SPEED,_bd.bd_vals[SPEED_AFFECT_FACTOR_INDEX]);
}

void SpeedAffect::onExit(GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd)
{
	AttrChange::appendAttr(_owner,AttrChange::AT_SPEED,-_bd.bd_vals[SPEED_AFFECT_FACTOR_INDEX]);
	
	// ������״̬
	TimeBuffBase::onExit(_owner,_tar,_buff,_bd);
}





int TimeBuffBase::onCheck( GameEntity* _owner, GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd )
{

	float delta = Director::getInstance()->getDeltaTime();
	_buff.m_elapse += delta;

	// ��ʱ������
	if (_bd.active_time < GameDefine::MIN_FLOAT_VALUE)
	{
		return GameDefine::ER_OK;
	}

	// ��ʱ��,ʹ����Դﵽ�趨�Ĵ���
	if (_buff.m_elapse > _bd.active_time + 0.1f)
	{
		return GameDefine::ER_EXPIRE;
	}

	// �����ǲ���dot buff,������buff,dot buff �������������ж�
	if( _bd.first_time + (_buff.m_act_num + 1) * _bd.act_interval < _bd.active_time)
	{
		if(_bd.first_time + (_buff.m_act_num+1) * _bd.act_interval <= _buff.m_elapse)
			return GameDefine::ER_OK;
	}

	return GameDefine::ER_CHECKFAIL;
}



int TimeBuffBase::onActive( GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd )
{
	// dot����
	if (_bd.act_interval > GameDefine::MIN_FLOAT_VALUE)
	{
		_buff.m_act_num++;
	}

	return GameDefine::ER_OK;
}

int ReborthAffect::onActive( GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd )
{
	GameEntity* _obj = _owner;


	EventCustom event("reborth");
	event.setUserData(_obj);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);

	return GameDefine::ER_EXIT;
}


void AttrChangeAffect::onEnter( GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd )
{

}



int AttrChangeAffect::onActive( GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd )
{

	TimeBuffBase::onActive(_owner,_tar,_buff,_bd);

	int type = (int)_bd.bd_vals[ACA_TYPE_PARAM_INDEX];
	AttrChange::appendAttr(_owner,(AttrChange::ATTR_TYPE)type,_bd.bd_vals[ACA_VALUE_PARAM_INDEX]);

	return GameDefine::ER_OK;
}



void AttrChangeAffect::onExit( GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd )
{
	TimeBuffBase::onExit(_owner,_tar,_buff,_bd);
}





int DeadthBornAffect::onActive( GameEntity* _owner,GameEntity* _tar,GameDefine::tBuffData& _buff,const GameDefine::cfg_Buff_Data& _bd )
{
	do 
	{
		if (_bd.bd_vals[SUMMONER_ID_INDEX] <= 0)
		{
			CCLOG("DeadthBornAffect has invalid parameter");
			break; 
		}


		auto bs = (BattleScene*)Director::getInstance()->getRunningScene();
		auto& mm = bs->getCurMapMgr();

		GameEntity* src_obj = mm.GetGameObject(_buff.src_id);
		if (!src_obj)
		{
			CCLOG("buff %d has no owner",_buff.m_buff_id);
			break;
		}

		GameEntity* sum_obj = nullptr;
		if (src_obj->getMainType() & GameEntity::OT_DEFENDER)
		{
			// 
			sum_obj = createSummoner((Defender*)src_obj);
		}
		else if(src_obj->getMainType() & GameEntity::OT_OFFENSIVE)
		{
			sum_obj = createSummoner((Zombie*)src_obj);	
		}

		if (!sum_obj)
		{
			CCLOG("not compatable owner type");
			break;
		}

		// ���ﹲ����buff_id,������Ϊ�ٻ�����id
		sum_obj->initCardId(_bd.bd_vals[SUMMONER_ID_INDEX]);
		// �ٻ��ĳ��������ﲻҪ��ռλ
		auto rect_idx = mm.getVec2Rect(_owner->getPosition(),false);
		mm.putObjectInGrid(rect_idx,sum_obj);
		
		// ���ӵ��˼����������ж�ʤ��
		if (sum_obj->getMainType() & GameEntity::OT_OFFENSIVE)
		{
			mm.increEnemyCnt();
		}

		// �ٻ��������
		MessageDispatcher::Instance()->DispatchMsg(-1,(GameEntity*)sum_obj,(GameEntity*)sum_obj,M_BORN,nullptr);

	} while (false);

	return GameDefine::ER_EXIT;
}
