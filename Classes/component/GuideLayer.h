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
		// tips 距离屏幕边沿距离
		TIPS_POS_PADDING_Y = 20,
		TIPS_POS_PADDING_X = 20,

		// tips 由于动画偏移问题，这个偏移值要大些
		TIPS_POS_OFFSET_Y = 150,
		TIPS_POS_OFFSET_X = 150,


		// guide层不透明度
		TIPS_OPACITY = 180,
	};


	//
	bool init();

	//
	bool initConfig(int _guide_id);


	/*
	 * @desc 执行下一步
	 * @return 如果没有下一步，就是本guide_id对应的引导结束
	 *	
	 */
	GLResult nextStep(int nEvent = 0);



	CREATE_FUNC(GuideLayer);
protected:


	// 由于rect的数据是根据win坐标系来的，所以要转换成cocos坐标系
	void fixedRect(Rect& _rect);


	// 增加引导描述
	void appendGuideTips(const GameDefine::tGuideMaskInfo& _gmi);

	//
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);



	/*
	 * @desc 调整tips的位置，防止跑出屏幕边缘
	 * @param _dir 方向
	 * @return
	 *	
	 */
	void adjustTipsPos(char _dir);



	/*
	 * @desc 调整tips图片的位置
	 * @param _gmi 引导数据
	 * @return
	 *	
	 */
	void adjustTipsImgPos(const GameDefine::tGuideMaskInfo& _gmi);



private:
	Rect m_act_rect;
	int m_guide_id;
	int m_step;

};

