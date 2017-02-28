#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;




class StageArmySel : public Widget
{
public:
	StageArmySel(void);
	~StageArmySel(void);


	enum
	{
		BAG_ITEM_COL_MAX = 4,

		// ��ק��Ч��ֵ
		DRAG_ACT_LENGTH = 16,

		BASE_FE_TYPE = 100,
	};


	bool init();


	// ˢ��С������
	void updateArmyInfo();

	// ˢ��Ӣ������
	void updateHeroInfo();

	//
	void setCurStageId(int _stage_id)		{ m_stage_id = _stage_id;}


	CREATE_FUNC(StageArmySel);
protected:

	// ��ť����¼�
	void btnTouchEvent(Ref *pSender, Widget::TouchEventType type);

	// ѡ��Ӣ�۴����¼�
	void heroCardTouchEvent(Ref *pSender, Widget::TouchEventType type);

	// ѡ��С�������¼�
	void armyCardTouchEvent(Ref *pSender, Widget::TouchEventType type);

	// Ӣ��ѡ��ȡ�������¼�
	void heroCardCancelTouchEvent(Ref *pSender, Widget::TouchEventType type);

	// С��ѡ��ȡ���¼�
	void armyCardCancelTouchEvent(Ref *pSender, Widget::TouchEventType type);


	// ����С��
	void appendArmy(int _sel_index);


private:
	Layout* m_layout;
	int m_wx_type;
	int m_stage_id;
};

