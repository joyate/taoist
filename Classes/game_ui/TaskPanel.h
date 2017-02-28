#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


/*
 * 任务面板
 * 
 * 
 *	
 */





class TaskPanel : public Widget
{
public:
	TaskPanel(void);
	~TaskPanel(void);


	bool init();


	// 从玩家初始化
	bool initFromPlayer();


	CREATE_FUNC(TaskPanel);
protected:

	//
	void touchEvent(Ref *pSender, Widget::TouchEventType type);

private:
	Layout* m_layout;
};

