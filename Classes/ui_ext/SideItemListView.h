#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class FightUI;

class SideItemListView : public ListView
{
public:
	SideItemListView(void);
	~SideItemListView(void);


	enum DIR_OP
	{
		DIR_SHOP_LIST_NONE,
		DIR_SHOP_LIST_VERTICAL,
		DIR_SHOP_LIST_HORIZONTAL,
	};


	bool init();



	void initFromLocalPlayer(FightUI* _owner);


	void setOpDir(int _dir)		{ m_op = (DIR_OP)_dir;}



	CREATE_FUNC(SideItemListView);
protected:

	//
	virtual void interceptTouchEvent(Widget::TouchEventType event,Widget* sender,Touch* touch) override;

protected:

	DIR_OP m_op;
};

