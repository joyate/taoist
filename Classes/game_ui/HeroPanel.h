#pragma once
#include "../GameDefine.h"

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;



/*
 * Ӣ����Ϣ�б����
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


	// ʵ�����ݳ�ʼ��
	bool updatePanelInfo(int cur_show_type);


	CREATE_FUNC(HeroPanel);

protected:

	// ��崥���¼�
	void touchEvent(Ref *pSender, Widget::TouchEventType type);

	// ������¼�
	void cardTouchEvent(Ref *pSender, Widget::TouchEventType type);

private:
	Layout* m_layout;
	int m_show_type;
};

