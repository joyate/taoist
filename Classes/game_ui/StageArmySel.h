#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;




class StageArmySel : public Widget
{
public:
	StageArmySel(void);
	~StageArmySel(void);


	enum
	{
		BAG_ITEM_COL_MAX = 4,

		// 拖拽有效阈值
		DRAG_ACT_LENGTH = 16,

		BASE_FE_TYPE = 100,
	};


	bool init();


	// 刷新小兵数据
	void updateArmyInfo();

	// 刷新英雄数据
	void updateHeroInfo();

	//
	void setCurStageId(int _stage_id)		{ m_stage_id = _stage_id;}


	CREATE_FUNC(StageArmySel);
protected:

	// 按钮点击事件
	void btnTouchEvent(Ref *pSender, Widget::TouchEventType type);

	// 选择英雄触摸事件
	void heroCardTouchEvent(Ref *pSender, Widget::TouchEventType type);

	// 选择小兵触摸事件
	void armyCardTouchEvent(Ref *pSender, Widget::TouchEventType type);

	// 英雄选择取消触摸事件
	void heroCardCancelTouchEvent(Ref *pSender, Widget::TouchEventType type);

	// 小兵选择取消事件
	void armyCardCancelTouchEvent(Ref *pSender, Widget::TouchEventType type);


	// 附加小兵
	void appendArmy(int _sel_index);


private:
	Layout* m_layout;
	int m_wx_type;
	int m_stage_id;
};

