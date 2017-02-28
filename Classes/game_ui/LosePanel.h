#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;



class LosePanel : public LayerColor
{
public:
	LosePanel(void);
	~LosePanel(void);


	bool init();

	
	CREATE_FUNC(LosePanel);
protected:

	void touchEvent(Ref *pSender, Widget::TouchEventType type);

private:
	Layout* m_layout;
};

