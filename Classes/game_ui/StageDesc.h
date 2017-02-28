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


	// ���������ʶ
	enum
	{
		TAG_OWNER_LAYER = 0x3F02,
		
		// ���ж�����ʾ�㼶
		TOP_IMG_BTN_LAYER = 6,

		// һ�������ʾ4��
		BAG_ITEM_COL_MAX = 4,

		// ���а�ť��׼
		WX_BASE_TAG = 100,


		// tip
		TAG_TIP_NODE = 0x3F03,

	};


	enum
	{
		ST_ARMY = 1,
		ST_HERO,
	};


	// ����
	enum 
	{
		SST_COPY_DESC,
		SST_ARMY_SELECT,
		SST_MAX,
	};



	bool init();


	// �Ӹ������ʼ��
	bool initFromStageId(int _copy_id);


	// ������Ʒ
	void updateItem(int army_type,int wx_type);

	// ˢ������Ѿ�ѡ���Ӣ�ۣ�С������
	// _sel_index ��ǰѡ���С������
	void updateSelectedItem(int _sel_index);


	//
	CREATE_FUNC(StageDesc);

protected:

	// ����¼�
	void btnTouchEvent(Ref *pSender, Widget::TouchEventType type);
	// 
	void imgTouchEvent(Ref *pSender, Widget::TouchEventType type);
	// ѡ��Ӣ�ۣ�С�������¼�
	void cardTouchEvent(Ref *pSender, Widget::TouchEventType type);
	// ѡ��ȡ�������¼�
	void cardSelCancelTouchEvent(Ref *pSender, Widget::TouchEventType type);

	//
	void selectedItemEvent(Ref* pSender, ListView::EventType type);


	// ��ʾ��ϸ��Ϣ
	void showDetailTip(Ref *pSender, Widget::TouchEventType type);


	// page view �¼�
	void pageViewEvent(Ref *pSender, PageView::EventType type);

private:
	Layout* m_layout;
	
	int m_cur_step;						// ��ǰ�ڼ���			

	int m_fe_type;						// ��������
	int m_army_type;					// ����ѡ�����ͣ�Ӣ��,С����
	int m_last_zorder;					// ���а�ť����
	std::string m_last_img_btn_name;
	std::string m_last_amry_type_name;	// ��������
};

