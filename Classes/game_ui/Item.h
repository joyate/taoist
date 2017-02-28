#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


/*
 * 物品面板
 * 	
 */




class UIItem : public Widget
{
public:
	UIItem(void);
	~UIItem(void);


	bool init();


	/*
	 * @desc 从物品模板id初始化
	 * @param _item_temp_id 模板id
	 * @param _item_cnt 数量
	 * @return
	 *	
	 */
	bool initFromItemTempId(int _item_temp_id, int _item_cnt = 1);



	/*
	 * @desc 从物品实例id初始化
	 * @param _item_id 物品实例id
	 * @return
	 *	
	 */
	bool initFromItemId(int _item_id);



	// 设置星级
	void setStarLvl(int _lvl);
	// 设置个数
	void setItemCnt(int _cnt);



	CREATE_FUNC(UIItem);

private:

	Layout* m_layout;
};

