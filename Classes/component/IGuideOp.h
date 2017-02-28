#pragma once
#include "../GameDefine.h"


/*
 * 引导行为类
 * 由于引导可能有不能的行为，如只是显示引导层，有打开指定面板加引导层，
 *
 */




class IGuideOp
{
public:
	virtual ~IGuideOp(void) = 0;


	enum 
	{
		IGO_BASE_NONE,
		IGO_BASE_OP,							// 基本操作，只弹出遮罩层
		IGO_FIRST_GAME_ENTER,					// 第一次进入游戏
		IGO_REWARD_HERO,						// 送一个英雄
	};


	enum
	{
		GO_OWNER_LAYER = 990,								// 自己显示的层
	};


	enum
	{
		ID = IGO_BASE_NONE,
	};



	/*
	 * @desc 执行引导操作
	 * @param _root 当前引导的主场景节点
	 * @param _cfg_gi 当前引导的配置信息
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





