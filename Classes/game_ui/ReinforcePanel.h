#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


/*
 * –ﬁ¡∂ΩÁ√Ê
 * 
 */







class ReinforcePanel : public Widget
{
public:
	ReinforcePanel(void);
	~ReinforcePanel(void);


	bool init();



	CREATE_FUNC(ReinforcePanel);
protected:

	//
	void touchEvent(Ref *pSender, Widget::TouchEventType type);


private:
	Layout* m_layout;
};

