#include "LocalPlayer.h"
#include "GameDefine.h"
#include "utility/TaoIStream.h"
#include "utility/TaoOStream.h"
//#include "GameData.h"
#include "../component/TimeManager.h"

#include "../component/ObjFactory.h"

using namespace GameDefine;

LocalPlayer* LocalPlayer::g_spRoleData = nullptr;



LocalPlayer::LocalPlayer(void)
{
}


LocalPlayer::~LocalPlayer(void)
{
}

LocalPlayer* LocalPlayer::getInstance()
{
	/*static LocalPlayer s_inst;
	return s_inst;*/

	if (!g_spRoleData)
	{
		g_spRoleData = new LocalPlayer();
	}
	return g_spRoleData;
}



bool LocalPlayer::load( const char* _save_file )
{
	
	if(!_save_file)
	{
		CCLOG("save file null");
		return false;
	}

	std::string path = FileUtils::getInstance()->getWritablePath() + _save_file;
	Data _data = FileUtils::getInstance()->getDataFromFile(path);

	if (_data.isNull())
	{
		CCLOG("file no data");
		return false;
	}
	

	TaoIStream tis(_data.getBytes(),_data.getSize());
	//////////////////////////////////////////////////////////////////////////
	// unserialize begin
	//////////////////////////////////////////////////////////////////////////


	
	// 载入初始数据
	m_global.unserialize(tis);
	m_base_attr.unserialize(tis);
	m_copy_info.unserialize(tis);
	m_bag.unserialize(tis);
	m_guide_info.unserialize(tis);
	m_task_tri.unserialize(tis);

	// 每日任务
	int daily_task_cnt = 0;
	tis >> daily_task_cnt;

	for (int i = 0; i < daily_task_cnt; i++)
	{
		tDailyTaskInfo dti;
		dti.unserialize(tis);
		m_daily_task.push_back(dti);
	}



	// 进一步初始化
	initStageInfo();



	//////////////////////////////////////////////////////////////////////////
	// serialize end
	//////////////////////////////////////////////////////////////////////////

	//
	CC_ASSERT(_data.getSize() == tis.GetSize());

	return true;
}



void LocalPlayer::save( const char* _save_file )
{
	if(!_save_file)
	{
		CCLOG("save file null");
		return;
	}

	std::string path = FileUtils::getInstance()->getWritablePath() + _save_file;


	int buff_size = 1024*256;
	std::vector<char> buff;
	buff.resize(buff_size);

	FILE* fp = fopen(path.c_str(),"wb+");
	if (!fp)
	{
		CCLOG("path %s can't open");
		return;
	}


	TaoOStream tos(&buff[0],buff_size);

	//////////////////////////////////////////////////////////////////////////
	// serialize begin
	//////////////////////////////////////////////////////////////////////////

	m_global.serialize(tos);
	m_base_attr.serialize(tos);
	m_copy_info.serialize(tos);
	m_bag.serialize(tos);
	m_guide_info.serialize(tos);
	m_task_tri.serialize(tos);

	// 每日任务
	int dailytask_cnt = m_daily_task.size();
	tos << dailytask_cnt;
	for (int i = 0; i < dailytask_cnt; i++)
	{
		m_daily_task[i].serialize(tos);
	}


	//////////////////////////////////////////////////////////////////////////
	// serialize end
	//////////////////////////////////////////////////////////////////////////

	int size = tos.GetSize();
	size_t wr_size = fwrite(&buff[0],1,size,fp);
	CC_ASSERT(wr_size == size);
	
	fflush(fp);
	fclose(fp);
}

void LocalPlayer::initDefaultLocalPlayer()
{
	// 基本信息
	m_base_attr.m_data[tBaseAttr::BA_LVL]		= 1;
	m_base_attr.m_data[tBaseAttr::BA_VIP]		= 0;
	m_base_attr.m_data[tBaseAttr::BA_GOLD]		= GD_PLAYER_INIT_GOLD;
	m_base_attr.m_data[tBaseAttr::BA_DIAMOND]	= GD_PLAYER_INIT_DIAMOND;
	m_base_attr.m_data[tBaseAttr::BA_PHYSICAL]	= GD_PLAYER_PHYS_CNT;



#define CREATE_ITEM(_item_id)	\
	do																		\
	{																		\
		auto item = ObjFactory::getInstance().createItem(_item_id);			\
		if (item)															\
		{																	\
			m_bag.addItem(item);											\
		}																	\
	} while (false)
	


	CREATE_ITEM(200001);
	CREATE_ITEM(200002);
	CREATE_ITEM(200004);
	CREATE_ITEM(200005);
	CREATE_ITEM(200006);
	CREATE_ITEM(200007);
	CREATE_ITEM(200008);
	//CREATE_ITEM(200009);


	// 初始化每日任务
	initDailyTask();

}

int LocalPlayer::addValue( GameDefine::tBaseAttr::BA_TYPE _ba_index,int _gold, unsigned int uLimits/* = BaseDefine::MAX_INT_RANGE*/)
{
	unsigned int orign_val = m_base_attr.m_data[_ba_index];

	int nRet = 0;

	// 为负的
	if (_gold < 0)
	{
		orign_val += _gold;
		if(orign_val < 0)
		{
			nRet = _gold - orign_val;
			orign_val = 0;
		}
		else
		{
			nRet = _gold;
		}
		m_base_attr.m_data[_ba_index] = orign_val;
	}
	else
	{
		if (orign_val + _gold > uLimits)
		{
			nRet = uLimits - orign_val;
			orign_val = uLimits;
		}
		else
		{
			nRet = _gold;
		}
		
		m_base_attr.m_data[_ba_index] = orign_val + nRet;
	}

	return nRet;
}

void LocalPlayer::conformReward()
{
	if (m_temp_fight_info.curr_stage_id <= 0)
	{
		CCLOG("invalid stage id: %d",m_temp_fight_info.curr_stage_id);
		return;
	}
	

	// 宝箱奖励
	for (int i = 0; i < GD_REWARD_CNT_MAX; i++)
	{
		if (m_temp_fight_info.rewards[i].id != 0)
		{
			// 
			m_bag.addTempItem(m_temp_fight_info.rewards[i].id,m_temp_fight_info.rewards[i].cnt);
		}
	}

	addValue(tBaseAttr::BA_GOLD, m_temp_fight_info.rewardGold);


	// 存储副本战斗信息
	if(m_stage_infos.count(m_temp_fight_info.curr_stage_id) == 0)
	{
		m_stage_infos[m_temp_fight_info.curr_stage_id] = m_temp_fight_info.star_cnt;
		m_copy_info.setStageStar(m_temp_fight_info.curr_stage_id,m_temp_fight_info.star_cnt);
	}


	save(GameDefine::ROLE_SAVE_FILE);
	// 重置一下
	m_temp_fight_info.resetReward();
}




void LocalPlayer::initStageInfo()
{
	if (m_copy_info.m_data.empty())
	{
		return;
	}

	for (const auto& _iter : m_copy_info.m_data )
	{
		int _stage_id = m_copy_info.getStageId(_iter);
		int _star_cnt = m_copy_info.getStageStar(_iter);


		//int main_stage_id = _stage_id / BaseDefine::HUNDRED_BASE;
		//int sub_stage_id = _stage_id % BaseDefine::HUNDRED_BASE;

		//if (m_last_stage_infos[main_stage_id] < sub_stage_id)
		//{
		//	m_last_stage_infos[main_stage_id] = sub_stage_id;
		//}

		m_stage_infos[_stage_id] = _star_cnt;
	}

}



void LocalPlayer::initDailyTask()
{
	// 初始化每日任务
	int default_init_task_ids[] = {1};
	//
	for (int i = 0; i < sizeof(default_init_task_ids)/sizeof(default_init_task_ids[0]); i++)
	{
		tDailyTaskInfo dti;
		dti.newTask(default_init_task_ids[i]);
		
		m_daily_task.push_back(dti);
	}
}

tDailyTaskInfo* LocalPlayer::getDailyTaskByTid( int _tid )
{
	int dti_cnt = m_daily_task.size();
	for (int i = 0; i < dti_cnt; i++)
	{
		if (m_daily_task[i].tid == _tid)
		{
			return &m_daily_task[i];
		}
	}

	return nullptr;
}



void LocalPlayer::touchTaskTrigger( int _t_mask )
{
	if (m_task_tri.triggerTask(_t_mask))
	{
		save(GameDefine::ROLE_SAVE_FILE);
	}
}



void LocalPlayer::update( float Delta )
{
	static float three_sec = 0;

	// 3秒更新
	do
	{
		three_sec -= Delta;
		if (three_sec > 0)
		{
			break;
		}

		three_sec = LP_UPDATE_INTERVAL;

		// 更新体力值
		if (m_base_attr[tBaseAttr::BA_PHYSICAL_UPDATE] != 0)
		{
			unsigned int _now = TimeManager::getInstance().getTime();

			do 
			{
				if(!TimeManager::getInstance().checkTimeOver(
					m_base_attr[tBaseAttr::BA_PHYSICAL_UPDATE],GameDefine::GD_PHYS_INCR_INTERVAL))
				{
					break;
				}

				if(addValue(tBaseAttr::BA_PHYSICAL,1,GameDefine::GD_PLAYER_PHYS_CNT) == 0)
				{
					m_base_attr[tBaseAttr::BA_PHYSICAL_UPDATE] = 0;
				}
				else
				{					
					m_base_attr[tBaseAttr::BA_PHYSICAL_UPDATE] = MIN(_now,m_base_attr[tBaseAttr::BA_PHYSICAL_UPDATE] + GameDefine::GD_PHYS_INCR_INTERVAL);
				}

			} while (m_base_attr[tBaseAttr::BA_PHYSICAL] < GameDefine::GD_PLAYER_PHYS_CNT);

			// 通知attr更新
			GameDefine::sttCustomEvent ce;
			ce.ce_type = GameDefine::sttCustomEvent::CE_MAIN_UI_ATTR_UPDATE;		
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GameDefine::MAIN_UI_UPDATE_EVENT,&ce);
		}


	} while (false);
}

