#pragma once
#include "cocos2d.h"
#include "utility/ObjectManager.h"
#include "ai/GameEntity.h"
#include "ui/CocosGUI.h"
#include "../MapManager.h"


USING_NS_CC;
using namespace cocos2d::ui;



// ս������
class BattleScene : public Scene
{
public:
	BattleScene(void);
	~BattleScene(void);


	enum
	{
		TAG_BS_SHOP_EVENT,



		TAG_MAP_LAYER = 10,

	};


	bool initialize(int _scene_id);


	virtual void onEnter();
	virtual void onExit();



	// ����ս������
	bool addToMap(GameEntity* _obj);


	// 
	virtual void update(float delta);



	MapManager& getCurMapMgr()			{ return m_mapMgr; }


#ifdef _DEBUG
	const Vec2& getMapBeginPos() const
	{
		return m_mapMgr.getPosition();
	}
#endif



	CREATE_FUNC(BattleScene);

protected:

	// shop �¼�
	void touchShopEvent( Ref *pSender, Widget::TouchEventType type );

	// shop item �¼�
	void touchShopItemEvent( Ref *pSender, Widget::TouchEventType type );


	// TouchEvent
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);


	void initShopUI();



private:
	
	// shop
	Node* m_shop_layout;
	
	// map
	MapManager m_mapMgr;

	bool m_bShopShow;
	Sprite* m_drag_sprite;
};

