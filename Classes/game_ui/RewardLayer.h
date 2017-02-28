#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


class RewardLayer : public LayerColor
{
public:
	RewardLayer(void);
	~RewardLayer(void);

	enum
	{
		BR_TRI_STAR_LB = 2,		// С�ڵ���2�˵�������
		BR_TWO_STAR_LB = 5,		// С�ڵ���5�˵��Ƕ���
	};


	enum
	{
		BR_STAR_NUM = 3,
	};


	//
	bool init();


	/*
	 * @desc ����ս�������ʼ��������� 
	 * @param _stage_id �ؿ�id
	 * @return
	 *	
	 */
	void initBattleResult(int _stage_id);


	// ����ս������Ǽ�
	int calculateBRStar(int _defender_dead_cnt);


	CREATE_FUNC(RewardLayer);

protected:

	// ���װ������
	void fillEquipReward();


	// ������ʾս����������Ǽ�
	void setBRStar();


	// ͼƬ�¼�
	void touchEvent(Ref *pSender, Widget::TouchEventType type);

private:
	Layout* m_layout;
	int m_br_star_cnt; // ս�������Ǽ�
};

