#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


/*
 * 卡牌信息
 *
 *
 */





class UICard : public Widget
{
public:
	UICard(void);
	~UICard(void);


	// 卡等级，颜色
	enum
	{
		CARD_COLOR_WHITE = 1,
		CARD_COLOR_GREEN = 2,
		CARD_COLOR_BLUE = 3,
		CARD_COLOR_PURPLE = 4,
		CARD_COLOR_ORANGE = 5,
	};


	bool init();


	// 填充实例数据
	void onEnter();

	CREATE_FUNC(UICard);

protected:

	// 设置星级
	void setStarLvl(int _star_lvl);

	// 设置卡等级（白卡，绿卡，蓝卡，紫卡，橙卡）
	void setCardLvl(int _card_lvl);

	// 设置卡牌形象
	void setCardImage(const char* sz_file_name);

	// 设置魂魄需求
	void setCardGhostReq(int _val);

	// 设置声望需求
	//void setCardPrestigeReq(int _val);


private:

	Layout* m_layout;
};

