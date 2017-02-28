#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;



class StageDesc : public Layer
{
public:
	StageDesc(void);
	~StageDesc(void);


	// 本层特殊标识
	enum
	{
		TAG_OWNER_LAYER = 0x3F02,
		
		// 五行顶层显示层级
		TOP_IMG_BTN_LAYER = 6,

		// 一行最多显示4个
		BAG_ITEM_COL_MAX = 4,

		// 五行按钮基准
		WX_BASE_TAG = 100,


		// tip
		TAG_TIP_NODE = 0x3F03,

	};


	enum
	{
		ST_ARMY = 1,
		ST_HERO,
	};


	// 步骤
	enum 
	{
		SST_COPY_DESC,
		SST_ARMY_SELECT,
		SST_MAX,
	};



	bool init();


	// 从副本表初始化
	bool initFromStageId(int _copy_id);


	// 更新物品
	void updateItem(int army_type,int wx_type);

	// 刷新面板已经选择的英雄，小兵数据
	// _sel_index 当前选择的小兵索引
	void updateSelectedItem(int _sel_index);


	//
	CREATE_FUNC(StageDesc);

protected:

	// 点击事件
	void btnTouchEvent(Ref *pSender, Widget::TouchEventType type);
	// 
	void imgTouchEvent(Ref *pSender, Widget::TouchEventType type);
	// 选择英雄，小兵触摸事件
	void cardTouchEvent(Ref *pSender, Widget::TouchEventType type);
	// 选择取消触摸事件
	void cardSelCancelTouchEvent(Ref *pSender, Widget::TouchEventType type);

	//
	void selectedItemEvent(Ref* pSender, ListView::EventType type);


	// 显示详细信息
	void showDetailTip(Ref *pSender, Widget::TouchEventType type);


	// page view 事件
	void pageViewEvent(Ref *pSender, PageView::EventType type);

private:
	Layout* m_layout;
	
	int m_cur_step;						// 当前第几步			

	int m_fe_type;						// 五行类型
	int m_army_type;					// 兵种选择类型（英雄,小兵）
	int m_last_zorder;					// 五行按钮排序
	std::string m_last_img_btn_name;
	std::string m_last_amry_type_name;	// 兵种类型
};

