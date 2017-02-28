#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameDefine.h"

USING_NS_CC;
using namespace ui;



/*
 * 关卡子项
 *
 *
 */





class StageItem : public Widget
{
public:
	StageItem(void);
	~StageItem(void);



	bool init();

	
	// 设置关卡星级
	void setStageStar(int _star_num);


	void onEnter();


	CREATE_FUNC(StageItem);

protected:

	//
	void touchEvent(Ref *pSender, Widget::TouchEventType type);


	// 获取最顶层的layer
	Layer* getRootLayer();



private:

	Layout* m_layout;
};

