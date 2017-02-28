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


// ��Ϣ���ͣ�
enum eMessage
{
	M_NULL,
	M_IDLE			= 0x0001,	// ����
	M_RUN			= 0x0002,
	M_ATK			= 0x0004,
	M_BEATK			= 0x0008,
	M_DEAD			= 0x0010,
	M_ARDER			= 0x0020,	// ����
	M_REBORN		= 0x0040,	// ����
	M_BORN			= 0x0080,	// ���ֶ���
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
		TAG_GNT_BODY = 0x1F01,						// ���壬����
		TAG_GNT_BODY_LAYER_LVL = 5,


		TAG_GNT_GROUND_EFFECT = 0x1F02,				// ��Ч
		TAG_GNT_GROUND_EFFECT_LVL = 1,


		TAG_GNT_SHADOW = 0x1F03,					// Ӱ��
		TAG_GNT_SHADOW_LAYER_LVL = 2,

		TAG_GNT_BLOOD_BG = 0x1F04,
		TAG_GNT_BLOOD_FG = 0x1F05,					// Ѫ����
		TAG_GNT_HUD_LAYER_LVL = 9,

		TAG_GNT_TITLE = 0x1F06,						// ����
		TAG_GNT_TITLE_LAYER_LVL = 9,


		TAG_GNT_BEATK_EFFECT = 0x1F07,				// ������Ч
		TAG_GNT_BEATK_EFFECT_LVL = 15,		


		TAG_GNT_BLOOD_FLY = 0x1F08,					// Ʈ��
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
		OT_SUMMONER		= 0x0010, // �ٻ���

	};

	//
	int getMainType() const		{ return m_type & 0xf000; }
	int getSubType() const		{ return m_type & 0x0fff; }


	int getType() const			{ return m_type;}

	// ʵ��id�� ������MapManager
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


	// �ص���һ��״̬
	void revertPreState()
	{
		if (_stateMechine)
		{
			_stateMechine->RevertToPreviousState();
		}
	}


	//////////////////////////////////////////////////////////////////////////
	


	// ���һ��buff
	bool handleGotBuff(int _buff_id)
	{
		return m_buffMgr.handleGotBuff(_buff_id,this);
	}

	// buff �¼�
	void onBuffEvent(unsigned int _em,GameEntity* _tar = nullptr)
	{
		m_buffMgr.onEvent(_em,_tar);
	}


	// ����
	void OnReborth();



	//
	virtual void setAlpha(bool alpha)
	{

	}


	/*
	 * @desc ����obj���ݱ��ʼ��
	 * @param _cid card id
	 * @return �Ƿ�ɹ���ʼ��
	 *	
	 */
	virtual bool initCardId(int _cid);


	// ��ȡ�ýڵ�İ�Χ��
	virtual Rect getBoundingBox() const;

	// �Ƿ����
	bool isAlive() const { return m_attr.m_hp > 0;}

	// ��Ѫ
	void decreaseHp(int _hp);
	// ��Ѫ
	void increateHp(int _hp);

	// ��ŭ��
	void decreaseAnger(float _anger)	{ m_anger_val = (m_anger_val > _anger ? m_anger_val - _anger : 0); }
	float getAnger() const				{ return m_anger_val;}

	// ��ȡ��ǰ����
	Skill* GetCurSkill()
	{
		return m_skillMgr.GetCurSkill();
	}
	void cleanSkill() { m_skillMgr.cleanSkill();}
	

	void setDest(Vec2 _dest)			{ m_dest = _dest; }
	const Vec2& getDest() const			{ return m_dest;}

	void setTarget(GameEntity* _tar)	{ m_target = _tar;}
	GameEntity* getTarget()				{ return m_target;}


	// �����Լ���λ������z order
	void reOrder()
	{
		static Size winSize = Director::getInstance()->getWinSize();
		Vec2 obj_pos = getPosition();
		int _z_order = winSize.height - (int)obj_pos.y;
		this->setLocalZOrder(_z_order);
	}


	//////////////////////////////////////////////////////////////////////////
	// �������
	//////////////////////////////////////////////////////////////////////////

	// ��֧ͣ��
	void pause();
	// �ظ�
	void resume();

	//
	void setAttackSpeed(float _speed);


	/*
	 * @desc ���Ŷ���
	 * @param _at ��������
	 * @param durationTo
	 * @param loop �Ƿ�ѭ������
	 * @return
	 *	
	 */
	virtual void playAnim(AnimType _at,int durationTo = -1,  int loop = -1);
	void playAnim(const char* act_name,int durationTo = -1,  int loop = -1);

	// ֹͣ����
	virtual void stopAnim();


	// ���Ŷ���
	void playDeadFade(float _delay);

	// ���Ӷ�����һ������Чʲô�ģ��󶨵�m_char_root��
	void attachCharAnim(Node* _anim, int _lvl, int _tag);

	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// �ƶ����
	//////////////////////////////////////////////////////////////////////////


	// �ƶ���ĳ��
	virtual void runTo(const Vec2& _dest);
	// �����³���
	virtual void fixDir() {};

	// ����
	virtual void onDead();
	// -------------------------------------
	


	//////////////////////////////////////////////////////////////////////////
	// �߼�����
	//////////////////////////////////////////////////////////////////////////

	
	// tick
	virtual void update(float delta);


	//virtual void onExit();


	virtual void idle_tick(float dt)	{}
	virtual void attack_tick(float dt)	{}



	// �����¼�,����������������󴥷�
	virtual void onDeadEvent();


	
	virtual bool isWalking()	{ return false;}
	virtual bool isBorning()	{ return false;}
	//////////////////////////////////////////////////////////////////////////


	// -------- callback ��� -----------

	// ѪƮ�ֻص�
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



	// ����֡�ص�
	void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
	// �����ص�
	void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
	


	// תidle�ص�
	//virtual void idleCallback();


protected:
	int m_id;
	Vec2 m_dest;
	GameEntity* m_target;

	// ����
	Vec2 m_dir;
	GameDefine::Dir m_e_dir;


	int m_type;			// ����
	int m_card_id;		// ����ID

	// ����
	float m_atk_speed;
	// ŭ�����Զ����������ͷŵ�����
	float m_anger_val;


	// --------- ������� -----------

	GameDefine::stGameEntityAttr m_attr;
	// �����Ա��õ�
	GameDefine::stGameEntityAttr m_attr_copy;

	// -----------------------------

	// ���ܹ�����
	SkillMgr m_skillMgr;
	BuffMgr m_buffMgr;

	//--- ������� ----
protected:

	// ��Ϸ����ĸ��ڵ�
	Node* m_char_root;
	//EventListenerCustom* _custom_event;
	StateMachine<GameEntity> *_stateMechine;


};



