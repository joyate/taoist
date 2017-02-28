#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../data/GameData.h"


USING_NS_CC;
using namespace ui;





/*
 * Ӣ���������UI
 *
 */





class HeroInfoPanel	: public Widget
{
public:
	HeroInfoPanel(void);
	~HeroInfoPanel(void);



	bool init();


	/*
	 * @desc ��ʵ����id��ʼ�����
	 * @param _card_inst_id ��ʵ��id
	 * @return �Ƿ��ʼ�ɹ�
	 *	
	 */
	bool initFromInstCardInfo(const GameDefine::tItemInfo* _item_info);


	// �����Ǽ�
	void setStarLvl(int _lvl);
	// ���ñ߿�
	void setHeadFrame(int _lvl);
	// ��������
	void setFiveElement(int fe_type);


	CREATE_FUNC(HeroInfoPanel);

private:
	Layout* m_layout;
};

