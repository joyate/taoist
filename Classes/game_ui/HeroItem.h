#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../GameDefine.h"


USING_NS_CC;
using namespace ui;



/*
 * 英雄头像 
 * 
 *
 */


class HeroItem : public Widget
{
public:
	HeroItem(void);
	~HeroItem(void);


	enum
	{
		HI_MASK_LVL		= 1,		// 显示等级
		HI_MASK_CTRL	= 2,		// 显示统御力
	};



	bool init();


	/*
	 * @desc 从卡牌id里初始化
	 * @param _card 卡牌模板信息
	 * @return
	 *	
	 */
	bool initFromCfgItemInfo(const GameDefine::cfg_Card* _card, int mask);



	/*
	 * @desc 从实例id初始化
	 * @param _inst_id 卡牌实例id
	 * @return
	 *	
	 */
	bool initFromInstId(int _inst_id, int mask = 0);




	void showStar(int _star_lvl,bool bShow = true);



	CREATE_FUNC(HeroItem);
protected:


	// 设置边框样式
	void setFrameType(int _lvl);

private:
	Layout* m_layout;
};

