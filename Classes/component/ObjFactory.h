#pragma once
#include "../data/GameData.h"



class ObjFactory
{
public:
	ObjFactory(int& _begin_item_id);
	~ObjFactory(void);


	static ObjFactory& getInstance();


	/*
	 * @desc ������Ʒ
	 * @param ��Ʒģ��id
	 * @return
	 *	
	 */
	tItemInfo* createItem(int _item_temp_id, int _item_cnt = 1);


	


private:
	// ���µ�ʵ����Ʒid
	int& base_item_id;

	static ObjFactory* s_objFactory;
};

