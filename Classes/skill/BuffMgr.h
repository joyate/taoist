#pragma once
#include <vector>
#include "../GameDefine.h"


class GameEntity;

class BuffMgr
{
public:
	BuffMgr(GameEntity* _owner);
	~BuffMgr(void);

	typedef std::vector<GameDefine::tBuffData>::iterator buff_iter;



	//
	enum BuffEventMask
	{
		// 一般持续性buff,包括（永久buff,dot buff,）
		BEM_EVENT_TIME	= 0x00000001,	// 时间事件

		// 在宿主死亡时触发
		BEM_EVENT_DEAD  = 0x00000002,	// 死亡事件

		// 在宿主消逝时触发
		BEM_EVENT_FADE	= 0x00000004,	// 消逝事件

		// 在宿主杀死怪物时触发
		BEM_EVENT_KILL  = 0x00000008,	// 杀怪事件
	};



	/*
	 * @desc 处理获得buff
	 * @param _b_id buff id
	 * @param _tar 释放buff的GameEntity
	 * @return
	 *	
	 */
	bool handleGotBuff(int _b_id,GameEntity* _tar); 




	// buff mgr 更新
	void update(float _dt);


	/*
	* @desc 事件入口
	* @param _em 事件掩码
	* @param _tar 事件目标对象
	* @return
	*	
	*/
	void onEvent(unsigned int _em,GameEntity* _tar = nullptr);


protected:

	/*
	 * @desc 看本buff是不是可以加入已中buff里
	 * @param _b_id buff id
	 * @return 返回可以放入的索引，如果不能放入返回-1
	 *	
	 */
	int tryGotBuff(int _b_id);
	

private:
	GameEntity* m_owner;
	std::vector<GameDefine::tBuffData> m_buffs;
};

