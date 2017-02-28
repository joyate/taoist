#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../GameDefine.h"

USING_NS_CC;
using namespace ui;


/*
 * ��Ϸ������ϸ��Ϣ���
 * 
 */



class ObjInfoDetailPanel : public Widget
{
public:
	ObjInfoDetailPanel(void);
	~ObjInfoDetailPanel(void);

	// skill tips tag
	enum
	{
		SUI_SKILL_DESC_TAG = 0x0f01,
	};

	enum
	{
		ODP_VIEW_ATTR,
		ODP_VIEW_SKILL,
		ODP_VIEW_WHERE,
	};


	bool init();
	
	/*
	 * @desc �Ӷ���id��ʼ����
	 * @param _id ����id��Ŀǰ��ģ��id
	 * @return
	 *	Ŀǰ��û��ʵ�����ݣ��������
	 */
	bool initFromInstId(int _inst_id);


	//
	void showSkillTips(int _sk_id,const Vec2& _pos);


	CREATE_FUNC(ObjInfoDetailPanel);
protected:

	// ��������
	void initBaseAttr(GameDefine::tCardInfo* _inst_card,GameDefine::cfg_Card* _cfg_card);
	// �������
	void initSkill(GameDefine::tCardInfo* _inst_card,GameDefine::cfg_Card* _cfg_card);
	// ������
	void initWhere(GameDefine::tCardInfo* _inst_card,GameDefine::cfg_Card* _cfg_card);

	// �л���ͼ
	void updateSubView(int _vi);
	

	// ͼƬ����¼�
	void imgTouchEvent(Ref *pSender, Widget::TouchEventType type);

private:
	Layout* m_layout;
	int m_cur_view_index;
	int m_inst_id;
};

