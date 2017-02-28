#pragma once
#include "../GameDefine.h"
#include <vector>


class GameEntity;


/*
 * �˺�����ģ��
 *
 */





class ISkillDamage
{
public:
	ISkillDamage(void);
	virtual ~ISkillDamage(void) = 0;


	enum
	{
		SD_BASE,
		// ͨ���˺�����
		SD_HARM_BASE,
		// ��������������
		SD_SKILL_FACTOR,
		// ��ʬ����ɱ����
		SD_HARM_DEADLY,
	};


	enum
	{
		ID = SD_BASE,
	};


	void init(GameDefine::cfg_Skill_Info& sk_info)
	{
		m_skill_id = sk_info.id;
		//std::memcpy(m_val,sk_info.dt_vals,sizeof(float)*GameDefine::GD_SKILL_DAMAGE_VAR_MAX);
	}


	/*
	 * @desc ִ�м��ܽ���
	 * @param
	 * @return
	 *	
	 */
	virtual void handleDamage(GameEntity* _obj,std::vector<GameEntity*>& res) = 0;


protected:
	int m_skill_id;
	//float m_val[GameDefine::GD_SKILL_DAMAGE_VAR_MAX];


	/*
	 * @desc ������������_obj�����ܻ���Ч
	 * @param _obj ��������
	 * @return
	 *	
	 */
	void appandHitEffect(GameEntity* _obj);

};





class BaseSkillDamage : public ISkillDamage
{
public:
	virtual ~BaseSkillDamage() {}


	enum
	{
		ID = SD_HARM_BASE,
	};


	//
	virtual void handleDamage(GameEntity* _obj,std::vector<GameEntity*>& res);

};




// �����˺�����ʬ���м���
class DeadlySkillDamage : public ISkillDamage
{
public:
	virtual ~DeadlySkillDamage() {}


	enum
	{
		ID = SD_HARM_DEADLY,
	};


	virtual void handleDamage(GameEntity* _obj,std::vector<GameEntity*>& res);
};

