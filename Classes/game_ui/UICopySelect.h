#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"



USING_NS_CC;
using namespace ui;


class LocalPlayer;


class UICopySelect : public Layer
{
public:
	UICopySelect(void);
	~UICopySelect(void);


	enum CS_PAGE_INDEX
	{
		CS_COPY = 1,
		CS_HERO,
		CS_SHOP,
	};


	// 商店一些配置信息
	enum
	{
		CS_SHOP_ROW = 2,
		CS_SHOP_COL = 4,


		SHOP_ITEM_UPDATE_INTERVAL = 900,
	};


	// 本层特殊标识
	enum
	{
		TAG_OWNER_LAYER = 0x3F01,
	};


	bool init();


	// 用于刷新时间
	virtual void update(float delta) override;




	// 用玩家信息初始化副本信息
	bool applyCopyInfoWithRoleData(int _copy_id);




	CREATE_FUNC(UICopySelect);

protected:

	// image 点击事件
	void touchEvent(Ref *pSender, Widget::TouchEventType type);
	// hero购买事件
	void btnTouchEvent(Ref *pSender, Widget::TouchEventType type);
	// 购买事件
	void buyTouchEvent(Ref *pSender, Widget::TouchEventType type);

	// 初始化副本选择UI
	bool initCopySelect(int _copy_id);
	// 初始化英雄选择UI
	bool initHeroSelect(int _copy_id);
	// 初始化副本商店
	bool initCopyShop(int _copy_id);


	// 更新pageview
	void updatePageView(int _new_page_index);


	// 时间刷新
	void timeUpdate(float delta);


private:

	Layout* m_layout;
	CS_PAGE_INDEX m_cur_page_index;			// 当前所在的关卡页索引
	int m_copy_id;

	// 剩余的刷新时间
	float m_left_update_time;
};

