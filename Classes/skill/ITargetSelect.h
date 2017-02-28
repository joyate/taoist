#pragma once
#include "../ai/GameEntity.h"
#include "../GameDefine.h"

/*
 *  Ŀ��ѡ���㷨
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
		TS_COMMON_SKILL,					// ��ͨ��������,���е�Ϊ�����׼�ļ���
		TS_SUMMON,							// �ҵ������Լ����ٻ���
		TS_SELF,							// ѡ���Լ�
		TS_RECT,							// ����ѡ��
		TS_BULLET,							// �ӵ�����ѡ��
	};


	enum
	{
		ID = TS_BASE,
	};


	/*
	 * @desc ����ѡ��Ŀ��ʵ��
	 * @param _obj �ο����󣬼����ͷ���
	 * @param _skill ������Ϣ
	 * @param _out ѡ���Ŀ����󼯺ϣ���Ϊnull
	 * @return ѡ��Ŀ�����
	 *	
	 */
	int handleSelect(GameEntity* _obj,Skill* _skill);


protected:

	/*
	 * @desc ִ��ʵ�ʵ�Ŀ��ѡ���㷨
	 * @param _obj �����ͷ���
	 * @param sk_id ����id
	 * @param _out ����ѡ���Ŀ�꼯��
	 * @return
	 *	
	 */
	virtual int handleTargetSelectFilter(GameEntity* _obj,Skill* _skill,std::vector<GameEntity*>* _out) = 0;

};





// ͨ�ù���Ŀ��ѡ��
class CommonSkillSelect : public ITargetSelect
{
public:
	~CommonSkillSelect() {}

	enum
	{
		// ����ѡ������ID
		ID = TS_COMMON_SKILL,

		// ts_vals ��������
		// ѡ��Χ
		TS_COMMON_SELECT_DIST_INDEX = 0,
	};


protected:

	virtual int handleTargetSelectFilter(GameEntity* _obj,Skill* _skill,std::vector<GameEntity*>* _out) override;
};



// �ٻ���Ŀ��ѡ��
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
	 * @desc ��ȡ����Ŀ��
	 * @param _obj ��ǰӦ�õĶ���
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
	 * @desc ��ȡ����Ŀ��
	 * @param _obj ��ǰӦ�õĶ���
	 * @return
	 *	
	 */
	virtual int handleTargetSelectFilter(GameEntity* _obj,Skill* _skill,std::vector<GameEntity*>* _out) override;
};



// ����ѡ��
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
	 * @desc ��ȡ����Ŀ��
	 * @param _obj ��ǰӦ�õĶ���
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
	 * @desc ��ȡ����Ŀ��
	 * @param _obj ��ǰӦ�õĶ���
	 * @return
	 *	
	 */
	virtual int handleTargetSelectFilter(GameEntity* _obj,Skill* _skill,std::vector<GameEntity*>* _out) override;

};