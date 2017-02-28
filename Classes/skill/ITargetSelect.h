#pragma once
#include "../ai/GameEntity.h"
#include "../GameDefine.h"

/*
 *  目标选择算法
 * 
 * 
 *	
 */

class ITargetSelect
{
public:

	virtual ~ITargetSelect() = 0;


	enum
	{
		TS_BASE = 0,
		TS_COMMON_SKILL,					// 普通攻击技能,以行道为计算标准的技能
		TS_SUMMON,							// 找到所有自己的召唤物
		TS_SELF,							// 选择自己
		TS_RECT,							// 格子选择
		TS_BULLET,							// 子弹类型选择
	};


	enum
	{
		ID = TS_BASE,
	};


	/*
	 * @desc 技能选择目标实现
	 * @param _obj 参考对象，技能释放者
	 * @param _skill 技能信息
	 * @param _out 选择的目标对象集合，可为null
	 * @return 选择目标个数
	 *	
	 */
	int handleSelect(GameEntity* _obj,Skill* _skill);


protected:

	/*
	 * @desc 执行实际的目标选择算法
	 * @param _obj 技能释放者
	 * @param sk_id 技能id
	 * @param _out 返回选择的目标集合
	 * @return
	 *	
	 */
	virtual int handleTargetSelectFilter(GameEntity* _obj,Skill* _skill,std::vector<GameEntity*>* _out) = 0;

};





// 通用攻击目标选择
class CommonSkillSelect : public ITargetSelect
{
public:
	~CommonSkillSelect() {}

	enum
	{
		// 近程选择类型ID
		ID = TS_COMMON_SKILL,

		// ts_vals 参数解释
		// 选择范围
		TS_COMMON_SELECT_DIST_INDEX = 0,
	};


protected:

	virtual int handleTargetSelectFilter(GameEntity* _obj,Skill* _skill,std::vector<GameEntity*>* _out) override;
};



// 召唤物目标选择
class SummonTargetSelect : public ITargetSelect
{
public:
	~SummonTargetSelect() {}

	enum
	{
		ID = TS_SUMMON,
	};


protected:
	/*
	 * @desc 获取所有目标
	 * @param _obj 当前应用的对象
	 * @return
	 *	
	 */
	virtual int handleTargetSelectFilter(GameEntity* _obj,Skill* _skill,std::vector<GameEntity*>* _out) override;

};



class SelfTargetSelect : public ITargetSelect
{
public:
	~SelfTargetSelect() {}


	enum
	{
		ID = TS_SELF,
	};


	protected:
	/*
	 * @desc 获取所有目标
	 * @param _obj 当前应用的对象
	 * @return
	 *	
	 */
	virtual int handleTargetSelectFilter(GameEntity* _obj,Skill* _skill,std::vector<GameEntity*>* _out) override;
};



// 格子选择
class RectTargetSelect : public ITargetSelect
{
public:

	~RectTargetSelect() {}

	enum
	{
		ID = TS_RECT,

		//
		TS_RECT_SELECT_WIDTH_INDEX = 0,
		TS_RECT_SELECT_HEIGHT_INDEX = 1,
	};


protected:


	/*
	 * @desc 获取所有目标
	 * @param _obj 当前应用的对象
	 * @return
	 *	
	 */
	virtual int handleTargetSelectFilter(GameEntity* _obj,Skill* _skill,std::vector<GameEntity*>* _out) override;
};



class BulletTargetSelect : public ITargetSelect
{
public:
	virtual ~BulletTargetSelect() {}


	enum
	{
		ID = TS_BULLET,
	};


protected:


	/*
	 * @desc 获取所有目标
	 * @param _obj 当前应用的对象
	 * @return
	 *	
	 */
	virtual int handleTargetSelectFilter(GameEntity* _obj,Skill* _skill,std::vector<GameEntity*>* _out) override;

};