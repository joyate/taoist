#include "../GameDefine.h"



class GameEntity;

// �����˺����㹫ʽ
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

	// res��������
	enum
	{
		CRITICAL_INDEX,
		DAMAGE_INDEX,
		CALC_RES_MAX,
	};



	// ����
	void doDamage();


protected:

	// ����ǰ����
	virtual void preCalc(std::vector<float>& _res);

	// �����д���
	virtual void onCalc(std::vector<float>& _res);

	// �������
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

	// �����д���
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


	// �����д���
	virtual void onCalc(std::vector<float>& _res) override;

};

