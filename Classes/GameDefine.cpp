#include "GameDefine.h"
//#include "data/GameData.h"
#include "data/GameData.h"


// ------ 存档文件 ------------
const char* GameDefine::ROLE_SAVE_FILE = "role.db";
// ---------------------------


//////////////////////////////////////////////////////////////////////////
// 常用变量
//////////////////////////////////////////////////////////////////////////

const char* GameDefine::BATTLE_HERO_INFO_UPDATE_EVENT = "battle_hero_info_update";
const char* GameDefine::REWARD_UPDATE_EVENT = "_reward_update";
const char* GameDefine::MAIN_UI_UPDATE_EVENT = "main_ui_update";
const float GameDefine::MIN_FLOAT_VALUE = 0.000001f;


void GameDefine::tBaseAttr::serialize( TaoOStream& _stream )
{
	for (int i = 0; i < GameDefine::tBaseAttr::BA_MAX; i++)
	{
		_stream << m_data[i];
	}

}

void GameDefine::tBaseAttr::unserialize( TaoIStream& _stream )
{
	for (int i = 0; i < GameDefine::tBaseAttr::BA_MAX; i++)
	{
		_stream >> m_data[i];
	}
}

void GameDefine::tCopyInfo::serialize( TaoOStream& _stream )
{
	int size = m_data.size();
	_stream << size;
	for (int i = 0; i < size; i++)
	{
		_stream << m_data[i];
	}

	_stream << (int)m_copy_shop_infos.size();
	for (auto& _iter : m_copy_shop_infos)
	{
		_stream << _iter.first;								// copy id
		_stream << _iter.second.last_update_time;			// update time
		_stream << _iter.second.u_bought_mask;				// bought mask
		_stream << (int)_iter.second._item_ids.size();		// shop item count
		for (auto _item_iter : _iter.second._item_ids)
		{
			_stream << _item_iter;
		}
	}

}

void GameDefine::tCopyInfo::unserialize( TaoIStream& _stream )
{
	int size = 0;
	_stream >> size;
	for (int i = 0; i < size; i++)
	{
		unsigned int si;
		_stream >> si;
		m_data.push_back(si);
	}

	_stream >> size;
	for (int i = 0; i < size; i++)
	{
		int copy_id = 0;
		int shop_update_time = 0;
		unsigned int u_bought_mask = 0;
		int item_cnt = 0;

		_stream >> copy_id;
		_stream >> shop_update_time;
		_stream >> u_bought_mask;
		_stream >> item_cnt;

		tCopyShopItemInfo csii;
		csii.last_update_time = shop_update_time;
		csii.u_bought_mask = u_bought_mask;

		for (int i = 0; i < item_cnt; i++)
		{
			int _shop_item_id = 0;
			_stream >> _shop_item_id;
			csii._item_ids.push_back(_shop_item_id);
		}

		m_copy_shop_infos.insert(std::make_pair(copy_id,csii));
	}
}

void GameDefine::tItemInfo::serialize( TaoOStream& _stream )
{
	_stream <<	item_id;
	_stream <<	item_temp_id;
	_stream <<	item_num;
}

void GameDefine::tItemInfo::unserialize( TaoIStream& _stream )
{
	_stream >>	item_id;
	_stream >>	item_temp_id;
	_stream >>	item_num;
}


void GameDefine::tCardInfo::serialize( TaoOStream& _stream )
{
	tItemInfo::serialize(_stream);

	_stream << m_lvl;
	_stream << m_star;
	_stream << m_intense_lvl;
	_stream << m_exp;
	_stream << m_fight;
}

void GameDefine::tCardInfo::unserialize( TaoIStream& _stream )
{
	tItemInfo::unserialize(_stream);

	_stream >> m_lvl;
	_stream >> m_star;
	_stream >> m_intense_lvl;
	_stream >> m_exp;
	_stream >> m_fight;
}


void GameDefine::tEquipInfo::serialize( TaoOStream& _stream )
{
	tItemInfo::serialize(_stream);
	_stream << m_intense_lvl;

}


void GameDefine::tEquipInfo::unserialize( TaoIStream& _stream )
{
	tItemInfo::unserialize(_stream);
	_stream >> m_intense_lvl;

}








void GameDefine::tBagInfo::serialize( TaoOStream& _stream )
{
	_stream << m_grid_num;

	int item_size = m_items.size();
	_stream << item_size;

	for (item_iter _iter = m_items.begin();
		_iter != m_items.end(); _iter++)
	{
		CC_ASSERT(_iter->second);
		_stream << _iter->second->item_temp_id;
		_iter->second->serialize(_stream); 
	}
}

void GameDefine::tBagInfo::unserialize( TaoIStream& _stream )
{
	_stream >> m_grid_num;
	
	int item_size = 0;
	_stream >> item_size;
	
	for (int i = 0; i < item_size; i++)
	{
		int item_temp_id = 0,item_num = 1;

		_stream >> item_temp_id;

		tItemInfo* item = nullptr;
		auto item_info = g_ItemInfoMgr.getObject(item_temp_id);
		if (item_info)
		{
			if (item_info->item_type == IT_CARD)
			{
				item = new tCardInfo();
			}
			else if(item_info->item_type == IT_EQUIP)
			{
				item = new tEquipInfo();
			}
			else
			{
				item = new tItemInfo();
			}

			CC_ASSERT(item);
			item->unserialize(_stream);
			m_items.insert(std::make_pair(item->item_id,item));
		}
	}
}

void GameDefine::tGlobalData::serialize( TaoOStream& _stream )
{
	_stream << version;
	_stream << structSize;
	_stream << lastItemId;
}

void GameDefine::tGlobalData::unserialize( TaoIStream& _stream )
{
	_stream >> version;
	_stream >> structSize;
	_stream >> lastItemId;
}


void GameDefine::tGuideInfo::serialize( TaoOStream& _stream )
{
	_stream << last_guide_id;
}

void GameDefine::tGuideInfo::unserialize( TaoIStream& _stream )
{
	_stream >> last_guide_id;
}




void GameDefine::tDailyTaskInfo::serialize( TaoOStream& _stream )
{
	_stream << tid;
	_stream << ts;
	_stream << cur_num;
	_stream << last_time;
}


void GameDefine::tDailyTaskInfo::unserialize( TaoIStream& _stream )
{
	_stream >> tid;
	_stream >> ts;
	_stream >> cur_num;
	_stream >> last_time;
}

bool GameDefine::tDailyTaskInfo::newTask( int _tid )
{
	auto cfg_daily_task = g_DailyTaskMgr.getObject(_tid);
	if (!cfg_daily_task)
	{
		return false;
	}


	tid = cfg_daily_task->id;
	ts = TS_DOING;
	cur_num = 0;
	last_time = 0;

	return true;
}

void GameDefine::tDailyTaskInfo::reset()
{
	tid = 0;
	ts = TS_INVALID;
	cur_num = 0;
	last_time = 0;
}




