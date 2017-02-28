#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


class RewardLayer : public LayerColor
{
public:
	RewardLayer(void);
	~RewardLayer(void);

	enum
	{
		BR_TRI_STAR_LB = 2,		// 小于等于2人的是三星
		BR_TWO_STAR_LB = 5,		// 小于等于5人的是二星
	};


	enum
	{
		BR_STAR_NUM = 3,
	};


	//
	bool init();


	/*
	 * @desc 根据战斗结果初始化结算面板 
	 * @param _stage_id 关卡id
	 * @return
	 *	
	 */
	void initBattleResult(int _stage_id);


	// 计算战斗结果星级
	int calculateBRStar(int _defender_dead_cnt);


	CREATE_FUNC(RewardLayer);

protected:

	// 填充装备奖励
	void fillEquipReward();


	// 设置显示战斗结果评价星级
	void setBRStar();


	// 图片事件
	void touchEvent(Ref *pSender, Widget::TouchEventType type);

private:
	Layout* m_layout;
	int m_br_star_cnt; // 战斗评价星级
};

