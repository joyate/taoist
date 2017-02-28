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
		// ����ͼ��zorder
		SKILL_ICON_LAYER = 700,
		// С��ͼ��zorder
		ARMY_ICON_LAYER = SKILL_ICON_LAYER,


		// ����ˢ�¼��
		GHOST_UPDATE_INTERVAL = 1,


		// head up info
		TAG_HUI_NODE = 0x3F12,
		TAG_CARD_TIP_NODE = 0x3F13,

	};


	bool init();


	// ��ʼ��С�����
	bool initFromLocalPlayer();
	// Ϊ�˷������MapManager
	void setMapManager(MapManager* _map_mgr)		{ _mapMgr = _map_mgr;}
	// ��ʼ��Ӣ������
	bool initHeroData(int _inst_card_id);


	virtual void update(float delta) override;


	// 
	void updateHeroInfo();
	// ˢ������ֵ�������㻹�ǲ�����
	void updateSideItemGhost();



	// ѡ����ӦС��
	void touchShopItemEvent( Ref *pSender, Widget::TouchEventType type );


	//////////////////////////////////////////////////////////////////////////

	//
	CREATE_FUNC(FightUI);

protected:


	// �ƶ��������
	void moveItemEvent(Ref *pSender, Widget::TouchEventType type);

	// ��ѡ�����
	void touchShopEvent( Ref *pSender, Widget::TouchEventType type );

	// ���������¼�
	void touchSkillEvent(Ref *pSender, Widget::TouchEventType type);


	// TouchEvent
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);


	// ��ʼ�������ֵ
	void initUI();
	// �������
	void cleanUI();

private:

	Layout* m_layout;
	MapManager* _mapMgr;

	Node* m_skill_icon;				// ����ָʾͼ��
	int m_base_ghost;				// ��������ֵ
	DIR_OP m_sideitem_op_dir;


	//
	bool m_bShopShow;
	Sprite* m_drag_sprite;			// С��ָʾͼ��

	
	EventListener* m_reward_update_listener;
	EventListener* m_hero_info_update_listener;
};

