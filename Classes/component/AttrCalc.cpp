#include "AttrCalc.h"
#include "../data/LocalPlayer.h"
#include "../data/GameData.h"



const float STR_2_PHY_FACTOR = 1.0f;
const float STR_2_MAG_FACTOR = 0.2f;

const float WIS_2_PHY_FACTOR = 0.1f;
const float WIS_2_MAG_FACTOR = 1.0f;

const float AGI_2_CRI_FACTOR = 1.f;


/*
 * 战斗力的计算公式
 * 
 * （物理攻击 + 法术攻击）/2 * 0.5 + (物理防御 + 法术防御）/2 * 0.3 + 暴击 *0.2
 */

int AttrCalc::calcFight( const GameDefine::tCardInfo& _card_info )
{

	auto cfg_card = (cfg_Card*)g_CardInfoMgr.getObject(_card_info.item_temp_id);
	if (!cfg_card)
	{
		CCLOG("card id %d has no data",_card_info.item_temp_id);
		return 0;
	}


	auto cfg_obj_attr = (cfg_Obj_Attr*)g_ObjInfoMgr.getObject(cfg_card->obj_id);
	if (!cfg_obj_attr)
	{
		CCLOG("obj id %d has no data",cfg_card->obj_id);
		return 0;
	}


	float phy_atk = cfg_obj_attr->phy_atk + cfg_obj_attr->strength * (_card_info.m_lvl - 1) * STR_2_PHY_FACTOR;
	float mag_atk = cfg_obj_attr->mag_atk + cfg_obj_attr->wise * (_card_info.m_lvl - 1) * WIS_2_MAG_FACTOR;
	float atk_cri = cfg_obj_attr->atk_cri + cfg_obj_attr->agility * (_card_info.m_lvl - 1) * AGI_2_CRI_FACTOR;



	return 0;
}
