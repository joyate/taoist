#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


/*
 * 公告栏类
 *
 *
 */



class NoticeBoard : public Layer
{
public:
	NoticeBoard(void);
	~NoticeBoard(void);

	// 内容id,
	enum
	{
		NB_CONTENT_ID = 1000,
	};


	bool init();



	// 换title
	void changeTitle(const std::string& _title_png);
	// 添加文字
	void addString(const std::string& _content);


	//
	CREATE_FUNC(NoticeBoard);


protected:

	void touchEvent(Ref *pSender, Widget::TouchEventType type);


private:
	Layout* m_layout;
};

