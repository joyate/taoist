#pragma once
#include "cocos2d.h"
#include "../ai/GameEntity.h"
#include "../skill/SkillMgr.h"


/*
 * ��������
 *
 */


class Defender : public GameEntity
{
public:
	Defender(void);
	virtual ~Defender(void);


	/*
	 * @desc ��ʼ����ʬ����
	 * @param _cid card id
	 * @return
	 *	
	 */
	virtual bool initCardId(int _cid) override;


	// ����λ��rect����
	void setRectIndex(int _pos)			{ m_rect_index = _pos;}
	int getRectIndex() const			{ return m_rect_index;}




	// ������������Ϊ
	virtual void idle_tick(float dt) override;

	// �����߸���
	virtual void update(float delta) override;


	// ʹ���Լ����ؼ���
	void usePrivateSkill();
	

	// 
	CREATE_FUNC(Defender);
	
protected:



	//
	virtual bool changeState( unsigned int mask, const Telegram& telegram ) override;


	// �����ƶ�����Ҫ�������򣬳�����Ļ�ұ�
	virtual void fixDir() override;


	// �Ƿ�Ҫ����
	virtual GameDefine::Dir flipDir(GameDefine::Dir _new_dir) override;
	
	// ����rect������
	int m_rect_index;
	// ������һ�����ж�����ʱ��
	float m_arder_elapse_time; 
};

