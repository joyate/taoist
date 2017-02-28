#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameDefine.h"

USING_NS_CC;
using namespace ui;


/*
 * 副本商店物品
 *
 */



class CopyShopItem : public Widget
{
public:
	CopyShopItem(void);
	~CopyShopItem(void);



	bool init();


	// 从商店物品变初始化
	bool initFromShopItemId(int _item_id);


	// 设置购买状态
	void setBoughtState(bool _bought);
	
	// 设置物品属于那个副本的
	void setCopyId(int _copy_id)
	{
		m_copy_id = _copy_id;
	}
	// 设置物品索引，用于设置购买掩码
	void setItemIndex(int _item_index)
	{
		m_item_index = _item_index;
	}




	// 初始化示例数据
	void onEnter();


	//
	CREATE_FUNC(CopyShopItem);
	
protected:

	void touchEvent(Ref *pSender, Widget::TouchEventType type);

private:

	int m_copy_id;					// 副本id
	int m_item_index;				// 物品索引
	Layout* m_layout;

};

