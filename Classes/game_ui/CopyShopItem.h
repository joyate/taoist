#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameDefine.h"

USING_NS_CC;
using namespace ui;


/*
 * �����̵���Ʒ
 *
 */



class CopyShopItem : public Widget
{
public:
	CopyShopItem(void);
	~CopyShopItem(void);



	bool init();


	// ���̵���Ʒ���ʼ��
	bool initFromShopItemId(int _item_id);


	// ���ù���״̬
	void setBoughtState(bool _bought);
	
	// ������Ʒ�����Ǹ�������
	void setCopyId(int _copy_id)
	{
		m_copy_id = _copy_id;
	}
	// ������Ʒ�������������ù�������
	void setItemIndex(int _item_index)
	{
		m_item_index = _item_index;
	}




	// ��ʼ��ʾ������
	void onEnter();


	//
	CREATE_FUNC(CopyShopItem);
	
protected:

	void touchEvent(Ref *pSender, Widget::TouchEventType type);

private:

	int m_copy_id;					// ����id
	int m_item_index;				// ��Ʒ����
	Layout* m_layout;

};

