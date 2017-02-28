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
		MB_TYPE_EXIT_GAME = 1,					// �˳���Ϸ
		MB_TYPE_TIP = 2,						// ��ʾ
	};


	CREATE_FUNC(MsgBox);
	bool init() { return LayerColor::init();}
	bool initMsg(int _msg_type_id,int _msg_title_id,int _msg_content_id,bool bModel = true);


protected:

	void touchEvent(Ref *pSender, Widget::TouchEventType type);


	// ���ΰ���
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
	{
		return true;
	}

private:
	Widget* m_node;

	int m_type;				// ���Ի��������
	int m_msg_id;			// ��Ϣid
};

