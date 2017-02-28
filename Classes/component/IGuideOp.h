#pragma once
#include "../GameDefine.h"


/*
 * ������Ϊ��
 * �������������в��ܵ���Ϊ����ֻ����ʾ�����㣬�д�ָ�����������㣬
 *
 */




class IGuideOp
{
public:
	virtual ~IGuideOp(void) = 0;


	enum 
	{
		IGO_BASE_NONE,
		IGO_BASE_OP,							// ����������ֻ�������ֲ�
		IGO_FIRST_GAME_ENTER,					// ��һ�ν�����Ϸ
		IGO_REWARD_HERO,						// ��һ��Ӣ��
	};


	enum
	{
		GO_OWNER_LAYER = 990,								// �Լ���ʾ�Ĳ�
	};


	enum
	{
		ID = IGO_BASE_NONE,
	};



	/*
	 * @desc ִ����������
	 * @param _root ��ǰ�������������ڵ�
	 * @param _cfg_gi ��ǰ������������Ϣ
	 * @return
	 *	
	 */
	virtual void onExec(const GameDefine::cfg_Guide_Info& _cfg_gi) = 0;

};



class GuideOpBase : public IGuideOp
{
public:
	virtual ~GuideOpBase() {}


	enum
	{
		ID = IGO_BASE_OP,
	};


	//
	virtual void onExec(const GameDefine::cfg_Guide_Info& _cfg_gi) override;

};





