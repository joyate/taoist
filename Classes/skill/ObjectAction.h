#pragma once
#include "cocos2d.h"


USING_NS_CC;


/*
 * ƮѪ
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
		RED_HP_SUB = 1,		// ��Ѫ
		GRN_HP_ADD = 2,		// ��Ѫ
	};


	/*
	 * @desc ��ʼ��
	 * @param _hp Ʈ������
	 * @return
	 *	
	 */
	void initialize(int _hp,int _type = RED_HP_SUB);


	
	// ��ʼƮ
	/* @param _owner ˭��Ʈ��
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

	// �����ص�
	void deadCallback(Node* sender);


	CREATE_FUNC(CorpseEffect);

private:
	GameEntity* m_owner;
	float m_delay;
};
