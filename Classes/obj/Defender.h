#pragma once
#include "cocos2d.h"
#include "../ai/GameEntity.h"
#include "../skill/SkillMgr.h"


/*
 * 防卫者类
 *
 */


class Defender : public GameEntity
{
public:
	Defender(void);
	virtual ~Defender(void);


	/*
	 * @desc 初始化僵尸数据
	 * @param _cid card id
	 * @return
	 *	
	 */
	virtual bool initCardId(int _cid) override;


	// 所在位置rect索引
	void setRectIndex(int _pos)			{ m_rect_index = _pos;}
	int getRectIndex() const			{ return m_rect_index;}




	// 防御者休闲行为
	virtual void idle_tick(float dt) override;

	// 防御者更新
	virtual void update(float delta) override;


	// 使用自己独特技能
	void usePrivateSkill();
	

	// 
	CREATE_FUNC(Defender);
	
protected:



	//
	virtual bool changeState( unsigned int mask, const Telegram& telegram ) override;


	// 由于移动后，需要调整朝向，朝向屏幕右边
	virtual void fixDir() override;


	// 是否要换向
	virtual GameDefine::Dir flipDir(GameDefine::Dir _new_dir) override;
	
	// 所在rect的索引
	int m_rect_index;
	// 距离上一次休闲动作的时间
	float m_arder_elapse_time; 
};

