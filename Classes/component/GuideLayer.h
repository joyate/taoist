#pragma once
#include "cocos2d.h"
#include "../GameDefine.h"

USING_NS_CC;


class GuideLayer : public Layer
{
public:
	GuideLayer(void);
	~GuideLayer(void);


	enum
	{
		TAG_GUIDE_NODE = 0x0E00,
		GUIDE_NODE_LAYER = 999,

		TAG_CLIP_NODE = 0x0E01,
		TAG_ANIM_NODE = 0x0E02,

		TAG_TIPS_NODE = 0x0E03,
	};

	enum GLResult
	{
		GLR_FAILED,
		GLR_CONTINUE,
		GLR_OVER,
	};


	enum
	{
		// tips ������Ļ���ؾ���
		TIPS_POS_PADDING_Y = 20,
		TIPS_POS_PADDING_X = 20,

		// tips ���ڶ���ƫ�����⣬���ƫ��ֵҪ��Щ
		TIPS_POS_OFFSET_Y = 150,
		TIPS_POS_OFFSET_X = 150,


		// guide�㲻͸����
		TIPS_OPACITY = 180,
	};


	//
	bool init();

	//
	bool initConfig(int _guide_id);


	/*
	 * @desc ִ����һ��
	 * @return ���û����һ�������Ǳ�guide_id��Ӧ����������
	 *	
	 */
	GLResult nextStep(int nEvent = 0);



	CREATE_FUNC(GuideLayer);
protected:


	// ����rect�������Ǹ���win����ϵ���ģ�����Ҫת����cocos����ϵ
	void fixedRect(Rect& _rect);


	// ������������
	void appendGuideTips(const GameDefine::tGuideMaskInfo& _gmi);

	//
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);



	/*
	 * @desc ����tips��λ�ã���ֹ�ܳ���Ļ��Ե
	 * @param _dir ����
	 * @return
	 *	
	 */
	void adjustTipsPos(char _dir);



	/*
	 * @desc ����tipsͼƬ��λ��
	 * @param _gmi ��������
	 * @return
	 *	
	 */
	void adjustTipsImgPos(const GameDefine::tGuideMaskInfo& _gmi);



private:
	Rect m_act_rect;
	int m_guide_id;
	int m_step;

};

