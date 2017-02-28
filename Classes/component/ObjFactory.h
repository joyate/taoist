#pragma once
#include "../data/GameData.h"



class ObjFactory
{
public:
	ObjFactory(int& _begin_item_id);
	~ObjFactory(void);


	static ObjFactory& getInstance();


	/*
	 * @desc 产生物品
	 * @param 物品模板id
	 * @return
	 *	
	 */
	tItemInfo* createItem(int _item_temp_id, int _item_cnt = 1);


	


private:
	// 最新的实例物品id
	int& base_item_id;

	static ObjFactory* s_objFactory;
};

