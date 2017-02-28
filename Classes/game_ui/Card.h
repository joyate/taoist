#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


/*
 * ������Ϣ
 *
 *
 */





class UICard : public Widget
{
public:
	UICard(void);
	~UICard(void);


	// ���ȼ�����ɫ
	enum
	{
		CARD_COLOR_WHITE = 1,
		CARD_COLOR_GREEN = 2,
		CARD_COLOR_BLUE = 3,
		CARD_COLOR_PURPLE = 4,
		CARD_COLOR_ORANGE = 5,
	};


	bool init();


	// ���ʵ������
	void onEnter();

	CREATE_FUNC(UICard);

protected:

	// �����Ǽ�
	void setStarLvl(int _star_lvl);

	// ���ÿ��ȼ����׿����̿����������Ͽ����ȿ���
	void setCardLvl(int _card_lvl);

	// ���ÿ�������
	void setCardImage(const char* sz_file_name);

	// ���û�������
	void setCardGhostReq(int _val);

	// ������������
	//void setCardPrestigeReq(int _val);


private:

	Layout* m_layout;
};

