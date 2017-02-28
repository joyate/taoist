#pragma once
#include "cocos2d.h"


USING_NS_CC;



class SceneMain : public Scene
{
public:
	SceneMain(void);
	~SceneMain(void);


	// ��Դid
	enum
	{
		SCENE_ID = 1,
	};


	enum 
	{
		// tag
		TAG_MAP_LAYER = 0x0F0E,

		// ��ͼ��
		MAP_LAYER = 5,

		// ui tag
		TAG_UI_LAYER = 0x1F00,

		// ui ��
		UI_LAYER = 99,


		// pop menu layer
		TAG_POP_LAYER = 0x1FF1,


		// pop menu
		POP_MENU = 155,

		// 
		TAG_POP_MENU = 0x1FF2,


		// notice tag
		TAG_NOTICE_LAYER = 0x2F00,

		// ֪ͨ��
		NOTICE_LAYER = 199,
	};


	CREATE_FUNC(SceneMain);


protected:

	bool init();

	void onTouchesMoved(const std::vector<Touch*>& touches, Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);


private:


};

