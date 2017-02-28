#pragma once
#include "cocos2d.h"
#include "../GameDefine.h"
#include "StateMachine.h"

#include "cocostudio/CocoStudio.h"
#include "../skill/SkillMgr.h"
#include "../skill/BuffMgr.h"


USING_NS_CC;
using namespace BaseDefine;
using namespace cocostudio;


// 消息类型，
enum eMessage
{
	M_NULL,
	M_IDLE			= 0x0001,	// 闲置
	M_RUN			= 0x0002,
	M_ATK			= 0x0004,
	M_BEATK			= 0x0008,
	M_DEAD			= 0x0010,
	M_ARDER			= 0x0020,	// 休闲
	M_REBORN		= 0x0040,	// 重生
	M_BORN			= 0x0080,	// 出现动画
};



class Telegram;

class GameEntity : public Node
{
public:
	GameEntity();
	virtual ~GameEntity()
	{
		if(m_char_root)
		{
			m_char_root->release();
			m_char_root = nullptr;
		}
	}


	friend class BaseDamageCalc;
	friend class DeadlyDamageCalc;
	friend class SelfMurderCalc;
	friend class AttrChange;



	// node type
	enum TAG_GAME_NODE_TYPE
	{
		TAG_GNT_BODY = 0x1F01,						// 身体，主体
		TAG_GNT_BODY_LAYER_LVL = 5,


		TAG_GNT_GROUND_EFFECT = 0x1F02,				// 地效
		TAG_GNT_GROUND_EFFECT_LVL = 1,


		TAG_GNT_SHADOW = 0x1F03,					// 影子
		TAG_GNT_SHADOW_LAYER_LVL = 2,

		TAG_GNT_BLOOD_BG = 0x1F04,
		TAG_GNT_BLOOD_FG = 0x1F05,					// 血条等
		TAG_GNT_HUD_LAYER_LVL = 9,

		TAG_GNT_TITLE = 0x1F06,						// 名称
		TAG_GNT_TITLE_LAYER_LVL = 9,


		TAG_GNT_BEATK_EFFECT = 0x1F07,				// 被击特效
		TAG_GNT_BEATK_EFFECT_LVL = 15,		


		TAG_GNT_BLOOD_FLY = 0x1F08,					// 飘字
		TAG_GNT_BLOOD_FLY_LAYER_LVL = 19,	

		TAG_GNT_MAX,
	};



	enum
	{
		ATTACK_Z_OFFSET = 15,
	};



	enum ObjectType
	{
		OT_NONE,

		// main type
		OT_DEFENDER		= 0x1000,
		OT_OFFENSIVE	= 0x2000,

		// sub type
		OT_SOLDIER		= 0x0001,
		OT_HERO			= 0x0002,
		OT_MONSTER		= 0x0004,
		OT_BULLET		= 0x0008,
		OT_SUMMONER		= 0x0010, // 召唤物

	};

	//
	int getMainType() const		{ return m_type & 0xf000; }
	int getSubType() const		{ return m_type & 0x0fff; }


	int getType() const			{ return m_type;}

	// 实例id， 依赖于MapManager
	int getID() const			{ return m_id;}
	void setID(int _id)			{ m_id = _id;}

	int getHp() const			{ return m_attr.m_hp;}
	int getHpMax() const		{ return m_attr.m_hp_max;}


	int getCardId() const	{ return m_attr.m_card_id;}
	int getObjId() const	{ return m_attr.m_obj_id;}

	//////////////////////////////////////////////////////////////////////////
	//    state model
	//////////////////////////////////////////////////////////////////////////
	virtual bool  HandleMessage(const Telegram& msg);

	//
	virtual bool changeState( unsigned int mask, const Telegram& telegram );


	// 回到上一个状态
	void revertPreState()
	{
		if (_stateMechine)
		{
			_stateMechine->RevertToPreviousState();
		}
	}


	//////////////////////////////////////////////////////////////////////////
	


	// 获得一个buff
	bool handleGotBuff(int _buff_id)
	{
		return m_buffMgr.handleGotBuff(_buff_id,this);
	}

	// buff 事件
	void onBuffEvent(unsigned int _em,GameEntity* _tar = nullptr)
	{
		m_buffMgr.onEvent(_em,_tar);
	}


	// 重生
	void OnReborth();



	//
	virtual void setAlpha(bool alpha)
	{

	}


	/*
	 * @desc 根据obj数据表初始化
	 * @param _cid card id
	 * @return 是否成功初始化
	 *	
	 */
	virtual bool initCardId(int _cid);


	// 获取该节点的包围盒
	virtual Rect getBoundingBox() const;

	// 是否活着
	bool isAlive() const { return m_attr.m_hp > 0;}

	// 减血
	void decreaseHp(int _hp);
	// 加血
	void increateHp(int _hp);

	// 减怒气
	void decreaseAnger(float _anger)	{ m_anger_val = (m_anger_val > _anger ? m_anger_val - _anger : 0); }
	float getAnger() const				{ return m_anger_val;}

	// 获取当前技能
	Skill* GetCurSkill()
	{
		return m_skillMgr.GetCurSkill();
	}
	void cleanSkill() { m_skillMgr.cleanSkill();}
	

	void setDest(Vec2 _dest)			{ m_dest = _dest; }
	const Vec2& getDest() const			{ return m_dest;}

	void setTarget(GameEntity* _tar)	{ m_target = _tar;}
	GameEntity* getTarget()				{ return m_target;}


	// 根据自己的位置重设z order
	void reOrder()
	{
		static Size winSize = Director::getInstance()->getWinSize();
		Vec2 obj_pos = getPosition();
		int _z_order = winSize.height - (int)obj_pos.y;
		this->setLocalZOrder(_z_order);
	}


	//////////////////////////////////////////////////////////////////////////
	// 动画相关
	//////////////////////////////////////////////////////////////////////////

	// 暂停支持
	void pause();
	// 回复
	void resume();

	//
	void setAttackSpeed(float _speed);


	/*
	 * @desc 播放动画
	 * @param _at 动画类型
	 * @param durationTo
	 * @param loop 是否循环播放
	 * @return
	 *	
	 */
	virtual void playAnim(AnimType _at,int durationTo = -1,  int loop = -1);
	void playAnim(const char* act_name,int durationTo = -1,  int loop = -1);

	// 停止动画
	virtual void stopAnim();


	// 消逝动画
	void playDeadFade(float _delay);

	// 绑定子动画，一般是特效什么的，绑定到m_char_root上
	void attachCharAnim(Node* _anim, int _lvl, int _tag);

	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// 移动相关
	//////////////////////////////////////////////////////////////////////////


	// 移动到某点
	virtual void runTo(const Vec2& _dest);
	// 调整下朝向
	virtual void fixDir() {};

	// 死亡
	virtual void onDead();
	// -------------------------------------
	


	//////////////////////////////////////////////////////////////////////////
	// 逻辑机制
	//////////////////////////////////////////////////////////////////////////

	
	// tick
	virtual void update(float delta);


	//virtual void onExit();


	virtual void idle_tick(float dt)	{}
	virtual void attack_tick(float dt)	{}



	// 死亡事件,在死亡动作播放完后触发
	virtual void onDeadEvent();


	
	virtual bool isWalking()	{ return false;}
	virtual bool isBorning()	{ return false;}
	//////////////////////////////////////////////////////////////////////////


	// -------- callback 相关 -----------

	// 血飘字回调
	void bloodFlyCallback(Node* sender);

	
	
protected:

	//
	int getDir()
	{
		float angle = _getAngle();
		float degree = angle / PI * 180.0;
		if(degree < 0) degree += 360.0;
		if(degree > 360.0) degree -= 360.0;

		GameDefine::Dir direction;

		if(degree > 90.0f && degree <= 270.0f)
			direction = GameDefine::DIR_L;
		else
			direction = GameDefine::DIR_R;

		return (int)direction;
	}



	void setDir(const Vec2& _dir)
	{
		m_dir = _dir;
	}


	virtual GameDefine::Dir flipDir(GameDefine::Dir _new_dir);
	
	


	// 
	float _getAngle()
	{
		float angle = atan2(m_dir.y, m_dir.x);
		return isnan(angle) ? 0 : angle;
	}



	// 动画帧回调
	void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
	// 动画回调
	void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
	


	// 转idle回调
	//virtual void idleCallback();


protected:
	int m_id;
	Vec2 m_dest;
	GameEntity* m_target;

	// 朝向
	Vec2 m_dir;
	GameDefine::Dir m_e_dir;


	int m_type;			// 类型
	int m_card_id;		// 卡牌ID

	// 攻速
	float m_atk_speed;
	// 怒气，自动主动技能释放的能量
	float m_anger_val;


	// --------- 属性相关 -----------

	GameDefine::stGameEntityAttr m_attr;
	// 用来对比用的
	GameDefine::stGameEntityAttr m_attr_copy;

	// -----------------------------

	// 技能管理器
	SkillMgr m_skillMgr;
	BuffMgr m_buffMgr;

	//--- 引擎相关 ----
protected:

	// 游戏物件的根节点
	Node* m_char_root;
	//EventListenerCustom* _custom_event;
	StateMachine<GameEntity> *_stateMechine;


};



