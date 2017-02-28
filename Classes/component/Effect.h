#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

/*
 * ��Ч
 * 
 */

class GameEntity;

class Effect : public Node
{
public:
	Effect(void);
	~Effect(void);


	enum
	{
		EFF_GE_FRONT = 1,									// �����Ч��Ҫ����Ŀ�����ϵģ�ǰ��
		EFF_GE_BACK = 2,									// �����Ч��Ҫ����Ŀ�����ϵģ�����

		EFF_GP_MID = 4,										// �м�λ��
		EFF_GP_BTM = 8,										// �ײ�λ��

		EFF_LAYER_BACK			= 0x1F00,					// ����Ч�㣬��GameEntity�����
		EFF_LAYER_FRONT			= 0x2F00,					// ǰ��Ч��



		PARAM_POS_BEGIN = 4,								// �Ƚ���ʼλ��
		PARAM_POS_LENGTH = 3,								// �Ƚϳ���

	};



	CREATE_FUNC(Effect);


	// ����ר����Ч
	bool createEffect(GameEntity* _owner);

	// ���ڶ�����Ч
	bool createEffect(const char* szName);


	// ����Ч��_tar, _tar��_owner����ͬҲ���ܲ�ͬ
	bool attachGameObj(GameEntity* _tar,int nLayer);

	//
	bool attachGameObj(GameEntity* _tar,const std::string& frame_event);


	//
	void playEffect(const char* szName = nullptr,int loop = -1);

protected:


	// �����ص�
	void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);


private:
	Node* m_ani;
};

