#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;



class HeadUpInfo : public Widget
{
public:
	HeadUpInfo(void);
	~HeadUpInfo(void);


	bool init();


	virtual void onEnter() override;

	void setOwnerId(int _id)	{ m_owner_id = _id;}


	CREATE_FUNC(HeadUpInfo);
protected:


	void btnTouchEvent(Ref *pSender, Widget::TouchEventType type);

private:
	Layout* m_layout;

	int m_owner_id;
};

