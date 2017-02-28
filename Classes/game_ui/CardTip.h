#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class CardTip : public Widget
{
public:
	CardTip(void);
	~CardTip(void);


	bool init();


	/*
	 * @desc ³õÊ¼»¯
	 * @param _id Ä£°åid
	 * @param _lvl
	 * @return
	 *	
	 */
	void initFrom(int _id,int _lvl = 1);



	CREATE_FUNC(CardTip);
protected:




private:
	Layout* m_layout;

};

