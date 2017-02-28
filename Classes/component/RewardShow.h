#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


class RewardShow : public LayerColor
{
public:
	RewardShow(void);
	~RewardShow(void);


	enum
	{
		RS_TYPE_CARD = 1,
		RS_TYPE_ITEM,
	};


	bool init();

	
	//
	void initReward(int rw_type,int _temp_item_id);


	CREATE_FUNC(RewardShow);
protected:

	//
	Widget* createWidget(int _type);

	//
	void callback();

	//
	void touchEvent(Ref *pSender, Widget::TouchEventType type);

	//
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

private:
	int m_type;
	int m_item_id;
};

