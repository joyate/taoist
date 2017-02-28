#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
using namespace ui;


/*
 * 游戏世界副本地图
 *
 *
 */




class GameWorldMap : public Layer
{
public:
	GameWorldMap(void);
	~GameWorldMap(void);



	enum
	{
		TAG_GAME_WORLD_MAP = 0x3f01,
	};



	bool init();


	//
	CREATE_FUNC(GameWorldMap);


protected:


	void touchEvent(Ref *pSender, Widget::TouchEventType type);

private:

	Layout* m_layout;

};

