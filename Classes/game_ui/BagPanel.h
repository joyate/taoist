#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


/*
 * �������
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
		// һ��������Ʒ����
		ONELINE_ITEM_CNT_MAX = 8,
	};


	bool init();


	void initFromPlayer();


	CREATE_FUNC(BagPanel);
protected:


	// �����¼�
	void touchEvent(Ref *pSender, Widget::TouchEventType type);


	// �����Ʒ���¼�
	void itemTouchEvent(Ref *pSender, Widget::TouchEventType type);


private:

	Layout* m_layout;
};

