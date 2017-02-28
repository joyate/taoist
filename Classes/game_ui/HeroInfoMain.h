#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


/*
 *	Ӣ�۲鿴���������
 *
 */



class ObjInfoDetailPanel;

class HeroInfoMain : public Widget
{
public:
	HeroInfoMain();
	~HeroInfoMain();



	bool init();


	/*
	 * @desc ��ʵ��id��ʼ��
	 * @param _inst_id ����ʵ��id
	 * @return
	 *	
	 */
	void initWithInstId(int _inst_id);


	// ���õȼ�
	void setLevel(int _lvl);
	// ���þ���
	void setExp(unsigned int _exp);
	// ����ս����
	void setFight(int _ft);
	// ��������
	void setFeType(int _fe);
	// ���û�ʯ
	void setGhost(int _gh, int _gh_max);
	// ����ȫ����
	void setFullPic(const char* _path);


	CREATE_FUNC(HeroInfoMain);

protected:


	// ��ť����¼�
	void btnTouchEvent(Ref *pSender, Widget::TouchEventType type);
	
	
	// ͼƬ����¼�
	void imgTouchEvent(Ref *pSender, Widget::TouchEventType type);


	//
	void WidgetCallback( Node* sender );

private:
	Layout* m_layout;

	//
	ObjInfoDetailPanel* m_info_detail;
};

