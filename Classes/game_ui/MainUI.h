#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class LocalPlayer;
class MainUI : public Layer
{
public:
	MainUI(void);
	~MainUI(void);


	enum
	{
		MAIN_FUNC_UI_PADDING = 5,


		TAG_MAIN_FUNC_MENU = 0x7f1,
	};


	enum
	{
		TAG_MENU_ITEM_HERO = 301,
		TAG_MENU_ITEM_BAG,
		TAG_MENU_ITEM_UNK_1,
		TAG_MENU_ITEM_UNK_2,
		TAG_MENU_ITEM_UNK_3,
	};


	// �ɵ��node���¼�TAG
	enum TAG_TOUCH_ITEM
	{

	};


	bool init();


	// ��ʼ���������
	void initFromPlayer(LocalPlayer* _lp);



	void onEnter();


	// callback

	// �����ܻص�
	void MainFuncCallback(Ref* _ref);
	//
	void touchEvent(Ref *pSender, Widget::TouchEventType type);

	//
	CREATE_FUNC(MainUI);

private:
	bool m_bShow;
	Layout* m_layout;

	EventListener* m_ui_update_listener;
};

