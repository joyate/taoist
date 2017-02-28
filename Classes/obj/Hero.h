#pragma once
#include "cocos2d.h"
#include "Defender.h"
#include "../skill/SkillMgr.h"
#include "../ai/AIState.h"

class Hero : public Defender
{
public:
	Hero(void);
	virtual ~Hero(void);


	//////////////////////////////////////////////////////////////////////////
	// ͨ����Ϊ
	//////////////////////////////////////////////////////////////////////////

	virtual void update(float delta);


	//////////////////////////////////////////////////////////////////////////
	// ������Ϊ
	//////////////////////////////////////////////////////////////////////////
	
	// ����
	virtual void runTo( const Vec2& _dest );



	// ����
	virtual void onDead() override;


	// �Ƿ�������״̬
	virtual bool isWalking() override
	{
		if (_stateMechine)
		{
			return _stateMechine->isInState(*HeroRunState::getInstance());
		}
		return false;
	}


	
	/*
	 * @desc ��������
	 * @param _sk_info ������������
	 * @param _bCost �Ƿ��ֵ
	 * @return ���/��ֵ�ɹ� ����true
	 *	
	 */
	bool skillCost(const GameDefine::cfg_Skill_Info* _sk_info,bool _bCost = false);

	/*
	 * @desc ʹ�ü���
	 * @param _sk_id ����id��
	 * @param _sk_lvl ���ܵȼ�
	 * @return ��ǰʹ�õļ���
	 *	
	 */
	Skill* useSkill(int _sk_id,int _sk_lvl);


	// 
	CREATE_FUNC(Hero);

protected:


	// ��������
	void ghostUpdate(float delta);


	//
	virtual bool changeState( unsigned int mask, const Telegram& telegram ) override;


	// ���ûص�
	/*virtual */void idleCallback();


private:



};

