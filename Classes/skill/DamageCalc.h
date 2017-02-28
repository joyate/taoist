#include "../GameDefine.h"



class GameEntity;

// 基础伤害计算公式
class BaseDamageCalc
{
public:

	BaseDamageCalc(GameEntity* _src,GameEntity* _tar,int sk_id):
		m_src(_src),
		m_tar(_tar),
		m_sk_id(sk_id)
	{}


	//
	enum
	{
		SRC_SKILL_DMG_INDEX = 0,
	};

	// res容器索引
	enum
	{
		CRITICAL_INDEX,
		DAMAGE_INDEX,
		CALC_RES_MAX,
	};



	// 结算
	void doDamage();


protected:

	// 结算前处理
	virtual void preCalc(std::vector<float>& _res);

	// 结算中处理
	virtual void onCalc(std::vector<float>& _res);

	// 结算后处理
	virtual void postCalc(std::vector<float>& _res);


protected:

	GameEntity* m_src;
	GameEntity* m_tar;
	int m_sk_id;

};



class DeadlyDamageCalc : public BaseDamageCalc
{
public:
	DeadlyDamageCalc(GameEntity* _src,GameEntity* _tar,int sk_id):
		BaseDamageCalc(_src,_tar,sk_id)
	{

	}

protected:

	// 结算中处理
	virtual void onCalc(std::vector<float>& _res) override;

};




class CureCalc : public BaseDamageCalc
{
public:
	CureCalc(GameEntity* _src,GameEntity* _tar,int sk_id):
		BaseDamageCalc(_src,_tar,sk_id)
	{

	}


protected:
	
	//
	virtual void onCalc(std::vector<float>& _res) override;
};



class SelfMurderCalc : public BaseDamageCalc
{
public:
	SelfMurderCalc(GameEntity* _src,GameEntity* _tar,int sk_id):
		BaseDamageCalc(_src,_tar,sk_id)
	{

	}


	// 结算中处理
	virtual void onCalc(std::vector<float>& _res) override;

};

