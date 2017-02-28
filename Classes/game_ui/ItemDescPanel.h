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
	 * @desc 从实例物品id初始化
	 * @param _id 实例物品id
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

