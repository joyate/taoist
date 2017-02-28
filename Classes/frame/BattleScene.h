#pragma once
#include "cocos2d.h"
#include "utility/ObjectManager.h"
#include "ai/GameEntity.h"
#include "ui/CocosGUI.h"
#include "MapManager.h"


USING_NS_CC;
using namespace cocos2d::ui;



// 战斗场景
class BattleScene : public Scene
{
public:
	BattleScene(void);
	~BattleScene(void);


	enum
	{
		// 
		TAG_SHOP_BTN = 0x3F11,

		// 
		SHOP_BTN_LAYER = 9,
		

		// fightui tag
		TAG_FIGHT_UI = 0x3F13,
		//
		FIGHT_UI_LAYER = 9,



		// 奖励面板
		REWARD_PANEL_LAYER = 11,



		//
		TAG_MAP_LAYER = 0x3F12,


		SHOP_CONTENT_LAYER = 9,
	};


	bool init();


	virtual void onEnter();
	virtual void onExit();



	// 用于暂停
	void specialPause(int _except_id = BaseDefine::INVALID_ID);
	// 恢复
	void specialResume();


	// 加入战斗场景
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




	// callback
	void handleBattleResEvent(int nRes);


	// 返回主场景回调
	void backGameMainCallback(Ref* sender)
	{
		Director::getInstance()->popScene();
	}



	CREATE_FUNC(BattleScene);

protected:


	// TouchEvent
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);


private:
	
	// shop
	Node* m_shop_layout;
	
	// map
	MapManager m_mapMgr;


};

