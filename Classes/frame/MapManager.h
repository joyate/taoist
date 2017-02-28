#pragma once
#include "cocos2d.h"
#include "../GameDefine.h"
#include <map>

USING_NS_CC;



/*
 * ����GameEntity������йܣ�Ŀǰ���е���Դ������MapManager����
 * 
 * ����������Ҳ��������ã�һ��Ҫע�⣬Ŀǰ��ʱ������Դ�ϵ�retain
 * ���濴�������
 */


using namespace GameDefine;


struct stGridIdx 
{
	int x;
	int y;

	stGridIdx()
	{
		x = 0;
		y = 0;
	}

	bool operator == (const stGridIdx _rh)
	{
		return x == _rh.x && y == _rh.y;
	}
};


/*
 * tmx Ĭ����������Ϊ��׼�ġ�
 * 
 * 
 * ��Ϸ�����е����λ�ü��㶼�Դ�Ϊ��׼
 */


// ע������ṹ�壬��Դ��������
struct sttGridInfo
{
	enum
	{
		E_GRID_ACTIVE,
		E_GRID_OBSTACLE,
	};


	Rect _rect;
	int _grid_type;
	Sprite* _sel_bg;
	int _obj_id;


	sttGridInfo()
	{
		_grid_type = E_GRID_ACTIVE;
		_sel_bg = nullptr;
		_obj_id = 0;
	}


	sttGridInfo(const sttGridInfo& _rh):
		_rect(_rh._rect),
		_grid_type(_rh._grid_type),
		_sel_bg(_rh._sel_bg),
		_obj_id(_rh._obj_id)
	{
		
	}


	sttGridInfo& operator = (const sttGridInfo& _rh)
	{
		_rect = _rh._rect;
		_grid_type = _rh._grid_type;
		_sel_bg = _rh._sel_bg;
		_obj_id = _rh._obj_id;

		return *this;
	}



	void clear()
	{
		_rect = Rect::ZERO;
		_grid_type = E_GRID_ACTIVE;
		_sel_bg = nullptr;
		_obj_id = 0;	
	}

};


class GameEntity;

class MapManager
{
public:
	MapManager(void);
	~MapManager(void);


	typedef std::vector<sttGridInfo>::iterator rect_iter;
	typedef std::vector<GameEntity*>::iterator obj_iter;
	typedef std::vector<GameDefine::tTriggerInfo>::iterator trig_iter;

	typedef std::map<int, std::vector<tEnemyObj> >::iterator enemy_iter;

	enum
	{
		// �������ӳ��ȣ���ͼ��Ƶ���С��λ����
		GRID_BASE_LEN = 48,

		// ���ٸ��������Ӻϳ�һ�������
		GRID_FIXED_HEIGHT_NUM = 2,

		GRID_FIXED_WIDTH_NUM = 3,

		//
		GRID_WIDTH_LEN = GRID_BASE_LEN * GRID_FIXED_WIDTH_NUM,

		//
		GRID_HEIGHT_LEN = GRID_BASE_LEN * GRID_FIXED_HEIGHT_NUM,

		// ���ھ����ê��λ�ã�λ����Ҫ����
		// ����λ��Xλ��ƫ��ֵ
		OBJ_POS_OFFSET_GRID_X = (int)(GRID_WIDTH_LEN * 0.5f),

		// ����λ��Y����ƫ��ֵ
		OBJ_POS_OFFSET_GRID_Y = (int)(GRID_HEIGHT_LEN * 0.42f),


		// ����λ��Y���� λ�þ���
		GRID_POS_OFFSET_Y = (int)(GRID_HEIGHT_LEN * 0.5f),

	};



	//
	enum
	{
		TAG_SELECT_GRID_LAYER = 10,

		// ������ЧTAG
		TAG_BACK_EFFECT_LAYER = 0x1F00,
		// ������Ч�㼶
		BACK_EFFECT_LAYER_LVL = 20,

		// ǰ����ЧTAG
		TAG_FRONT_EFFECT_LAYER = 0x2F00,
		// ǰ����Ч�㼶
		FRONT_EFFECT_LAYER_LVL = 720,
	};




	enum
	{
		// ������ʾ����
		TIP_ENEMY_BOUND_MSG_ID = 3,
	};



	// ��������
	enum OP_TYPE
	{
		OT_COMMON = 1,			// ͨ��
		OT_HERO_MOVE = 2,		// Ӣ���ƶ�
	};




#ifndef OBJ_FIXED_POS				
#define OBJ_FIXED_POS(_VEC2_)						\
		do {										\
			(_VEC2_).x += OBJ_POS_OFFSET_GRID_X;	\
			(_VEC2_).y += OBJ_POS_OFFSET_GRID_Y;	\
		}while(0)
#endif



#ifndef OBJ_FIXED_POS_Y				
#define OBJ_FIXED_POS_Y(_VEC2_)		(_VEC2_).y += OBJ_POS_OFFSET_GRID_Y
#endif


#ifndef GRID_FIXED_POS				
#define GRID_FIXED_POS(_VEC2_)				\
	do {									\
	(_VEC2_).x += OBJ_POS_OFFSET_GRID_X;	\
	(_VEC2_).y += GRID_POS_OFFSET_Y;		\
	}while(0)
#endif



	/*
	 * @desc ��ʼ����ͼ����
	 * @param _scene_id ս������id
	 * @return map manager �ڵ�ָ��
	 *	
	 */
	Node* init(int _stage_id);



	// ��ͣ������_id
	void specialPause(int _id = BaseDefine::INVALID_ID);
	// �ָ�����
	void specialResume();

	int getStageId() const			{ return m_stage_id;}

	// ���ӵ�����Ŀ�����ڶ�̬���ӵ�
	void increEnemyCnt()			{ m_enemys_cnt++;}

	/*
	 * @desc ��ȡָ����Ķ�Ӧ��ͼ����
	 * @param
	 * @return
	 *	
	 */
	inline Rect getActiveRectFromVec2(const Vec2& _pos);

	

	/*
	 * @desc ��ȡ��ͼ��GameEntity��ʾ��
	 * @param _id GameEntity��ID
	 * @return GameEntity
	 *	
	 */
	GameEntity* GetGameObject(int _id);
	

	/*
	 * @desc ����pos��λ�û�ȡGameEntity
	 * @param pos ָ����λ��
	 * @return �ڸ�λ�õ�GameEntity
	 *	
	 */
	GameEntity* GetGameObjectByPos(const Vec2& pos);



	/*
	 * @desc �ж�2��y�����ǲ�����ͬһ��
	 * @param _lh_y 
	 * @param _rh_y
	 * @return ��ͬһ�з���true,���򷵻�false
	 *	
	 */
	bool isInLine(float _lh_y,float _rh_y,bool bAdjustY)
	{
		float lh_val = bAdjustY ? (_lh_y - OBJ_POS_OFFSET_GRID_Y - m_bound_rect.origin.y) : (_lh_y - m_bound_rect.origin.y);
		return  ((int)(lh_val))/GRID_HEIGHT_LEN == ((int)(_rh_y - m_bound_rect.origin.y))/GRID_HEIGHT_LEN;
	}



	/*
	 * @desc ת��ָ���㵽ѡ���
	 * @param _pos ָ���㣬��MapManager
	 * @param bCheck ����Ƿ�ռλ
	 * @return
	 *	
	 */
	int getVec2Rect( const Vec2& _pos, bool bCheck = true);




	/*
	 * �߼�����
	 */
	void update(float delta);





	/*
	 * @desc ��ʾ��ѡ�����
	 * @param
	 * @return
	 *	
	 */
	void ShowObjGrid(bool bShow = true);




	/*
	 * @desc ����ѡ����ӱ�������
	 * @param _pos ѡ���������
	 * @return
	 *	
	 */
	bool activeSelectBg(int _pos);
	

	


	/*
	 * @desc ��_obj����_pos��������
	 * @param _pos ��������
	 * @param _obj ����Ķ���
	 * @return
	 *	
	 */
	bool putObjectInGrid(int _pos,Node* _obj);





	/*
	 * @desc _obj���볡��
	 * @param _obj ����ָ�룬һ���ǹ��
	 * @return
	 *	
	 */
	void enterMap(Node* _obj);



	/*
	 * @desc ��nLayer��_owner����Ч_effect
	 * @param _owner ��Ч����˭����
	 * @param _effect �󶨵���Ч
	 * @param nLayer �����ض����
	 * @return
	 *	
	 */
	void attachEffect(GameEntity* _owner,Node* _effect,int nLayer);



	/*
	 * @desc _obj�뿪����
	 * @param _obj ����ָ��
	 * @return
	 *	
	 */
	void exitMap(GameEntity* _obj);


	// ƫ�Ƶ�ͼʹ��
	void setPosition(const Vec2& _pos)
	{
		if (m_map_owner)
		{
			m_map_owner->setPosition(_pos);
		}
	}
	const Vec2& getPosition() const
	{
		if (m_map_owner)
		{
			return m_map_owner->getPosition();
		}

		return Vec2::ZERO;
	}
	const Rect getBoundingBox() const
	{
		if (m_map_owner)
		{
			return m_map_owner->getBoundingBox();
		}

		return Rect::ZERO;
	}



	/*
	 * @desc ������λ�� @param _pos �Ķ���ʱ��
	 * @param _pos ���λ�ã�ԭʼ����
	 * @return �õ�����Ķ���
	 *	
	 */
	GameEntity* onTouch(Vec2 _pos,int& _op);



	//////////////////////////////////////////////////////////////////////////
	// Ч��
	//////////////////////////////////////////////////////////////////////////

	// ����Ч��
	void shakeAffect(float _dt,float offset_x,float offset_y);
	
	/*
	 * @desc ����Ч��
	 * @param _dt
	 * @param opacity ͸����
	 * @param _owner ����Ч���Ķ���
	 * @return
	 *	
	 */
	void screenTintAffect(float _dt,GLubyte opacity, GameEntity* _owner);




	//////////////////////////////////////////////////////////////////////////




	/*
	 * @desc ��ȡ��_me�����GameEntity
	 * @param _me �ο���GameEntity
	 * @param _out 
	 * @param _filter ѡ�������
	 * @return
	 * @mark �����ָͬһ���ϵ������
	 */
	int getLineNearestObjs(GameEntity* _me,std::vector<GameEntity*>* _out,const TargetSelectorFilter& _filter);




	/*
	 * @desc ��ȡ��pos�����GameEntity
	 * @param pos ָ����λ��
	 * @param _out �����
	 * @param _filter ѡ�������
	 * @return
	 *	
	 */
	int getPosNearestObjs(const Vec2& pos, std::vector<GameEntity*>* _out,const TargetSelectorFilter& _filter);


	/*
	 * @desc ��ȡRect�ڵ�GameEntity
	 * @param _rect ѡ����ο�
	 * @param _out �����
	 * @param _filter ѡ�������
	 * @return
	 *	
	 */
	int getRectInObjs(const Rect& _rect, std::vector<GameEntity*>* _out,const TargetSelectorFilter& _filter);




	/*
	 * @desc ��ȡ���е��ٻ���
	 * @param
	 * @return
	 *	
	 */
	int getAllSummonObjs(GameEntity* _me,std::vector<GameEntity*>* _out,const TargetSelectorFilter& _filter);




	/*
	 * @desc ��ȡ_rect�е�objs
	 * @param _rect ָ����rect
	 * @param _out ��ȡ��obj��ID
	 * @return ��ȡ�ĸ���
	 *	
	 */
	int getObjsInRect(const Rect& _rect,std::vector<int>& _out);



	// ��ȡӢ��
	GameEntity* getHero();
	
	// ��ȡĳһ���͵Ķ�����Ч����
	int getActiveObjCount(int nObjType);

protected:


	// ������ͼ����
	bool _analyseMap();



	/*
	 * @desc ��ʼ����������
	 * @return
	 *	
	 */
	bool _initEnemy();



	


	/*
	 * @desc ��ʼ��Ӣ��
	 * @return ��ʼ���ɹ�
	 *	
	 */
	bool _initHero();



	/*
	 * @desc ��48pxΪ��׼ת��ָ������Ϊ��������
	 * @param _pos ָ������
	 * @return
	 * @mark _pos������tmx layer�ڵ�����	
	 */
	stGridIdx _transVec2RectIndex(const Vec2 _pos)
	{
		stGridIdx gi;

		Size map_size = m_map_owner->getContentSize();
		if (_pos.x > map_size.width || _pos.y > map_size.height)
		{
			CCLOG("pos invalid");
			return gi;
		}

		// 
		gi.x = (int)(_pos.x / GRID_BASE_LEN);
		gi.y = (int)(_pos.y / GRID_BASE_LEN);


		return gi;
	}



	/*
	 * @desc ��������λ�ã���ս��������Ӧλ��
	 * @param ָ���㣬һ�������õ�
	 * @return 
	 * @mark Ϊ��ʹ������Ӣ����ͬһ�����ϣ���Ҫ����y����
	 */
	Vec2 _fixedMonsterPos(const Vec2& _pos);
	
	



	/*
	 * ��ʾ�ص�
	 *
	 */
	void hintCallback( Node* sender );





private:

	// ս������id
	int m_stage_id;


	// ����ʱ�䣬���ڿ��ƹ���Ĳ���
	float m_elapse_time;


	//
	EventListener* _custom_listener;


	/*experimental::*/TMXTiledMap* m_map_owner;

	/*
	 * ���еĿ�ѡ����������
	 * 
	 * �����м�����
	 * 1����¼���п�ѡ����ӵ����ĵ�����
	 * 2����¼���п�ѡ����ӵ�Rect,
	 * 
	 * ���õڶ�������ԭ����2����
	 * 1����λ����һ���������������㣬���������������
	 * 2����֧�ֲ�ͬ����������ʱ������2Ҫ���ڷ���1
	 */
	std::vector<sttGridInfo> m_act_rect;
	
	// ������
	std::vector<GameDefine::tTriggerInfo> m_triggers;
	

	/*
	 * ��Ч��������
	 *  
	 * ��������� �ڷ��� + ������
	 */
	Rect m_bound_rect;


	/*
	 * @desc ѡ���grid����
	 * @param
	 * @return
	 *	
	 */
	int m_sel_grid_index;


	// ��ʾ��Ϣ
	tHintInfo m_hints;
	// ---- �������� -----
	int m_enemys_cnt;
	std::map<int, std::vector<tEnemyObj> > m_enemys;


	std::vector<GameEntity*> m_vec_defenders;
	std::vector<GameEntity*> m_vec_monsters;
	std::vector<GameEntity*> m_vec_bullets;

	//
	GameEntity* m_hero;
};

