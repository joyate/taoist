#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ObjInfoDetailPanel.h"

USING_NS_CC;
using namespace ui;


/*
 * �������������ʾ��Ϣ������	
 */


class SkillUpItem : public Widget
{
public:
	SkillUpItem(void);
	~SkillUpItem(void);


	enum
	{
		SUI_SKILL_DESC_TAG = 0x0f01,
	};



	bool init();


	/*
	 * @desc �Ӽ���ID��ʼ��
	 * @param _sk_id ����id
	 * @param _sk_lvl ���ܵȼ�
	 * @return
	 *	
	 */
	bool initSkillId(int _sk_id,int _sk_lvl = 1);
	
	
	// ����һ�¸���壬��������skill tips
	void initRootPtr(ObjInfoDetailPanel* _root)
	{
		m_panel_root = _root;
	}


	// ���ü���ͼ��
	void setSkillIcon(const char* path);

	// ������������
	void setUpgradeCost(int _cost);

	// ���ü��ܵȼ�
	void setSkillLvl(int _lvl);

	// ���ü�������
	void setSkillName(const char* _sk_name);


	CREATE_FUNC(SkillUpItem);
protected:

	//
	void btnTouchEvent(Ref *pSender, Widget::TouchEventType type);


	// ��ʾ��������
	void showSkillDesc(Ref *pSender, Widget::TouchEventType type);

private:
	Layout* m_layout;
	int m_sk_id;
	ObjInfoDetailPanel* m_panel_root;
};

