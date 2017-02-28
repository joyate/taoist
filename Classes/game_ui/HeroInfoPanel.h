#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../data/GameData.h"


USING_NS_CC;
using namespace ui;





/*
 * 英雄面板子项UI
 *
 */





class HeroInfoPanel	: public Widget
{
public:
	HeroInfoPanel(void);
	~HeroInfoPanel(void);



	bool init();


	/*
	 * @desc 从实例卡id初始化面板
	 * @param _card_inst_id 卡实例id
	 * @return 是否初始成功
	 *	
	 */
	bool initFromInstCardInfo(const GameDefine::tItemInfo* _item_info);


	// 设置星级
	void setStarLvl(int _lvl);
	// 设置边框
	void setHeadFrame(int _lvl);
	// 设置五行
	void setFiveElement(int fe_type);


	CREATE_FUNC(HeroInfoPanel);

private:
	Layout* m_layout;
};

