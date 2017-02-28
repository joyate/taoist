#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


class MapManager;

class FightUI : public Layer
{
public:
	FightUI(void);
	~FightUI(void);



	enum DIR_OP
	{
		DIR_SHOP_LIST_NONE,
		DIR_SHOP_LIST_VERTICAL,
		DIR_SHOP_LIST_HORIZONTAL,
	};


	enum
	{
		// 
		TAG_SHOP_BTN = 0x3F11,
		// 
		SHOP_BTN_LAYER = 9,
		// 技能图标zorder
		SKILL_ICON_LAYER = 700,
		// 小兵图标zorder
		ARMY_ICON_LAYER = SKILL_ICON_LAYER,


		// 灵气刷新间隔
		GHOST_UPDATE_INTERVAL = 1,


		// head up info
		TAG_HUI_NODE = 0x3F12,
		TAG_CARD_TIP_NODE = 0x3F13,

	};


	bool init();


	// 初始化小兵面板
	bool initFromLocalPlayer();
	// 为了方便访问MapManager
	void setMapManager(MapManager* _map_mgr)		{ _mapMgr = _map_mgr;}
	// 初始化英雄数据
	bool initHeroData(int _inst_card_id);


	virtual void update(float delta) override;


	// 
	void updateHeroInfo();
	// 刷新灵气值，是满足还是不满足
	void updateSideItemGhost();



	// 选择相应小兵
	void touchShopItemEvent( Ref *pSender, Widget::TouchEventType type );


	//////////////////////////////////////////////////////////////////////////

	//
	CREATE_FUNC(FightUI);

protected:


	// 移动兵种面板
	void moveItemEvent(Ref *pSender, Widget::TouchEventType type);

	// 打开选择面板
	void touchShopEvent( Ref *pSender, Widget::TouchEventType type );

	// 触摸技能事件
	void touchSkillEvent(Ref *pSender, Widget::TouchEventType type);


	// TouchEvent
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);


	// 初始化面板数值
	void initUI();
	// 清理界面
	void cleanUI();

private:

	Layout* m_layout;
	MapManager* _mapMgr;

	Node* m_skill_icon;				// 技能指示图标
	int m_base_ghost;				// 基础灵气值
	DIR_OP m_sideitem_op_dir;


	//
	bool m_bShopShow;
	Sprite* m_drag_sprite;			// 小兵指示图标

	
	EventListener* m_reward_update_listener;
	EventListener* m_hero_info_update_listener;
};

