#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"



USING_NS_CC;
using namespace ui;


class LocalPlayer;


class UICopySelect : public Layer
{
public:
	UICopySelect(void);
	~UICopySelect(void);


	enum CS_PAGE_INDEX
	{
		CS_COPY = 1,
		CS_HERO,
		CS_SHOP,
	};


	// �̵�һЩ������Ϣ
	enum
	{
		CS_SHOP_ROW = 2,
		CS_SHOP_COL = 4,


		SHOP_ITEM_UPDATE_INTERVAL = 900,
	};


	// ���������ʶ
	enum
	{
		TAG_OWNER_LAYER = 0x3F01,
	};


	bool init();


	// ����ˢ��ʱ��
	virtual void update(float delta) override;




	// �������Ϣ��ʼ��������Ϣ
	bool applyCopyInfoWithRoleData(int _copy_id);




	CREATE_FUNC(UICopySelect);

protected:

	// image ����¼�
	void touchEvent(Ref *pSender, Widget::TouchEventType type);
	// hero�����¼�
	void btnTouchEvent(Ref *pSender, Widget::TouchEventType type);
	// �����¼�
	void buyTouchEvent(Ref *pSender, Widget::TouchEventType type);

	// ��ʼ������ѡ��UI
	bool initCopySelect(int _copy_id);
	// ��ʼ��Ӣ��ѡ��UI
	bool initHeroSelect(int _copy_id);
	// ��ʼ�������̵�
	bool initCopyShop(int _copy_id);


	// ����pageview
	void updatePageView(int _new_page_index);


	// ʱ��ˢ��
	void timeUpdate(float delta);


private:

	Layout* m_layout;
	CS_PAGE_INDEX m_cur_page_index;			// ��ǰ���ڵĹؿ�ҳ����
	int m_copy_id;

	// ʣ���ˢ��ʱ��
	float m_left_update_time;
};

