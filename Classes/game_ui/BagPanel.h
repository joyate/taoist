#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


/*
 * 背包面板
 *
 *
 */



class BagPanel : public Widget
{
public:
	BagPanel(void);
	~BagPanel(void);


	enum
	{
		// 一行最大的物品个数
		ONELINE_ITEM_CNT_MAX = 8,
	};


	bool init();


	void initFromPlayer();


	CREATE_FUNC(BagPanel);
protected:


	// 界面事件
	void touchEvent(Ref *pSender, Widget::TouchEventType type);


	// 点击物品项事件
	void itemTouchEvent(Ref *pSender, Widget::TouchEventType type);


private:

	Layout* m_layout;
};

