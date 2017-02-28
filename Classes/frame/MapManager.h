#pragma once
#include "cocos2d.h"
#include "../GameDefine.h"
#include <map>

USING_NS_CC;



/*
 * 关于GameEntity对象的托管，目前所有的资源都是由MapManager管理，
 * 
 * 其他管理器也有相关引用，一定要注意，目前暂时不做资源上的retain
 * 后面看情况处理。
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
 * tmx 默认是以左下为基准的。
 * 
 * 
 * 游戏中所有的物件位置计算都以此为基准
 */


// 注意这个结构体，资源引用问题
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
		// 基础格子长度，地图设计的最小单位长度
		GRID_BASE_LEN = 48,

		// 多少个基础格子合成一个大格子
		GRID_FIXED_HEIGHT_NUM = 2,

		GRID_FIXED_WIDTH_NUM = 3,

		//
		GRID_WIDTH_LEN = GRID_BASE_LEN * GRID_FIXED_WIDTH_NUM,

		//
		GRID_HEIGHT_LEN = GRID_BASE_LEN * GRID_FIXED_HEIGHT_NUM,

		// 由于精灵的锚点位置，位置需要修正
		// 格子位置X位置偏移值
		OBJ_POS_OFFSET_GRID_X = (int)(GRID_WIDTH_LEN * 0.5f),

		// 格子位置Y方向偏移值
		OBJ_POS_OFFSET_GRID_Y = (int)(GRID_HEIGHT_LEN * 0.42f),


		// 格子位置Y方向 位置居中
		GRID_POS_OFFSET_Y = (int)(GRID_HEIGHT_LEN * 0.5f),

	};



	//
	enum
	{
		TAG_SELECT_GRID_LAYER = 10,

		// 背景特效TAG
		TAG_BACK_EFFECT_LAYER = 0x1F00,
		// 背景特效层级
		BACK_EFFECT_LAYER_LVL = 20,

		// 前景特效TAG
		TAG_FRONT_EFFECT_LAYER = 0x2F00,
		// 前景特效层级
		FRONT_EFFECT_LAYER_LVL = 720,
	};




	enum
	{
		// 波次提示索引
		TIP_ENEMY_BOUND_MSG_ID = 3,
	};



	// 操作类型
	enum OP_TYPE
	{
		OT_COMMON = 1,			// 通常
		OT_HERO_MOVE = 2,		// 英雄移动
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
	 * @desc 初始化地图数据
	 * @param _scene_id 战斗场景id
	 * @return map manager 节点指针
	 *	
	 */
	Node* init(int _stage_id);



	// 暂停，除了_id
	void specialPause(int _id = BaseDefine::INVALID_ID);
	// 恢复所有
	void specialResume();

	int getStageId() const			{ return m_stage_id;}

	// 增加敌人数目，由于动态增加的
	void increEnemyCnt()			{ m_enemys_cnt++;}

	/*
	 * @desc 获取指定点的对应地图格子
	 * @param
	 * @return
	 *	
	 */
	inline Rect getActiveRectFromVec2(const Vec2& _pos);

	

	/*
	 * @desc 获取地图上GameEntity的示例
	 * @param _id GameEntity的ID
	 * @return GameEntity
	 *	
	 */
	GameEntity* GetGameObject(int _id);
	

	/*
	 * @desc 根据pos的位置获取GameEntity
	 * @param pos 指定的位置
	 * @return 在该位置的GameEntity
	 *	
	 */
	GameEntity* GetGameObjectByPos(const Vec2& pos);



	/*
	 * @desc 判断2个y坐标是不是在同一行
	 * @param _lh_y 
	 * @param _rh_y
	 * @return 在同一行返回true,否则返回false
	 *	
	 */
	bool isInLine(float _lh_y,float _rh_y,bool bAdjustY)
	{
		float lh_val = bAdjustY ? (_lh_y - OBJ_POS_OFFSET_GRID_Y - m_bound_rect.origin.y) : (_lh_y - m_bound_rect.origin.y);
		return  ((int)(lh_val))/GRID_HEIGHT_LEN == ((int)(_rh_y - m_bound_rect.origin.y))/GRID_HEIGHT_LEN;
	}



	/*
	 * @desc 转换指定点到选择框
	 * @param _pos 指定点，在MapManager
	 * @param bCheck 检查是否占位
	 * @return
	 *	
	 */
	int getVec2Rect( const Vec2& _pos, bool bCheck = true);




	/*
	 * 逻辑处理
	 */
	void update(float delta);





	/*
	 * @desc 显示可选择格子
	 * @param
	 * @return
	 *	
	 */
	void ShowObjGrid(bool bShow = true);




	/*
	 * @desc 激活选择格子背景动画
	 * @param _pos 选择格子索引
	 * @return
	 *	
	 */
	bool activeSelectBg(int _pos);
	

	


	/*
	 * @desc 将_obj放入_pos处格子里
	 * @param _pos 格子索引
	 * @param _obj 处理的对象
	 * @return
	 *	
	 */
	bool putObjectInGrid(int _pos,Node* _obj);





	/*
	 * @desc _obj进入场景
	 * @param _obj 对象指针，一般是怪物。
	 * @return
	 *	
	 */
	void enterMap(Node* _obj);



	/*
	 * @desc 在nLayer给_owner绑定特效_effect
	 * @param _owner 特效绑定在谁上面
	 * @param _effect 绑定的特效
	 * @param nLayer 绑在特定层次
	 * @return
	 *	
	 */
	void attachEffect(GameEntity* _owner,Node* _effect,int nLayer);



	/*
	 * @desc _obj离开场景
	 * @param _obj 对象指针
	 * @return
	 *	
	 */
	void exitMap(GameEntity* _obj);


	// 偏移地图使用
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
	 * @desc 处理点击位置 @param _pos 的对象时间
	 * @param _pos 点击位置，原始坐标
	 * @return 该点击处的对象
	 *	
	 */
	GameEntity* onTouch(Vec2 _pos,int& _op);



	//////////////////////////////////////////////////////////////////////////
	// 效果
	//////////////////////////////////////////////////////////////////////////

	// 抖动效果
	void shakeAffect(float _dt,float offset_x,float offset_y);
	
	/*
	 * @desc 黑屏效果
	 * @param _dt
	 * @param opacity 透明度
	 * @param _owner 触发效果的对象
	 * @return
	 *	
	 */
	void screenTintAffect(float _dt,GLubyte opacity, GameEntity* _owner);




	//////////////////////////////////////////////////////////////////////////




	/*
	 * @desc 获取离_me最近的GameEntity
	 * @param _me 参考的GameEntity
	 * @param _out 
	 * @param _filter 选择过滤器
	 * @return
	 * @mark 最近是指同一道上的最近的
	 */
	int getLineNearestObjs(GameEntity* _me,std::vector<GameEntity*>* _out,const TargetSelectorFilter& _filter);




	/*
	 * @desc 获取离pos最近的GameEntity
	 * @param pos 指定的位置
	 * @param _out 结果集
	 * @param _filter 选择过滤器
	 * @return
	 *	
	 */
	int getPosNearestObjs(const Vec2& pos, std::vector<GameEntity*>* _out,const TargetSelectorFilter& _filter);


	/*
	 * @desc 获取Rect内的GameEntity
	 * @param _rect 选择矩形框
	 * @param _out 结果集
	 * @param _filter 选择过滤器
	 * @return
	 *	
	 */
	int getRectInObjs(const Rect& _rect, std::vector<GameEntity*>* _out,const TargetSelectorFilter& _filter);




	/*
	 * @desc 获取所有的召唤物
	 * @param
	 * @return
	 *	
	 */
	int getAllSummonObjs(GameEntity* _me,std::vector<GameEntity*>* _out,const TargetSelectorFilter& _filter);




	/*
	 * @desc 获取_rect中的objs
	 * @param _rect 指定的rect
	 * @param _out 获取的obj的ID
	 * @return 获取的个数
	 *	
	 */
	int getObjsInRect(const Rect& _rect,std::vector<int>& _out);



	// 获取英雄
	GameEntity* getHero();
	
	// 获取某一类型的对象有效个数
	int getActiveObjCount(int nObjType);

protected:


	// 解析地图数据
	bool _analyseMap();



	/*
	 * @desc 初始化怪物数据
	 * @return
	 *	
	 */
	bool _initEnemy();



	


	/*
	 * @desc 初始化英雄
	 * @return 初始化成功
	 *	
	 */
	bool _initHero();



	/*
	 * @desc 以48px为基准转换指定坐标为格子索引
	 * @param _pos 指定坐标
	 * @return
	 * @mark _pos点是以tmx layer内的坐标	
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
	 * @desc 修正怪物位置，到战斗场景相应位置
	 * @param 指定点，一般是配置点
	 * @return 
	 * @mark 为了使怪物与英雄在同一条线上，需要修正y坐标
	 */
	Vec2 _fixedMonsterPos(const Vec2& _pos);
	
	



	/*
	 * 提示回调
	 *
	 */
	void hintCallback( Node* sender );





private:

	// 战斗场景id
	int m_stage_id;


	// 流逝时间，用于控制怪物的波次
	float m_elapse_time;


	//
	EventListener* _custom_listener;


	/*experimental::*/TMXTiledMap* m_map_owner;

	/*
	 * 所有的可选择区域数据
	 * 
	 * 方案有几个：
	 * 1、记录所有可选择格子的中心点坐标
	 * 2、记录所有可选择格子的Rect,
	 * 
	 * 采用第二方案，原因有2个：
	 * 1、定位：第一个方案求最近距离点，方案二用区域包含
	 * 2、对支持不同基础格子数时，方案2要优于方案1
	 */
	std::vector<sttGridInfo> m_act_rect;
	
	// 触发器
	std::vector<GameDefine::tTriggerInfo> m_triggers;
	

	/*
	 * 有效格子区域
	 *  
	 * 该区域包含 摆放区 + 怪物区
	 */
	Rect m_bound_rect;


	/*
	 * @desc 选择的grid索引
	 * @param
	 * @return
	 *	
	 */
	int m_sel_grid_index;


	// 提示信息
	tHintInfo m_hints;
	// ---- 怪物数据 -----
	int m_enemys_cnt;
	std::map<int, std::vector<tEnemyObj> > m_enemys;


	std::vector<GameEntity*> m_vec_defenders;
	std::vector<GameEntity*> m_vec_monsters;
	std::vector<GameEntity*> m_vec_bullets;

	//
	GameEntity* m_hero;
};

