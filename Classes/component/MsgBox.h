#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class MsgBox : public LayerColor
{
public:
	MsgBox(void);
	~MsgBox(void);
	

	enum 
	{
		MB_TYPE_EXIT_GAME = 1,					// 退出游戏
		MB_TYPE_TIP = 2,						// 提示
	};


	CREATE_FUNC(MsgBox);
	bool init() { return LayerColor::init();}
	bool initMsg(int _msg_type_id,int _msg_title_id,int _msg_content_id,bool bModel = true);


protected:

	void touchEvent(Ref *pSender, Widget::TouchEventType type);


	// 屏蔽按键
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
	{
		return true;
	}

private:
	Widget* m_node;

	int m_type;				// 本对话框的类型
	int m_msg_id;			// 消息id
};

