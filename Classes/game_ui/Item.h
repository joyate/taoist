#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


/*
 * ��Ʒ���
 * 	
 */




class UIItem : public Widget
{
public:
	UIItem(void);
	~UIItem(void);


	bool init();


	/*
	 * @desc ����Ʒģ��id��ʼ��
	 * @param _item_temp_id ģ��id
	 * @param _item_cnt ����
	 * @return
	 *	
	 */
	bool initFromItemTempId(int _item_temp_id, int _item_cnt = 1);



	/*
	 * @desc ����Ʒʵ��id��ʼ��
	 * @param _item_id ��Ʒʵ��id
	 * @return
	 *	
	 */
	bool initFromItemId(int _item_id);



	// �����Ǽ�
	void setStarLvl(int _lvl);
	// ���ø���
	void setItemCnt(int _cnt);



	CREATE_FUNC(UIItem);

private:

	Layout* m_layout;
};

