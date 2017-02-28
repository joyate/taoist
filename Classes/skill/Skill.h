#pragma once
#include "cocos2d.h"
#include "../data/GameData.h"

USING_NS_CC;

class GameEntity;

class Skill
{
public:
	Skill(int _id,int _lvl);
	~Skill(void);

	//
	int getID() const { return m_skill_id;}


	// 
	bool tick(GameEntity* _owner,float _dt);


	// 技能释放
	virtual bool beginSkill(GameEntity* _owner);

	/*
	 * @desc 触发特殊效果,如：抖动
	 * @param _target 目标
	 * @return
	 *	
	 */
	void touchAffect(int mask,GameEntity* _target = nullptr);



	void clear()
	{
		m_skill_id = 0;
		m_skill_lvl = 1;
		m_atk_eclapse_time = 0;
		m_tar_pos = Vec2::ZERO;
	}
	
	
	
	void setTargetPos(const Vec2& _pos)		{ m_tar_pos = _pos;}
	const Vec2& getTargetPos()				{ return m_tar_pos;}


	std::vector<int>& getTargetIds()		{ return m_ge_ids;}
	void pushTargetId(int _ge_id)			{ m_ge_ids.push_back(_ge_id);}

	void resetTargetIds()					{ m_ge_ids.clear();}


public:
	int m_skill_id;						// 技能id
	int m_skill_lvl;					// 技能等级

	float m_atk_eclapse_time;			// 攻击逝去的时间

	
	Vec2 m_tar_pos;						// 选择的位置
	std::vector<int> m_ge_ids;			// 被选择的GameEntity ID组
	
	
};

