#include "Bag.h"
#include "ObjFactory.h"

Bag::Bag()
{

}

Bag::~Bag()
{

}


bool Bag::addItem( tItemInfo* _item )
{
	if (!_item)
	{
		return false;
	}

	if (full())
	{
		CCLOG("bag full");
		return false;
	}

	return m_bag.addItem(_item);

}



int Bag::addTempItem( int _item_temp_id,int _cnt /*= 1*/)
{

	if (full())
	{
		CCLOG("bag full");
		return 0;
	}

	int to_add_cnt = _cnt;
	int cur_add_cnt = 0;
	tBagInfo::item_iter _iter = m_bag.m_items.begin();

	do 
	{		
		if (_iter->second->item_temp_id == _item_temp_id)
		{
			if (_iter->second->item_num + _cnt <= GameDefine::GD_ITEM_GRID_CNT)
			{
				_iter->second->item_num += _cnt;
				cur_add_cnt += _cnt;
			}
		}

		_iter++;

	} while (_iter != m_bag.m_items.end() && cur_add_cnt < to_add_cnt);


	// »¹Ã»ÓĞÌîÂú
	if (cur_add_cnt < to_add_cnt)
	{
		int nLeftCnt = to_add_cnt - cur_add_cnt;
		auto _item = ObjFactory::getInstance().createItem(_item_temp_id,nLeftCnt);
		if(_item)
		{
			cur_add_cnt += nLeftCnt;
			m_bag.addItem(_item);
		}
	}

	return cur_add_cnt;
}













