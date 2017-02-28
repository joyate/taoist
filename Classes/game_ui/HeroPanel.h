#pragma once
#include "../GameDefine.h"

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;



/*
 * 英雄信息列表面板
 */



class HeroPanel : public Widget
{
public:
	HeroPanel(void);
	~HeroPanel(void);


	enum
	{
		LINE_COUNT_MAX = 2,


		HP_SHOWTYPE_HERO = GameDefine::AT_ARMY_HERO,
		HP_SHOWTYPE_ARMY = GameDefine::AT_ARMY_SOLDIER,

	};


	bool init();


	// 实例数据初始化
	bool updatePanelInfo(int cur_show_type);


	CREATE_FUNC(HeroPanel);

protected:

	// 面板触摸事件
	void touchEvent(Ref *pSender, Widget::TouchEventType type);

	// 子项触摸事件
	void cardTouchEvent(Ref *pSender, Widget::TouchEventType type);

private:
	Layout* m_layout;
	int m_show_type;
};

