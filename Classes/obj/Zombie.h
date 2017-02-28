#pragma once
#include "../ai/GameEntity.h"


/*
* ��ʬ��
*
*
*/


class Zombie : public GameEntity
{
public:
	Zombie(void);
	virtual ~Zombie(void);



	/*
	 * @desc ��ʼ����ʬ����
	 * @param _cid card id
	 * @return
	 *	
	 */
	virtual bool initCardId(int _tid) override;

	

	//
	virtual void onEnter();


	/*
	 * @desc ÿ֡����
	 * @param delta ʱ����
	 * @return
	 *	
	 */
	virtual void update(float delta);


	//
	void run_tick(float df);
	virtual void idle_tick(float dt) override;

	//
	void clearThinkTime()	{ m_think_intval = 0.0f;}


	//
	virtual void runTo( const Vec2& _dest );


	//
	CREATE_FUNC(Zombie);

#ifdef _DEBUG
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
protected:
	void onDraw(const Mat4 &transform, uint32_t flags);
	CustomCommand _customCommand;
#endif


public:

	// �����ƶ����������ƶ�����Ҫ��������
	virtual void fixDir();



protected:


	//
	bool changeState( unsigned int mask, const Telegram& telegram );




	// �Ƿ�Ҫ����
	virtual GameDefine::Dir flipDir(GameDefine::Dir _new_dir) override;



	// ���ûص�
	void idleCallback() {}


private:

	char m_szName[BaseDefine::COMMON_LENGTH];
	float m_think_intval;							// ˼�����
};

