#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

/*
 * 特效
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
		EFF_GE_FRONT = 1,									// 这个特效是要挂在目标身上的，前面
		EFF_GE_BACK = 2,									// 这个特效是要挂在目标身上的，后面

		EFF_GP_MID = 4,										// 中间位置
		EFF_GP_BTM = 8,										// 底层位置

		EFF_LAYER_BACK			= 0x1F00,					// 后特效层，在GameEntity层后面
		EFF_LAYER_FRONT			= 0x2F00,					// 前特效层



		PARAM_POS_BEGIN = 4,								// 比较起始位置
		PARAM_POS_LENGTH = 3,								// 比较长度

	};



	CREATE_FUNC(Effect);


	// 用于专属特效
	bool createEffect(GameEntity* _owner);

	// 用于独立特效
	bool createEffect(const char* szName);


	// 绑定特效到_tar, _tar与_owner可能同也可能不同
	bool attachGameObj(GameEntity* _tar,int nLayer);

	//
	bool attachGameObj(GameEntity* _tar,const std::string& frame_event);


	//
	void playEffect(const char* szName = nullptr,int loop = -1);

protected:


	// 动画回调
	void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);


private:
	Node* m_ani;
};

