#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameDefine.h"

USING_NS_CC;
using namespace ui;



/*
 * �ؿ�����
 *
 *
 */





class StageItem : public Widget
{
public:
	StageItem(void);
	~StageItem(void);



	bool init();

	
	// ���ùؿ��Ǽ�
	void setStageStar(int _star_num);


	void onEnter();


	CREATE_FUNC(StageItem);

protected:

	//
	void touchEvent(Ref *pSender, Widget::TouchEventType type);


	// ��ȡ����layer
	Layer* getRootLayer();



private:

	Layout* m_layout;
};

