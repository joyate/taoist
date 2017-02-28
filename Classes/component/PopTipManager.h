#pragma once
#include "cocos2d.h"


USING_NS_CC;


/*
 * ������Ϣ��ʾ
 *
 * ���ڸ�����ʾ��������ʾ��
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

		// tip��Ʈ�ľ���
		POP_TIPS_MOVE_UP_SIZE = 50,
	};


	static PopTipManager* getInstance();
	

	/*
	 * @desc ������Ϣ��ʾ
	 * @param _tid ��Ϣid,��Ӧ��msg��id
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

