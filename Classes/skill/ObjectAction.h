#pragma once
#include "cocos2d.h"


USING_NS_CC;


/*
 * 飘血
 *
 *
 */

class GameEntity;

class BloodFly : public Node
{
public:
	BloodFly(void);
	~BloodFly(void);


	enum
	{
		RED_HP_SUB = 1,		// 减血
		GRN_HP_ADD = 2,		// 加血
	};


	/*
	 * @desc 初始化
	 * @param _hp 飘多少字
	 * @return
	 *	
	 */
	void initialize(int _hp,int _type = RED_HP_SUB);


	
	// 开始飘
	/* @param _owner 谁将飘字
	 *
	 */
	void fly(GameEntity* _owner,bool bCritical = false);



	CREATE_FUNC(BloodFly);

private:
	Label* m_blood_label;
};




class CorpseEffect : public Node
{
public:
	CorpseEffect();


	void go(GameEntity* _owner);
	void setDelay(float _dl) { m_delay = _dl;}

	// 死亡回调
	void deadCallback(Node* sender);


	CREATE_FUNC(CorpseEffect);

private:
	GameEntity* m_owner;
	float m_delay;
};
