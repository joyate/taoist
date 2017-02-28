#pragma once
#include "cocos2d.h"


USING_NS_CC;


/*
 * 弹出信息提示
 *
 * 用于各种提示，错误提示等
 *	
 */





class PopTipManager
{
public:
	PopTipManager(void);
	~PopTipManager(void);

	enum
	{
		POP_TIPS_FONT_SIZE = 24,

		// tip上飘的距离
		POP_TIPS_MOVE_UP_SIZE = 50,
	};


	static PopTipManager* getInstance();
	

	/*
	 * @desc 跳出信息提示
	 * @param _tid 信息id,对应于msg表id
	 * @return
	 *	
	 */
	void popTips(int _tid);


protected:

	//
	void deadCallback( Node* sender );


private:
	static PopTipManager* s_ptMgr;
	Vector<Label*> m_tips;
};

