#pragma once
#include "../ai/GameEntity.h"


/*
* 僵尸类
*
*
*/


class Zombie : public GameEntity
{
public:
	Zombie(void);
	virtual ~Zombie(void);



	/*
	 * @desc 初始化僵尸数据
	 * @param _cid card id
	 * @return
	 *	
	 */
	virtual bool initCardId(int _tid) override;

	

	//
	virtual void onEnter();


	/*
	 * @desc 每帧调用
	 * @param delta 时间间隔
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

	// 反向移动或者特殊移动后，需要调整方向
	virtual void fixDir();



protected:


	//
	bool changeState( unsigned int mask, const Telegram& telegram );




	// 是否要换向
	virtual GameDefine::Dir flipDir(GameDefine::Dir _new_dir) override;



	// 闲置回调
	void idleCallback() {}


private:

	char m_szName[BaseDefine::COMMON_LENGTH];
	float m_think_intval;							// 思考间隔
};

