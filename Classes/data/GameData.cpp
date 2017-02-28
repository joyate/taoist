#include "GameData.h"
#include "cocos2d.h"
#include <assert.h>
#include "json/document.h"
#include "../component/TaoResManager.h"

USING_NS_CC;


//
template<>
bool GameData<cfg_Obj_Attr>::load(const char* file_name)
{
	if (!file_name)
	{
		assert(false && "hero attr load failed: file_name null");
		return false;
	}

	rapidjson::Document doc;
	auto content = FileUtils::getInstance()->getDataFromFile(file_name);
	if (content.isNull())
	{
		CCLOG("file %s empty",file_name);
		return false;
	}


	std::string js((const char*)content.getBytes(), content.getSize());

	doc.Parse<0>(js.c_str());
	if(doc.HasParseError())
	{
		return false;
	}


	do 
	{
		for (size_t i=0; i<doc.Size(); ++i)
		{
			rapidjson::Value &val = doc[i];

			auto pItem = new GameDefine::cfg_Obj_Attr();
			pItem->id = val["id"].GetInt();
			strcpy(pItem->name,val["name"].GetString());
			strcpy(pItem->path,val["path"].GetString());
			pItem->hp = val["hp"].GetInt();
			pItem->ghost = val["ghost"].GetInt();
			pItem->ghost_speed = (float)val["ghost_speed"].GetDouble();
			pItem->ghost_drop = val["ghost_drop"].GetInt();
			pItem->buy_cd = val["buy_cd"].GetInt();
			pItem->hero_ctrl = val["hero_ctrl"].GetInt();
			pItem->strength = (float)val["strength"].GetDouble();
			pItem->agility = (float)val["agility"].GetDouble();
			pItem->wise = (float)val["wise"].GetDouble();
			pItem->phy_atk = val["phy_base_atk"].GetInt();
			pItem->mag_atk = val["mag_base_atk"].GetInt();
			pItem->atk_cri = val["atk_cri"].GetInt();		
			pItem->speed = (float)val["speed"].GetDouble();
			pItem->scale = (float)val["scale"].GetDouble();
			pItem->phy_def = val["phy_base_def"].GetInt();
			pItem->mag_def = val["mag_base_def"].GetInt();

			// 技能数据
			for (int j = 0; j < GameDefine::GD_SKILL_NUM_MAX; j++)
			{
				auto fmt = __String::createWithFormat("sk_id%d",j+1);
				pItem->skill_ids[j] = val[fmt->getCString()].GetInt();
			}

			pItem->drop_id = val["drop_id"].GetInt();

			//CCLOG("-------obj id: %d, name:%s, hp:%d, speed:%f, scale:%f",pItem->id,pItem->name,pItem->hp,pItem->speed,pItem->scale);

			addObject(pItem);	
		}

	} while (false);

	return true;
}


//
template<>
bool GameData<cfg_Skill_Info>::load(const char* file_name)
{
	if (!file_name)
	{
		assert(false && "skill info load failed: file_name null");
		return false;
	}

	rapidjson::Document doc;
	auto content = FileUtils::getInstance()->getDataFromFile(file_name);
	if (content.isNull())
	{
		CCLOG("file %s empty",file_name);
		return false;
	}


	std::string js((const char*)content.getBytes(), content.getSize());

	doc.Parse<0>(js.c_str());
	if(doc.HasParseError())
	{
		return false;
	}


	do 
	{
		for (size_t i=0; i<doc.Size(); ++i)
		{
			rapidjson::Value &val = doc[i];

			auto pItem = new GameDefine::cfg_Skill_Info();

			pItem->id = val["id"].GetInt();
			pItem->sk_type = (SKILL_TYPE)val["sk_type"].GetInt();
			pItem->sk_dmg_type = (SKILL_DMG_TYPE)val["sk_dmg_type"].GetInt();
			pItem->sk_exec_type = val["sk_exec_type"].GetInt();
			strcpy(pItem->sk_name,val["sk_name"].GetString());
			strcpy(pItem->szSkillDesc,val["sk_desc"].GetString());
			strcpy(pItem->szSkillIcon,val["sk_icon"].GetString());
			pItem->affect_mask = val["affect_mask"].GetInt();
			pItem->emit_id = val["emit_id"].GetInt();
			pItem->req_lvl = val["req_lvl"].GetInt();
			pItem->req_ling = val["req_ling"].GetInt();
			pItem->ling_speed = (float)val["ling_speed"].GetDouble();
			pItem->atk_interval = (float)val["atk_int"].GetDouble();
			pItem->tar_sel_type = val["tar_sel_type"].GetInt();
			pItem->tar_num	= val["tar_num"].GetInt();
			for (int j = 0; j < GameDefine::GD_SKILL_SELECT_VAR_MAX; j++)
			{
				auto fmt = __String::createWithFormat("ts_val%d",j+1);
				pItem->ts_vals[j] = (float)val[fmt->getCString()].GetDouble();
			}
			
			strcpy(pItem->hit_effect,val["hit_effect"].GetString());
			strcpy(pItem->src_act_name,val["src_act_name"].GetString());

			pItem->damage_type = val["damage_type"].GetInt();
			for (int j = 0; j < GameDefine::GD_SKILL_VAR_MAX; j++)
			{
				auto fmt = __String::createWithFormat("sk_val%d",j+1);
				pItem->sk_vals[j] = (float)val[fmt->getCString()].GetDouble();
			}
			pItem->buff_id = val["buff_id"].GetInt();

			addObject(pItem);
		}

	}while (false);

	return true;	
}




template<>
bool GameData<cfg_Buff_Data>::load(const char* file_name)
{
	if (!file_name)
	{
		assert(false && "skill info load failed: file_name null");
		return false;
	}

	rapidjson::Document doc;
	auto content = FileUtils::getInstance()->getDataFromFile(file_name);
	if (content.isNull())
	{
		CCLOG("file %s empty",file_name);
		return false;
	}


	std::string js((const char*)content.getBytes(), content.getSize());

	doc.Parse<0>(js.c_str());
	if(doc.HasParseError())
	{
		return false;
	}


	do 
	{
		for (size_t i=0; i<doc.Size(); ++i)
		{
			rapidjson::Value &val = doc[i];

			auto pItem = new GameDefine::cfg_Buff_Data();

			pItem->id			= val["id"].GetInt();
			pItem->buff_type	= val["buff_type"].GetInt();
			pItem->event_mask	= val["event_mask"].GetUint();
			pItem->active_time	= (float)val["active_time"].GetDouble();
			pItem->first_time	= (float)val["first_time"].GetDouble();
			pItem->act_interval = (float)val["act_interval"].GetDouble();
			

			for (int j = 0; j < GameDefine::GD_BUFF_VAL_MAX; j++)
			{
				auto fmt = __String::createWithFormat("bd_val%d",j+1);
				pItem->bd_vals[j] = (float)val[fmt->getCString()].GetDouble();
			}

			addObject(pItem);
		}

	}while (false);

	return true;
}




template<>
bool GameData<cfg_Bullet_Info>::load(const char* file_name)
{
	if (!file_name)
	{
		assert(false && "skill info load failed: file_name null");
		return false;
	}

	rapidjson::Document doc;
	auto content = FileUtils::getInstance()->getDataFromFile(file_name);
	if (content.isNull())
	{
		CCLOG("file %s empty",file_name);
		return false;
	}


	std::string js((const char*)content.getBytes(), content.getSize());

	doc.Parse<0>(js.c_str());
	if(doc.HasParseError())
	{
		return false;
	}


	do 
	{
		for (size_t i=0; i<doc.Size(); ++i)
		{
			rapidjson::Value &val = doc[i];

			auto pItem = new GameDefine::cfg_Bullet_Info();

			pItem->id			= val["id"].GetInt();
			pItem->scale		= (float)val["scale"].GetDouble();
			pItem->speed		= (float)val["speed"].GetDouble();
			pItem->distance		= (float)val["distance"].GetDouble();

			strcpy(pItem->path,val["path"].GetString());
			strcpy(pItem->tar_hit_effect,val["tar_hit_effect"].GetString());


			addObject(pItem);
		}

	}while(false);


	return true;
}




template<>
bool GameData<cfg_Item>::load(const char* file_name)
{
	if (!file_name)
	{
		assert(false && "skill info load failed: file_name null");
		return false;
	}

	rapidjson::Document doc;
	auto content = FileUtils::getInstance()->getDataFromFile(file_name);
	if (content.isNull())
	{
		CCLOG("file %s empty",file_name);
		return false;
	}


	std::string js((const char*)content.getBytes(), content.getSize());

	doc.Parse<0>(js.c_str());
	if(doc.HasParseError())
	{
		return false;
	}


	do 
	{
		for (size_t i=0; i<doc.Size(); ++i)
		{
			rapidjson::Value &val = doc[i];

			auto pItem = new GameDefine::cfg_Item();

			pItem->id			= val["id"].GetInt();
			pItem->item_type	= (ITEM_TYPE)val["item_type"].GetInt();
			pItem->item_lvl		= (ITEM_LVL)val["item_lvl"].GetInt();

			strcpy(pItem->szName,val["item_name"].GetString());
			strcpy(pItem->szItemPic,val["item_pic"].GetString());

			pItem->ct_type		= (COST_TYPE)val["cost_type"].GetInt();
			pItem->cost			= val["cost_val"].GetInt();

			addObject(pItem);
		}

	}while(false);

	return true;
}






template<>
bool GameData<cfg_Card>::load(const char* file_name)
{
	if (!file_name)
	{
		assert(false && "skill info load failed: file_name null");
		return false;
	}

	rapidjson::Document doc;
	auto content = FileUtils::getInstance()->getDataFromFile(file_name);
	if (content.isNull())
	{
		CCLOG("file %s empty",file_name);
		return false;
	}


	std::string js((const char*)content.getBytes(), content.getSize());

	doc.Parse<0>(js.c_str());
	if(doc.HasParseError())
	{
		return false;
	}



	do 
	{
		for (size_t i=0; i<doc.Size(); ++i)
		{
			rapidjson::Value &val = doc[i];

			auto pItem = new GameDefine::cfg_Card();

			pItem->id			= val["id"].GetInt();

			// hook 一下
			auto item = g_ItemInfoMgr.getObject(pItem->id);
			if (!item)
			{
				CCLOG("card %d has base item info",pItem->id);
				CC_SAFE_DELETE(pItem);
				continue;
			}

			memcpy(pItem,item,sizeof(cfg_Item));
			//g_ItemInfoMgr.removeObj(pItem->id);
			
			pItem->arm_type					= (ARMY_TYPE)val["army_type"].GetInt();
			pItem->desc_id					= val["desc_id"].GetInt();
			strcpy(pItem->card_pic, val["card_pic"].GetString());
			pItem->cat						= (CARD_ATTR_TYPE)val["fe_type"].GetInt();
			pItem->exchange_ghost			= (float)val["req_ghost"].GetDouble();
			pItem->exchange_prestige		= (float)val["req_prestige"].GetDouble();
			pItem->req_ctrl					= val["req_ctrl"].GetInt();
			pItem->obj_id					= val["obj_id"].GetInt();

			if(!g_ItemInfoMgr.replaceObj(pItem->id,pItem))
			{
				CCLOG("item %d replace failed",pItem->id);
			}
		}

	}while(false);


	return true;
}



template<>
bool GameData<cfg_Copy>::load(const char* file_name)
{
	if (!file_name)
	{
		assert(false && "skill info load failed: file_name null");
		return false;
	}

	rapidjson::Document doc;
	auto content = FileUtils::getInstance()->getDataFromFile(file_name);
	if (content.isNull())
	{
		CCLOG("file %s empty",file_name);
		return false;
	}


	std::string js((const char*)content.getBytes(), content.getSize());

	doc.Parse<0>(js.c_str());
	if(doc.HasParseError())
	{
		return false;
	}

	do 
	{
		for (size_t i=0; i<doc.Size(); ++i)
		{
			rapidjson::Value &val = doc[i];

			auto pItem = new GameDefine::cfg_Copy();

			pItem->id			= val["id"].GetInt();
			pItem->req_lvl		= val["req_lvl"].GetInt();

			rapidjson::Value& st = val["stages"];
			CC_ASSERT(st.IsArray());
			if (st.IsArray())
			{
				if (st.Size() > 0)
				{
					for (size_t j = 0; j < st.Size(); j++)
					{
						pItem->_stages.push_back(st[j].GetInt());
					}
				}
				
			}

			rapidjson::Value& cds  = val["cards"];
			CC_ASSERT(cds.IsArray());
			if (cds.IsArray())
			{
				if (cds.Size() > 0)
				{
					for (size_t j = 0; j < cds.Size(); j++)
					{
						pItem->_cards.push_back(cds[j].GetInt());
					}
				}
			}


			rapidjson::Value& its  = val["shop_items"];
			CC_ASSERT(its.IsArray());
			if (its.IsArray())
			{
				if (its.Size() > 0)
				{
					for (size_t j = 0; j < its.Size(); j++)
					{
						rapidjson::Value& si_obj = its[j];
						CC_ASSERT(si_obj.IsObject());
						
						GameDefine::tBaseItemProb bip;
						bip.id = si_obj["item_id"].GetInt();
						bip.prob = (float)si_obj["update_prob"].GetDouble();

						pItem->_shopitems.push_back(bip);
					}
				}
			}
			addObject(pItem);
		}

	}while(false);

	return true;
}



template<>
bool GameData<cfg_Stage>::load(const char* file_name)
{
	if (!file_name)
	{
		assert(false && "skill info load failed: file_name null");
		return false;
	}

	rapidjson::Document doc;
	auto content = FileUtils::getInstance()->getDataFromFile(file_name);
	if (content.isNull())
	{
		CCLOG("file %s empty",file_name);
		return false;
	}


	std::string js((const char*)content.getBytes(), content.getSize());

	doc.Parse<0>(js.c_str());
	if(doc.HasParseError())
	{
		return false;
	}

	do 
	{
		for (size_t i=0; i<doc.Size(); ++i)
		{
			rapidjson::Value &val = doc[i];

			auto pItem = new GameDefine::cfg_Stage();

			pItem->id				= val["id"].GetInt();
			pItem->req_lvl			= val["req_lvl"].GetInt();
			pItem->req_stage_id		= val["req_stage_id"].GetInt();
			strcpy(pItem->szDesc,val["desc"].GetString());
			strcpy(pItem->szNpcPic,val["npc_pic"].GetString());
			pItem->phys_cost		= val["phys_cost"].GetInt();
			pItem->reward_gold		= val["reward_gold"].GetInt();
			strcpy(pItem->stage_path, val["stage_path"].GetString());

			rapidjson::Value &drops = val["drops"];

			if (drops.IsArray())
			{
				pItem->drops = new int[drops.Size() + 1];
				pItem->drops[0] = drops.Size();			
				for (int j = 0; j < pItem->drops[0]; j++)
				{
					 pItem->drops[1+j] = drops[j].GetInt();
				}
			}

			rapidjson::Value &monsters = val["monsters"];
			if (monsters.IsArray())
			{
				pItem->monsters = new int[monsters.Size() + 1];
				pItem->monsters[0] = monsters.Size();			
				for (int j = 0; j < pItem->monsters[0]; j++)
				{
					pItem->monsters[1+j] = monsters[j].GetInt();
				}
			}

			addObject(pItem);
		}


	}while(false);


	return true;

}




template<>
bool GameData<cfg_EquipItem>::load(const char* file_name)
{
	if (!file_name)
	{
		assert(false && "skill info load failed: file_name null");
		return false;
	}

	rapidjson::Document doc;
	auto content = FileUtils::getInstance()->getDataFromFile(file_name);
	if (content.isNull())
	{
		CCLOG("file %s empty",file_name);
		return false;
	}


	std::string js((const char*)content.getBytes(), content.getSize());

	doc.Parse<0>(js.c_str());
	if(doc.HasParseError())
	{
		return false;
	}


	do 
	{
		for (size_t i=0; i<doc.Size(); ++i)
		{
			rapidjson::Value &val = doc[i];
			auto pItem = new GameDefine::cfg_EquipItem();


			pItem->id			= val["id"].GetInt();

			// hook 一下
			auto item = g_ItemInfoMgr.getObject(pItem->id);
			if (!item)
			{
				CCLOG("card %d has base item info",pItem->id);
				CC_SAFE_DELETE(pItem);
				continue;
			}

			memcpy(pItem,item,sizeof(cfg_Item));
			pItem->equip_type = (EQUIP_TYPE)val["equip_type"].GetInt();
			pItem->add_phy_atk = val["phy_atk"].GetInt();
			pItem->add_mag_atk = val["mag_atk"].GetInt();
			pItem->add_phy_cri = val["phy_cri"].GetInt();
			pItem->add_mag_cri = val["mag_cri"].GetInt();


			if(!g_ItemInfoMgr.replaceObj(pItem->id,pItem))
			{
				CCLOG("item %d replace failed",pItem->id);
			}

		}

	}while(false);


	return true;
}





template<>
bool GameData<cfg_DropInfo>::load(const char* file_name)
{
	if (!file_name)
	{
		assert(false && "skill info load failed: file_name null");
		return false;
	}

	rapidjson::Document doc;
	auto content = FileUtils::getInstance()->getDataFromFile(file_name);
	if (content.isNull())
	{
		CCLOG("file %s empty",file_name);
		return false;
	}


	std::string js((const char*)content.getBytes(), content.getSize());

	doc.Parse<0>(js.c_str());
	if(doc.HasParseError())
	{
		return false;
	}


	do 
	{
		for (size_t i=0; i<doc.Size(); ++i)
		{
			rapidjson::Value &val = doc[i];
			auto pItem = new GameDefine::cfg_DropInfo();

			pItem->id = val["id"].GetInt();
			pItem->drop_group_cnt = val["drop_group_cnt"].GetInt();
			pItem->reward_gold = val["drop_gold"].GetInt();
			CC_ASSERT(pItem->drop_group_cnt <= GameDefine::GD_DROP_GROUP_CNT);
			for (int i = 0; i < pItem->drop_group_cnt; i++)
			{
				auto fmt_prob = __String::createWithFormat("drop_prob%d",i+1);
				pItem->m_drop_items[i].drop_prob = (float)val[fmt_prob->getCString()].GetDouble();

				auto fmt_item = __String::createWithFormat("drop_item_id%d",i+1);
				pItem->m_drop_items[i].drop_item_id = (float)val[fmt_item->getCString()].GetDouble();
			}

			addObject(pItem);
		}

	}while (false);
	
	return true;
}




template<>
bool GameData<cfg_Msg>::load(const char* file_name)
{

	if (!file_name)
	{
		assert(false && "skill info load failed: file_name null");
		return false;
	}

	rapidjson::Document doc;
	auto content = FileUtils::getInstance()->getDataFromFile(file_name);
	if (content.isNull())
	{
		CCLOG("file %s empty",file_name);
		return false;
	}


	std::string js((const char*)content.getBytes(), content.getSize());

	doc.Parse<0>(js.c_str());
	if(doc.HasParseError())
	{
		return false;
	}


	do 
	{
		for (size_t i=0; i<doc.Size(); ++i)
		{
			rapidjson::Value &val = doc[i];
			auto pItem = new GameDefine::cfg_Msg();

			pItem->id = val["id"].GetInt();
			pItem->msg_type = val["msg_type"].GetInt();
			strcpy(pItem->msg,val["msg"].GetString());

			addObject(pItem);
		}

	}while (false);

	return true;

}



template<>
bool GameData<cfg_Guide_Info>::load(const char* file_name)
{

	if (!file_name)
	{
		assert(false && "skill info load failed: file_name null");
		return false;
	}

	rapidjson::Document doc;
	auto content = FileUtils::getInstance()->getDataFromFile(file_name);
	if (content.isNull())
	{
		CCLOG("file %s empty",file_name);
		return false;
	}


	std::string js((const char*)content.getBytes(), content.getSize());

	doc.Parse<0>(js.c_str());
	if(doc.HasParseError())
	{
		return false;
	}


	do 
	{
		for (size_t i=0; i<doc.Size(); ++i)
		{
			rapidjson::Value &val = doc[i];
			auto pItem = new GameDefine::cfg_Guide_Info();


			pItem->id = val["id"].GetInt();
			pItem->op_type = val["op_type"].GetInt();
			pItem->req_guide_id = val["req_guide_id"].GetInt();
			rapidjson::Value& rect_infos = val["rect_infos"];
			CC_ASSERT(rect_infos.IsArray());

			for (size_t j = 0; j < rect_infos.Size(); j++)
			{
				rapidjson::Value& _rect = rect_infos[j];
				CC_ASSERT(_rect.IsObject());

				tGuideMaskInfo gmi;
				gmi.rect = Rect(_rect["x"].GetInt(),
					_rect["y"].GetInt(),
					_rect["width"].GetInt(),
					_rect["height"].GetInt());

				strcpy(gmi.ani_name,_rect["ani_name"].GetString());
				gmi.event_mask = _rect["event_mask"].GetInt();
				gmi.tip_type = (GUIDE_TIP_TYPE)_rect["tip_type"].GetInt();
				gmi.desc_id = _rect["desc_id"].GetInt();

				pItem->mask_infos.push_back(gmi);
			}

			strcpy(pItem->ani_path,val["gf_path"].GetString());


			for (int k = 0; k < GameDefine::cfg_Guide_Info::GUIDE_INFO_NUM; k++)
			{
				std::string fmt = StringUtils::format("gf_val%d",k+1);
				pItem->gf_vals[k] = val[fmt.c_str()].GetInt(); 
			}
			
			addObject(pItem);

		}


	}while (false);


	return true;
}






template<>
bool GameData<cfg_DailyTask_Info>::load(const char* file_name)
{

	if (!file_name)
	{
		assert(false && "skill info load failed: file_name null");
		return false;
	}

	rapidjson::Document doc;
	auto content = FileUtils::getInstance()->getDataFromFile(file_name);
	if (content.isNull())
	{
		CCLOG("file %s empty",file_name);
		return false;
	}


	std::string js((const char*)content.getBytes(), content.getSize());

	doc.Parse<0>(js.c_str());
	if(doc.HasParseError())
	{
		return false;
	}


	do 
	{
		for (size_t i=0; i<doc.Size(); ++i)
		{

			rapidjson::Value &val = doc[i];

			auto pItem = new cfg_DailyTask_Info();
			
			pItem->id = val["id"].GetInt();
			pItem->task_type = val["task_type"].GetInt();
			
			strcpy(pItem->task_desc,val["task_desc"].GetString());
			pItem->task_target = val["task_target"].GetInt();
			pItem->task_num = val["task_num"].GetInt();
			
			
			rapidjson::Value& rewards = val["task_rewards"];
			CC_ASSERT(rewards.IsArray());

			for (size_t j = 0; j < rewards.Size(); j++)
			{
				pItem->rewards.push_back(rewards[j].GetInt());
			}
			
			addObject(pItem);
		}

	}while(false);


	return true;
}




template<>
bool GameData<cfg_AssetsInfo>::load(const char* file_name)
{

	if (!file_name)
	{
		assert(false && "skill info load failed: file_name null");
		return false;
	}

	rapidjson::Document doc;
	auto content = FileUtils::getInstance()->getDataFromFile(file_name);
	if (content.isNull())
	{
		CCLOG("file %s empty",file_name);
		return false;
	}


	std::string js((const char*)content.getBytes(), content.getSize());

	doc.Parse<0>(js.c_str());
	if(doc.HasParseError())
	{
		return false;
	}


	do 
	{
		for (size_t i=0; i<doc.Size(); ++i)
		{
			rapidjson::Value &val = doc[i];

			auto pItem = new cfg_AssetsInfo();

			pItem->id = val["id"].GetInt();
			pItem->asset_load_type = (ASSETS_LOAD_TYPE)val["load_type"].GetInt();
			pItem->asset_type = (ASSETS_TYPE)val["res_type"].GetInt();
			pItem->asset_id = val["assets_id"].GetInt();
			pItem->base_path = val["path"].GetString();
			
			rapidjson::Value& files = val["files"];
			CC_ASSERT(files.IsArray());

			for (size_t j = 0; j < files.Size(); j++)
			{
				pItem->files.push_back(files[j].GetString());
			}

			TaoResManager::getInstance().parseCfgAssetInfo(pItem);
			addObject(pItem);
		}

	}while(false);

	return true;
}










//////////////////////////////////////////////////////////////////////////

ObjInfoMgr g_ObjInfoMgr;
MsgInfoMgr g_MsgInfoMgr;
SkillInfoMgr g_SkillInfoMgr;
BuffInfoMgr g_BuffInfoMgr;
BulletInfoMgr g_BulletInfoMgr;
ItemInfoMgr g_ItemInfoMgr;
CardInfoMgr g_CardInfoMgr;
CopyInfoMgr g_CopyInfoMgr;
StageInfoMgr g_StageInfoMgr;
EquipInfoMgr g_EquipInfoMgr;
DropInfoMgr g_DropInfoMgr;
GuideInfoMgr g_GuideInfoMgr;
DailyTaskMgr g_DailyTaskMgr;
AssetInfoMgr g_AssetInfoMgr;
