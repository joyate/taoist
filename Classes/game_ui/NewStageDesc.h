#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;



/*
 * 新的关卡描述面板 
 *
 *
 */




class NewStageDesc : public Widget
{
public:
	NewStageDesc(void);
	~NewStageDesc(void);


	enum
	{
		// tip
		TAG_TIP_NODE = 0x4F01,


		// 
		TAG_STAGE_DESC = 0x4F02,

		//
		TAG_STAGE_SEL = 0x4F03,

	};


	bool init();


	bool initFromStageId(int _stage_id);



	CREATE_FUNC(NewStageDesc);
protected:


	// 显示详细信息
	void showDetailTip(Ref *pSender, Widget::TouchEventType type);

private:
	Layout* m_layout;
	int m_stage_id;
};

