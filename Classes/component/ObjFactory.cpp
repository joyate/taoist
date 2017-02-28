#include "ObjFactory.h"
#include "../data/LocalPlayer.h"
#include "../data/GameData.h"

ObjFactory* ObjFactory::s_objFactory = nullptr; 


ObjFactory::ObjFactory(int& _begin_item_id):
	base_item_id(_begin_item_id)
{
}


ObjFactory::~ObjFactory(void)
{
}


ObjFactory& ObjFactory::getInstance()
{
	if (!s_objFactory)
	{
		s_objFactory = new ObjFactory(LocalPlayer::getInstance()->m_global.lastItemId);
	}

	return *s_objFactory;
}



tItemInfo* ObjFactory::createItem( int _item_temp_id, int _item_cnt /*= 1*/)
{
	auto _item_info = g_ItemInfoMgr.getObject(_item_temp_id);
	if (!_item_info)
	{
		CCLOG("item id %d has no data",_item_temp_id);
		return nullptr;
	}


	tItemInfo* nRet = nullptr;

	switch (_item_info->item_type)
	{
	case IT_ITEM:
	case IT_FRAG:
		{
			auto pItem = new tItemInfo();
			pItem->item_num = _item_cnt;


			nRet = pItem;
		}
		break;
	case IT_EQUIP:
		{
			auto pItem = new tEquipInfo();
			pItem->item_num = _item_cnt;


			nRet = pItem;
		}
		break;
	case IT_CARD:
		{
			auto pItem = new tCardInfo();
			CC_ASSERT(_item_cnt == 1);
			pItem->m_lvl = _item_info->item_lvl;
			pItem->item_num = 1;


			nRet = pItem;
		}
		break;
	default:
		CC_ASSERT(false && "invalid item type");
		break;
	}

	nRet->item_temp_id = _item_temp_id;
	nRet->item_id = base_item_id++;
	return nRet;
}


