#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


/*
 * 关卡描述与兵种选择
 * 
 * 其包括2个子面板
 *	
 */




class StageDescLayer : public LayerColor
{
public:
	StageDescLayer(void);
	~StageDescLayer(void);


	enum
	{
		//
		TAG_STAGE_DESC = 0x4F02,

		//
		TAG_STAGE_SEL = 0x4F03,

		//
		TAG_STAGE_BACK = 0x4f04,

		//
		TAG_STAGE_NEXT = 0x4f05,

	};


	enum
	{
		BUTTON_MARGIN = 30,
	};


	enum
	{
		SD_DIR_LEFT,
		SD_DIR_RIGHT,
	};



	//
	bool init();



	//
	bool initFromStageId(int _stage_id);


	//
	void updateButton();


	//
	CREATE_FUNC(StageDescLayer);
protected:

	// 点击事件
	void btnTouchEvent(Ref *pSender, Widget::TouchEventType type);

	//
	void scrollStageView(int _dir = SD_DIR_RIGHT);


private:
	int m_stage_id;
	int m_cur_page_index;
};

