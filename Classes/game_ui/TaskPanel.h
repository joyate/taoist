#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


/*
 * �������
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


	// ����ҳ�ʼ��
	bool initFromPlayer();


	CREATE_FUNC(TaskPanel);
protected:

	//
	void touchEvent(Ref *pSender, Widget::TouchEventType type);

private:
	Layout* m_layout;
};

