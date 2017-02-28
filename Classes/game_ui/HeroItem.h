#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../GameDefine.h"


USING_NS_CC;
using namespace ui;



/*
 * Ӣ��ͷ�� 
 * 
 *
 */


class HeroItem : public Widget
{
public:
	HeroItem(void);
	~HeroItem(void);


	enum
	{
		HI_MASK_LVL		= 1,		// ��ʾ�ȼ�
		HI_MASK_CTRL	= 2,		// ��ʾͳ����
	};



	bool init();


	/*
	 * @desc �ӿ���id���ʼ��
	 * @param _card ����ģ����Ϣ
	 * @return
	 *	
	 */
	bool initFromCfgItemInfo(const GameDefine::cfg_Card* _card, int mask);



	/*
	 * @desc ��ʵ��id��ʼ��
	 * @param _inst_id ����ʵ��id
	 * @return
	 *	
	 */
	bool initFromInstId(int _inst_id, int mask = 0);




	void showStar(int _star_lvl,bool bShow = true);



	CREATE_FUNC(HeroItem);
protected:


	// ���ñ߿���ʽ
	void setFrameType(int _lvl);

private:
	Layout* m_layout;
};

