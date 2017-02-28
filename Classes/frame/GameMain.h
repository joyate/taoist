#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

USING_NS_CC;


class GameMain : public cocos2d::Layer
{
public:
	GameMain(void);
	~GameMain(void);

	
	enum TAG_BUTTON_NAME
	{
		TAG_TA = 18,
		TAG_UNK = 20,
		TAG_MIAO = 24,
		TAG_LU = 133,
		TAG_CAVE = 145,
		TAG_SHOP = 32,
	};



	enum
	{
		// ���ʶ����Сƽ����
		TOUCH_IDENTIFY_INTERVAL = 16,
	};


	//static Scene* scene();



	virtual bool init();
	virtual void onEnter();


	void update(float fDelta) override;
	


	CREATE_FUNC(GameMain);

protected:

	void touchEvent(Ref *pSender, Widget::TouchEventType type);


private:

	cocos2d::ui::Layout* _pNode;
	// ��¼�м�ĵ�λ�ã�
	Vec2 _pos;
	// �����Ƿ���Ч
	bool _bTouchOK;
};

