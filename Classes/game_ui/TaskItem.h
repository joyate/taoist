#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../GameDefine.h"


USING_NS_CC;
using namespace ui;


/*
 * 任务项 
 * 
 */




class UITaskItem : public Widget
{
public:
	UITaskItem(void);
	~UITaskItem(void);


	bool init();


	void initFromTask(const GameDefine::tDailyTaskInfo& _dti);


	// 更新状态
	void updateState(const GameDefine::tDailyTaskInfo& _dti);


	CREATE_FUNC(UITaskItem);
protected:

	//
	void touchEvent(Ref *pSender, Widget::TouchEventType type);

private:
	int m_task_id;
	Layout* m_layout;
};

