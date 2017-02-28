#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;



class SideItem : public Widget
{
public:
	SideItem(void);
	~SideItem(void);


	bool init();


	// �ӿ���ʵ��ID��ʼ�������UI
	bool initFromCardInstance(int _card_inst_id);


	// ʵ��id
	int getInstId() const	{ return m_inst_id;}
	// ��ȡobj id
	int getObjId() const	{ return cached_obj_id;}

	// ���ÿ����Ǽ�
	void setStarLvl(int _lvl);

	
	/*
	 * @desc ����С��������ʾ״̬�������벻����
	 * @param _cur_ghost ��ǰ��Ч��������
	 * @return
	 *	
	 */
	void updateGhostState(int _cur_ghost);


	//
	void hookHeadPicListener(Widget::ccWidgetTouchCallback _callback);
	void onEnterColddown();
	bool isColddown() const		{return m_bMaskRunning;}

	CREATE_FUNC(SideItem);

protected:

	//
	void touchEvent(Ref *pSender, Widget::TouchEventType type);



	// ��������ֵ
	void setGhost(int _ghost,const Color3B& _color);


	// ��ȴ��ɻص�
	void cdover();


	// ��������mask��Ĳ㼶��ϵ
	void adjustLocalOrder(int base_order);


private:
	int m_inst_id;				// ʵ��id
	int cached_obj_id;
	Layout* m_layout;
	ProgressTimer* m_mask;
	bool m_bMaskRunning;
};

