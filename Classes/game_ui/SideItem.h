#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;



class SideItem : public Widget
{
public:
	SideItem(void);
	~SideItem(void);


	bool init();


	// 从卡牌实例ID初始化本侧边UI
	bool initFromCardInstance(int _card_inst_id);


	// 实例id
	int getInstId() const	{ return m_inst_id;}
	// 获取obj id
	int getObjId() const	{ return cached_obj_id;}

	// 设置卡牌星级
	void setStarLvl(int _lvl);

	
	/*
	 * @desc 更新小兵灵气显示状态，满足与不满足
	 * @param _cur_ghost 当前有效的灵气数
	 * @return
	 *	
	 */
	void updateGhostState(int _cur_ghost);


	//
	void hookHeadPicListener(Widget::ccWidgetTouchCallback _callback);
	void onEnterColddown();
	bool isColddown() const		{return m_bMaskRunning;}

	CREATE_FUNC(SideItem);

protected:

	//
	void touchEvent(Ref *pSender, Widget::TouchEventType type);



	// 设置灵气值
	void setGhost(int _ghost,const Color3B& _color);


	// 冷却完成回调
	void cdover();


	// 调整加入mask后的层级关系
	void adjustLocalOrder(int base_order);


private:
	int m_inst_id;				// 实例id
	int cached_obj_id;
	Layout* m_layout;
	ProgressTimer* m_mask;
	bool m_bMaskRunning;
};

