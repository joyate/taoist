#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;




class ItemDescPanel : public Widget
{
public:
	ItemDescPanel(void);
	~ItemDescPanel(void);



	bool init();

	/*
	 * @desc ��ʵ����Ʒid��ʼ��
	 * @param _id ʵ����Ʒid
	 * @return
	 *	
	 */
	void initFromInstItemId(int _id);


	CREATE_FUNC(ItemDescPanel);

protected:


	//
	void touchEvent(Ref *pSender, Widget::TouchEventType type);


private:
	Layout* m_layout;
};

