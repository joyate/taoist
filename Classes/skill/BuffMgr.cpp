#include "BuffMgr.h"
#include "../ai/GameEntity.h"
#include "../data/GameData.h"
#include "SkillInstance.h"
#include "../utility/Utility.h"




BuffMgr::BuffMgr(GameEntity* _owner):
	m_owner(_owner)
{
	m_buffs.resize(GameDefine::GD_BUFF_NUM_MAX);
}


BuffMgr::~BuffMgr(void)
{
}



//
void BuffMgr::onEvent(unsigned int _em,GameEntity* _tar/* = nullptr*/)
{

	for (int i = 0, size = m_buffs.size(); i < size; i++)
	{
		if (m_buffs[i].isValid())
		{
			auto p_cfg_buff = g_BuffInfoMgr.getObject(m_buffs[i].m_buff_id);
			if (!p_cfg_buff)
			{
				CCLOG("buff id %d has no buff data");
				continue;
			}

			if(Utility::hasEvent(p_cfg_buff->event_mask,_em))
			{
				auto _inst = tBufferMgr::getInstance()->getHandler(p_cfg_buff->buff_type);
				if (!_inst)
				{
					CCLOG("buff type %d has no instance",p_cfg_buff->buff_type);
					continue;
				}

				int nRet = ER_OK;
				if( (nRet = _inst->onCheck(m_owner,_tar,m_buffs[i],*p_cfg_buff)) == GameDefine::ER_OK)
				{
					nRet = _inst->onActive(m_owner,_tar,m_buffs[i],*p_cfg_buff);		
				}

				if (nRet == GameDefine::ER_EXIT || nRet == GameDefine::ER_EXPIRE)
				{
					_inst->onExit(m_owner,_tar,m_buffs[i],*p_cfg_buff);
				}
				else if(nRet == GameDefine::ER_CHECKFAIL)
				{
					CCLOG("buff id %d onCheck failed",p_cfg_buff->id);
				}

			}
		}
	}
}




void BuffMgr::update( float _dt )
{
	onEvent(BEM_EVENT_TIME);
}

bool BuffMgr::handleGotBuff(int _b_id,GameEntity* _tar)
{
	if (_b_id == 0)
	{
		return false;
	}

	auto p_cfg_buff = g_BuffInfoMgr.getObject(_b_id);
	if (!p_cfg_buff)
	{
		CCLOG("buff id %d has no buff data");
		return false;
	}

	//
	int index = tryGotBuff(_b_id);
	if (index < 0)
	{
		return false;
	}

	auto _inst = tBufferMgr::getInstance()->getHandler(p_cfg_buff->buff_type);
	if (!_inst)
	{
		CCLOG("buff type %d has no instance",p_cfg_buff->buff_type);
		return false;
	}

	m_buffs[index].m_buff_id = _b_id;
	m_buffs[index].src_id = _tar->getID();
	// 获得buff,第一次产生作用
	_inst->onEnter(m_owner,_tar,m_buffs[index],*p_cfg_buff);

	return true;
}

int BuffMgr::tryGotBuff( int _b_id )
{
	int sel_index = -1;

	int buff_size = m_buffs.size();
	for (int cur_index = 0; cur_index < buff_size; cur_index++)
	{
		if (m_buffs[cur_index].m_buff_id == 0)
		{
			if(sel_index == -1)
			{
				sel_index = cur_index;
				continue;
			}
		}
		
		if(m_buffs[cur_index].m_buff_id == _b_id)
		{
			sel_index = cur_index;
		}
	}

	return sel_index;
}
