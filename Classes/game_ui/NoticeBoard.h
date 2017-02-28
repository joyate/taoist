#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


/*
 * ��������
 *
 *
 */



class NoticeBoard : public Layer
{
public:
	NoticeBoard(void);
	~NoticeBoard(void);

	// ����id,
	enum
	{
		NB_CONTENT_ID = 1000,
	};


	bool init();



	// ��title
	void changeTitle(const std::string& _title_png);
	// �������
	void addString(const std::string& _content);


	//
	CREATE_FUNC(NoticeBoard);


protected:

	void touchEvent(Ref *pSender, Widget::TouchEventType type);


private:
	Layout* m_layout;
};

