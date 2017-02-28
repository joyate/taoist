#pragma once
#include "BaseDefine.h"
#include "cocos2d.h"
#include <string>
#include "utility/TaoIStream.h"
#include "utility/TaoOStream.h"

USING_NS_CC;


namespace GameDefine
{

	// 实例id段
	enum ID_FIELDS
	{
		ITEM_ID			= 1000001,
	};



	// 配置表id分段
	enum CFG_ID_FIELDS
	{
		// 副本id
		CFG_COPY_ID		= 101,

		// stage id = copy_id * 100 ?


		// 物品id
		CFG_ITEM_ID		= 100001,


		// 由于卡牌，装备都属于物品，所以这里的id区分只是配置上的
		// 区分，最后还是统一到一个区间去。

		// 卡牌id
		CFG_CARD_ID		= 200001,

		// 装备id
		CFG_EQUIP_ID	= 300001,


		//
		CFG_SKILL_ID	= 900001,



		// 对象id
		CFG_OBJ_ID		= 1000001,

	};



	enum Dir
	{
		DIR_L,		// 左
		DIR_R,		// 右
		DIR_MAX
	};



	enum
	{
		STAGE_NORMAL,
		STAGE_PASS,
		STAGE_PERFECT = 3,
	};


	// buff event result
	enum EventResult
	{
		ER_EXPIRE = -2,					// 时间到
		ER_EXIT = -1,					// 作用失效
		ER_CHECKFAIL = 0,				// 检查失败
		ER_OK,							// 

	};



	// 游戏变量
	enum E_GAME_DEFINE_VAR
	{
		GD_STAGE_NUM_MAX = 256,
		//每条线归属判断基准
		GD_LINE_DISTANCE_MAX_LIMIT = 10,
		// 飘字偏移值
		GD_BLOOD_OFFSET_BODY_LEN = 5,
		// 技能个数
		GD_SKILL_NUM_MAX = 5,
		// obj可携带的buff数
		GD_BUFF_NUM_MAX = 5,
		GD_SKILL_SELECT_VAR_MAX = 2,
		// 最大技能伤害参数
		GD_SKILL_VAR_MAX = 3,
		// 怪物id编号起始
		GD_MONSTER_OBJ_ID_BEGIN = 0x10000,
		// 子弹id编号开始
		GD_BULLET_OBJ_ID_BEGIN = 0x100000,
		// buff 补充参数为3个
		GD_BUFF_VAL_MAX = 3,
		// 怪物在自由状态下思考的间隔，
		GD_NPC_THINK_INTERVAL = 3,
		// 最大的关卡数
		GD_STAGE_MAX_NUM = 100,
		// 关卡英雄最大个数
		GD_STAGE_HERO_MAX = 10,
		// 关卡商店最大物品数
		GD_STAGE_SHOP_ITEM_MAX = 8,
		// 每关最大的回合数
		GD_ROUND_NUM_MAX = 10,
		// 最大上场兵数
		GD_ARMY_ON_ROUND_NUM_MAX = 8,
		// 最大卡牌星级
		GD_CARD_STAR_LVL_MAX = 5,
		// 掉落最大组数
		GD_DROP_GROUP_CNT = 5,
		// 奖励最大组数
		GD_REWARD_CNT_MAX = 10,
		// 格子单元最大累计数目
		GD_ITEM_GRID_CNT = 999,
		
		// -- 角色初始配置
		// 初始化金币
		GD_PLAYER_INIT_GOLD			= 1000,
		// 初始化钻石
		GD_PLAYER_INIT_DIAMOND		= 100,
		// 初始化背包数
		GD_PLAYER_INIT_BAG_NUM		= 40,
		// 初始化体力
		GD_PLAYER_PHYS_CNT			= 100,
		// 体力增长的间隔
		GD_PHYS_INCR_INTERVAL		= 900,

		// 休闲动作间隔（秒）
		GD_ARDER_INTERVAL_TIME		= 2,

	};


	// 关卡得分等级
	enum
	{
		E_STAGE_LVL_NONE,
		E_STAGE_LVL_ONE,
		E_STAGE_LVL_TWO,
		E_STAGE_LVL_THREE,
	};


	
	// 技能释放类型
	enum SKILL_TYPE
	{
		ST_PASSIVE			= 1,				// 被动
		ST_AUTO,								// 自动释放，普通攻击
		ST_POSITIVE_IM,							// 主动，点击释放
		ST_POSITIVE_DRAG,						// 主动，拖放
	};



	// 战斗的结果
	enum BattleResult
	{
		BR_LOSE,
		BR_WIN,
		BR_TIMEOUT,
	};



	// 
	//enum BUFF_UPDATE_RES
	//{
	//	BUR_CONTINUE,
	//	BUR_DISPEAR,
	//};



	// 装备类型
	enum EQUIP_TYPE
	{
		ET_HELMET = 1,		// 头盔
		ET_NECKLACE,		// 项链
		ET_CLOTHES,			// 衣服
		ET_WEAPON,			// 武器
		ET_ORNAMENT,		// 饰品
		ET_SHOES,			// 靴子
		ET_MAX = ET_SHOES,
	};



	// 任务类型
	enum TASK_TYPE
	{
		TT_MT_EVENT			= 0x010000,			// 触发事件，譬如参加几次战斗等
		TT_MT_COLLECT		= 0x020000,			// 收集



		TT_ST_ITEM			= 1,				// 物品
		TT_ST_FIGHT_COPY	= 2,				// 战斗副本
		TT_ST_LOGIN			= 4,
		TT_ST_FIGHT_OBJ		= 8,
	};




	// obj属性
	struct cfg_Obj_Attr
	{
		int id;
		char name[BaseDefine::COMMON_LENGTH];			// object name
		char head_path[BaseDefine::PATH_LENGTH];		// head pic path
		char path[BaseDefine::PATH_LENGTH];				// Armature path
		float speed;									// 移动速度
		float scale;									// 为统一尺寸，放缩因子
		int hp;											// 血量
		int hp_max;										// 最大血量
		int ghost;										// 召唤的成本，目前叫魂魄
		float ghost_speed;								// 魂魄增长速度，一般只有英雄才有这个属性
		int ghost_drop;									// 魂魄掉落值
		int buy_cd;										// 选择出场的冷却时间
		int hero_ctrl;									// 统御力
		float strength;									// 力量
		float wise;										// 智力
		float agility;									// 敏捷
		int phy_atk;									// 攻击
		int mag_atk;
		int atk_cri;									// 暴击
		int phy_def;									// 防御
		int mag_def;									//
		int skill_ids[GameDefine::GD_SKILL_NUM_MAX];
		int drop_id;


		cfg_Obj_Attr()
		{
			memset(this,0,sizeof(cfg_Obj_Attr));
		}

	};







	struct cfg_Msg
	{
		int id;
		unsigned char msg_type;
		char msg[BaseDefine::MSG_LENGTH];


		cfg_Msg()
		{
			memset(this,0,sizeof(cfg_Msg));
		}
	};



	enum SkillAffectMask
	{
		SAM_SHAKE			= 0x0001,	// 震动效果
		SAM_BULLET_TIME		= 0x0002,	// 子弹时间
	};


	// 技能伤害类型
	enum SKILL_DMG_TYPE
	{
		SK_DMG_PHY	= 1,						// 物理结算类型
		SK_DMG_MAG,								// 法术结算类型
	};



	// 技能配置
	struct cfg_Skill_Info
	{
		int id;
		SKILL_TYPE sk_type;										// 技能释放操作类型
		SKILL_DMG_TYPE sk_dmg_type;								// 技能伤害类型
		int sk_exec_type;										// 技能执行类型
		char sk_name[BaseDefine::COMMON_LENGTH];				// 技能名称		
		char szSkillDesc[BaseDefine::STRING_LENGTH];			// 技能描述
		char szSkillIcon[BaseDefine::COMMON_LENGTH];			// 技能图标
		int affect_mask;										// 一些辅助效果掩码
		int emit_id;											// 发射ID
		int req_lvl;											// 等级需求
		int req_ling;											// 灵力需求
		float atk_interval;										// 攻击间隔
		float ling_speed;										// 灵力增长速度
		int tar_sel_type;										// 目标选择类型
		int tar_num;											// 目标数量，-1不限
		float ts_vals[GameDefine::GD_SKILL_SELECT_VAR_MAX];		// 目标选择类型参数1
		char src_act_name[BaseDefine::MIN_COMMON_LENGTH];		// 动作类型
		char hit_effect[BaseDefine::COMMON_LENGTH];				// 目标特效
		int damage_type;										// 伤害类型
		float sk_vals[GameDefine::GD_SKILL_VAR_MAX];			// 技能参数
		int buff_id;											// buffID

		cfg_Skill_Info()
		{
			memset(this,0,sizeof(cfg_Skill_Info));
		}
	};



	struct cfg_Bullet_Info
	{
		int id;														
		float scale;											// 放缩比例
		float speed;											// 速度
		float distance;											// 最大作用距离
		char path[BaseDefine::MIN_COMMON_LENGTH];				// sprite
		char tar_hit_effect[BaseDefine::MIN_COMMON_LENGTH];		// 命中的特效


		cfg_Bullet_Info()
		{
			memset(this,0,sizeof(cfg_Bullet_Info));
		}

	};



	// 游戏实例数据
	struct stGameEntityAttr
	{
		// 基本属性
		int m_card_id;					// 卡牌id
		int m_obj_id;					//  obj_attr_id 快速索引
		int m_hp;
		int m_hp_max;
		int m_phy_atk;					// 攻击
		int m_mag_atk;
		int m_atk_cri;					// 暴击
		int m_phy_def;					// 防御
		int m_mag_def;

		float m_speed;
		char m_szName[BaseDefine::COMMON_LENGTH];


		stGameEntityAttr()
		{
			memset(this,0,sizeof(stGameEntityAttr));
		}

	};





	/*
	 * 状态传递的数据	
	 */
	struct state_attr
	{

		enum
		{
			SA_SKILL_MASK	= 0x0001,
			SA_POS_MASK		= 0x0002,
			SA_DEST_MASK	= 0x0004,
		};

		int mask;
		int skill_id;
		Vec2 cur_pos;
		Vec2 dest;

		state_attr():
			mask(0),
			skill_id(0)
		{

		}
	};


	// 动画事件
	struct anim_event
	{
		int obj_id;
		char act_name[BaseDefine::MIN_COMMON_LENGTH];

		anim_event()
		{
			memset(this,0,sizeof(anim_event));
		}
	};



	// buff data
	struct cfg_Buff_Data
	{
		int id;											// id
		int buff_type;									// buff类型：持续型，dot型
		unsigned int event_mask;						// 事件掩码,对应BuffMgr::BuffEventMask
		float active_time;								// 持续时间
		char eff_name[BaseDefine::COMMON_LENGTH];		// 
		float first_time;								// 第一次作用时间
		float act_interval;								// 触发间隔
		float bd_vals[GD_BUFF_VAL_MAX];					// buff参数
		
		cfg_Buff_Data()
		{
			memset(this,0,sizeof(cfg_Buff_Data));
		}
	};



	struct tBuffData 
	{
		int m_buff_id;					// buff id
		float m_elapse;					// 逝去时间
		int	m_act_num;					// 作用次数
		//unsigned int m_em;			// 事件掩码
		int src_id;						// buff释放者

		tBuffData()
		{
			memset(this,0,sizeof(tBuffData));
		}

		void reset()
		{
			memset(this,0,sizeof(tBuffData));
		}


		bool isValid()
		{
			return m_buff_id > 0;
		}

	};
	

	enum GUIDE_TIP_TYPE
	{
		GTT_NONE,
		GTT_TEXT,
		GTT_IMAGE,
	};


	// 引导掩码信息
	struct tGuideMaskInfo
	{
		GUIDE_TIP_TYPE tip_type;							// 补充提示类型（无，文字，图片等）
		int desc_id;										// 补充描述id,对应msg表id
		int event_mask;										// 事件掩码，进行到下一步的条件，默认无
		Rect rect;											// 掩码信息
		char ani_name[BaseDefine::MIN_COMMON_LENGTH];		// 动画名

		tGuideMaskInfo()
		{
			memset(ani_name,0,sizeof(ani_name));
		}
	};


	// 引导数据表
	struct cfg_Guide_Info
	{
		enum
		{
			GUIDE_INFO_NUM = 4,
		};


		enum eGuideEventMask
		{
			GEM_NONE,
			GEM_DONE,			// 确定完成
		};


		//
		int id;
		int op_type;										// 一些特殊的操作类型									
		int req_guide_id;									// 前置引导id
		std::vector<tGuideMaskInfo> mask_infos;				// 掩码信息
		char ani_path[BaseDefine::COMMON_LENGTH];			// 动画文件路径
		int gf_vals[GUIDE_INFO_NUM];

		cfg_Guide_Info()
		{
			id = 0;
			op_type = 0;
			req_guide_id = 0;
			memset(ani_path,0,sizeof(ani_path));
			memset(gf_vals,0,sizeof(gf_vals));
		}
	};



	// 每日任务
	struct cfg_DailyTask_Info
	{
		int id;						
		int task_type;								// 任务类型 TASK_TYPE
		char task_desc[BaseDefine::PATH_LENGTH];	// 任务描述
		int task_target;							// 任务目标
		int task_num;								// 任务数量
		std::vector<int> rewards;					// 奖励
	};



	// ------------ 地图数据 ------------------


	// 触发器信息
	struct tTriggerInfo 
	{
		enum TRIG_METHOD_TYPE
		{
			TMT_ONCE,
			TMT_REPEAT,
		};

		int ti_id;			// 触发器ID
		int nTrigType;		// 触发器类型
		int nCount;			// 触发次数
		Rect m_rect;		// 区域


		tTriggerInfo()
		{
			memset(this,0,sizeof(tTriggerInfo));
		}

	};


	// 怪物出场数据
	struct tEnemyObj
	{
		int id;
		int round;
		int offset;
		Vec2 pos;
		bool bDone;

		tEnemyObj()
		{
			memset(this,0,sizeof(tEnemyObj));
		}

	};

	
	// 回合提示信息
	struct tHintInfo
	{
		int round_num;							// 总回合数
		int cur_round;							// 当前回合
		float round_offset[GD_ROUND_NUM_MAX];	// 回合偏移值


		bool isOver()
		{
			return cur_round >= round_num;
		}


		tHintInfo()
		{
			memset(this,0,sizeof(tHintInfo));
		}
	};


	// --------------------------------------



	// ---------- local player data ---------------
	// 保存玩家的游戏数据结构


	// 实例物品数据
	struct tItemInfo
	{
		int item_id;				// 示例ID
		int item_temp_id;			// item模板ID
		int item_num;				// 个数

		tItemInfo()
		{
			item_id = 0;
			item_temp_id = 0;
			item_num = 1;
		}

		virtual void serialize(TaoOStream& _stream);
		virtual void unserialize(TaoIStream& _stream);

	};


	// 卡实例
	struct tCardInfo : public tItemInfo
	{
		int m_lvl;					// 等级，实际的等级
		int m_star;					// 星级
		int m_intense_lvl;			// 强化等级
		unsigned int m_exp;			// 经验
		int m_fight;				// 战斗力

		tCardInfo():
			tItemInfo()
		{
			m_lvl = 1;
			m_star = 1;
			m_intense_lvl = 0;
			m_exp = 0;
			m_fight = 0;
		}

		virtual void serialize(TaoOStream& _stream);
		virtual void unserialize(TaoIStream& _stream);

	};



	// 装备实例信息
	struct tEquipInfo : public tItemInfo
	{
		int m_intense_lvl;			// 强化等级 


		tEquipInfo():
			tItemInfo()
		{
			m_intense_lvl = 0;
		}


		virtual void serialize(TaoOStream& _stream);
		virtual void unserialize(TaoIStream& _stream);
	};





	struct tBagInfo
	{
		int m_grid_num;							// 有效格子数
		std::map<int,tItemInfo*> m_items;		// 物品数据

		typedef std::map<int,tItemInfo*>::iterator item_iter;
		typedef std::map<int,tItemInfo*>::const_iterator const_item_iter;

		tBagInfo()
		{
			m_grid_num = GD_PLAYER_INIT_BAG_NUM;
		}

		~tBagInfo()
		{
			for (auto _iter : m_items)
			{
				CC_SAFE_DELETE(_iter.second);
			}
			m_items.clear();
		}


		bool full()
		{
			return m_grid_num == m_items.size();
		}

		//
		bool addItem(tItemInfo* item)
		{
			if (full())
			{
				return false;
			}

			m_items.insert(std::make_pair(item->item_id,item));
			return true;
		}


		//
		bool removeItem(int inst_id)
		{
			item_iter _iter = m_items.find(inst_id);
			if (_iter == m_items.end())
			{
				return false;
			}

			CC_SAFE_DELETE(_iter->second);
			m_items.erase(_iter);
			return true;
		}

		//
		tItemInfo* getItem(int inst_id)
		{
			item_iter _iter = m_items.find(inst_id);
			if (_iter != m_items.end())
			{
				return _iter->second;
			}

			return nullptr;
		}

		void serialize(TaoOStream& _stream);
		void unserialize(TaoIStream& _stream);

	};


	// 副本商店商品信息
	struct tCopyShopItemInfo
	{
		int last_update_time;			// 更新时间
		unsigned int u_bought_mask;		// 购买掩码
		std::vector<int> _item_ids;		// 物品id

		tCopyShopItemInfo()
		{
			u_bought_mask = 0;
			last_update_time = 0;
		}


		//
		bool isBought(int _item_index)
		{
			return (u_bought_mask & (1 << _item_index)) > 0;
		}

		//
		void maskBought(int _item_index)
		{
			u_bought_mask |= (1 << _item_index);
		}

	};


	// 实例副本数据
	struct tCopyInfo
	{
		enum
		{
			STAR_SHIFT = 30,
		};

		std::vector<unsigned int> m_data;
		// 副本商店刷新时间
		std::map<int,tCopyShopItemInfo> m_copy_shop_infos;

		
		void serialize(TaoOStream& _stream);
		void unserialize(TaoIStream& _stream);


		// 获取副本战斗评价星级
		int getStageStar(int _stage_info)
		{
			return (_stage_info & 0xc0000000) >> STAR_SHIFT;
		}

		int getStageId(int _stage_info)
		{
			return (_stage_info & (~0xc0000000));
		}

		void setStageStar(int _stage_id, int _stage_star)
		{
			unsigned int stage_info = ((_stage_star & 0x00000003) << STAR_SHIFT) | (_stage_id);
			m_data.push_back(stage_info);
		}

	};



	// 基本属性
	struct tBaseAttr 
	{
		enum BA_TYPE
		{
			BA_LVL,						// 等级
			BA_VIP,						// vip等级
			BA_GOLD,					// 金币
			BA_DIAMOND,					// 钻石
			BA_PHYSICAL,				// 体力
			BA_PHYSICAL_UPDATE,			// 体力更新时间
			BA_MAX,
		};

		std::vector<unsigned int> m_data;

		void serialize(TaoOStream& _stream);
		void unserialize(TaoIStream& _stream);


		// 注意返回的无效值
		unsigned int& operator[]( int _index)
		{
			if (_index > BA_MAX)
			{
				throw "out of range";
			}
			return m_data[_index];
		}


		tBaseAttr()
		{
			m_data.resize(BA_MAX);
		}

	};


	// 物品id + 物品数量
	struct tBaseItemCnt
	{
		int id;
		int cnt;

		tBaseItemCnt()
		{
			memset(this,0,sizeof(tBaseItemCnt));
		}
	};


	// 物品id + 物品概率
	struct tBaseItemProb
	{
		int id;
		float prob;

		tBaseItemProb()
		{
			memset(this,0,sizeof(tBaseItemProb));
		}
	};



	//战斗中英雄的数据
	struct tBattleHero
	{						
		int base_ghost;						// 灵气，用于召唤小兵
		float ghost_base_speed;				// 灵气增长速度

		tBattleHero()
		{
			memset(this,0,sizeof(tBattleHero));
		}

		bool costGhost(int _ghost,bool bCost = true)
		{
			if (base_ghost < _ghost)
			{
				return false;
			}

			if(bCost)
				base_ghost -= _ghost;

			return true;
		}
	};


	// 临时的战斗相关信息
	struct tTempFightInfo
	{

		enum
		{
			// 英雄索引
			ARMY_HERO_INDEX = 0,
		};

		// 战斗兵种选择信息
		int army_inst_id[GD_ARMY_ON_ROUND_NUM_MAX];
		// 当前关卡
		int curr_stage_id;
		// 奖励信息
		tBaseItemCnt rewards[GD_REWARD_CNT_MAX];
		// 奖励金币
		int rewardGold;
		// 防守者死亡个数
		unsigned char defender_dead_cnt;
		// 战斗结果评价星级
		unsigned char star_cnt;
		// 英雄的实时数据
		tBattleHero hero_info;

		
		tTempFightInfo()
		{
			memset(this,0,sizeof(tTempFightInfo));
		}

		void reset()
		{
			memset(this,0,sizeof(tTempFightInfo));
		}


		void resetReward()
		{
			memset(rewards,0,sizeof(tBaseItemCnt)*GD_REWARD_CNT_MAX);
			rewardGold = 0;
			defender_dead_cnt = 0;
			memset(&hero_info,0,sizeof(tBattleHero));
		}


		int addRewardId(int _item_id)
		{
			int item_idx = -1;
			for (int i = 0; i < GD_REWARD_CNT_MAX; i++)
			{
				if (rewards[i].id == _item_id)
				{
					rewards[i].cnt++;
					item_idx = i;
					break;
				}

				if(rewards[i].id == 0)
				{
					rewards[i].id = _item_id;
					rewards[i].cnt++;
					item_idx = i;
					break;
				}
			}

			return item_idx;
		}


		//
		int getRewardCnt()
		{
			int nRetCnt = 0;
			for (int i = 0; i < GD_REWARD_CNT_MAX; i++)
			{
				if (rewards[i].id == 0)
				{
					break;
				}
				nRetCnt += rewards[i].cnt;
			}
			return nRetCnt;
		}


		//
		bool removeArmyId(int _id)
		{
			for (int i = 0; i < GD_ARMY_ON_ROUND_NUM_MAX; i++)
			{
				if (army_inst_id[i] == _id)
				{
					army_inst_id[i] = 0;
					return true;
				}
			}

			return false;
		}


		/*
		 * @desc 添加兵种选择id数据
		 * @param _id 兵种实例id
		 * @return >=0 实际的位置索引, -1,满了，-2，重复 
		 *	
		 */
		int addArmyId(int _id)
		{
			int sel_index = -1; // 没有空位
			// 跳过英雄位
			for (int i = 1; i < GD_ARMY_ON_ROUND_NUM_MAX; i++)
			{
				if (army_inst_id[i] == 0)
				{
					if(sel_index == -1)
						sel_index = i;
				}
				else
				{
					if (army_inst_id[i] == _id)
					{
						sel_index = -2;
						break;
					}
				}
			}

			if (sel_index > 0)
			{
				army_inst_id[sel_index] = _id;
			}

			return sel_index;
		}


	};



	// 游戏存档版本信息
	enum GAME_VERSION_DATA
	{
		VER_A = 1,
		VER_B = 1,
		VER_C = 1,


		GVD_FACTOR = 100,
	};


	// 全局数据
	struct tGlobalData 
	{
		unsigned int version;			// 版本信息( A*10000 + B*100 + C)
		int structSize;					// 存档结构大小信息
		int lastItemId;					// 最后一次itemID


		tGlobalData()
		{
			version = VER_A * GVD_FACTOR * GVD_FACTOR + VER_B * GVD_FACTOR + VER_C;
			structSize = sizeof(tItemInfo) + sizeof(tCardInfo) + sizeof(tBagInfo) + sizeof(tCopyInfo) + sizeof(tBaseAttr);
			lastItemId = ITEM_ID;
		}


		bool check()
		{
			if(version != VER_A * GVD_FACTOR * GVD_FACTOR + VER_B * GVD_FACTOR + VER_C ||
				structSize != sizeof(tItemInfo) + sizeof(tCardInfo) + sizeof(tBagInfo) + sizeof(tCopyInfo) + sizeof(tBaseAttr))
				return false;

			return true;
		}


		void serialize(TaoOStream& _stream);
		void unserialize(TaoIStream& _stream);

	};


	// 引导数据
	struct tGuideInfo
	{
		int last_guide_id;

		tGuideInfo()
		{
			memset(this,0,sizeof(tGuideInfo));
		}


		void serialize(TaoOStream& _stream);
		void unserialize(TaoIStream& _stream);
	};


	enum TASK_STATE
	{
		TS_TIMEOUT = -1,
		TS_INVALID = 0,
		TS_DOING,
		TS_DONE,
	};


	// 每日任务实例数据
	struct tDailyTaskInfo
	{
		int tid;							// 任务Id
		TASK_STATE ts;						// 当前任务状态
		int cur_num;						// 当前有效次数
		unsigned int last_time;				// 上次时间



		tDailyTaskInfo()
		{
			memset(this,0,sizeof(tDailyTaskInfo));
		}
		~tDailyTaskInfo() {}


		bool newTask(int _tid);
		void reset();

		void serialize(TaoOStream& _stream);
		void unserialize(TaoIStream& _stream);

	};




	// ----------- local player data end ---------------





	// 物品类型
	enum ITEM_TYPE
	{
		IT_ITEM = 1,
		IT_EQUIP,
		IT_FRAG,
		IT_CARD,
	};


	// 五行
	enum CARD_ATTR_TYPE
	{
		CAT_METAL = 1,
		CAT_WOOD,
		CAT_WATER,
		CAT_FIRE,
		CAT_EARTH,
	};




	enum ARMY_TYPE
	{
		AT_NONE,			// 无
		AT_ARMY_SOLDIER,	// 小兵
		AT_ARMY_HERO,		// 英雄
	};




	// 物品等级
	enum ITEM_LVL
	{
		IL_WHITE = 1,
		IL_GREEN,
		IL_BLUE,
		IL_PURPLE,
		IL_ORANGE,
	};


	// 消耗类型
	enum COST_TYPE
	{
		CT_GOLD = 1,
		CT_DIAMOND,
	};


	// 物品模板基类
	struct cfg_Item
	{
		int id;												//
		ITEM_TYPE item_type;								// 物品类型
		ITEM_LVL item_lvl;									// 物品等级，白，绿，蓝，紫，橙

		// 显示相关
		char szName[BaseDefine::COMMON_LENGTH];				// 物品名称
		char szItemPic[BaseDefine::COMMON_LENGTH];			// 图片路径（98*98）
		// 价值
		COST_TYPE ct_type;									// 价值类型(金币，钻石)
		unsigned int cost;									// 价值


		cfg_Item()
		{
			memset(this,0,sizeof(cfg_Item));
		}

	};



	// 装备
	struct cfg_EquipItem : public cfg_Item
	{
		EQUIP_TYPE equip_type;

		int add_phy_atk;
		int add_mag_atk;
		int add_phy_cri;
		int add_mag_cri;

		cfg_EquipItem() 
		{
			memset(this,0,sizeof(cfg_EquipItem));
		}
	};




	// 卡
	struct cfg_Card : public cfg_Item
	{
		ARMY_TYPE arm_type;									// 小兵、英雄
		int desc_id;										// 对应msg配置表的id,用于描述
		char card_pic[BaseDefine::COMMON_LENGTH];			// 卡图片名称
		CARD_ATTR_TYPE cat;									// 五行属性
		unsigned int exchange_ghost;						// 魂魄兑换需求
		unsigned int exchange_prestige;						// 声望兑换需求
		int req_ctrl;										// 统御力需求
		int obj_id;											// 卡对应的角色id

		cfg_Card()
		{
			memset(this,0,sizeof(cfg_Card));
		}

	};



	// 副本表配置
	struct cfg_Copy
	{
		int id;
		int req_lvl;
		std::vector<int> _stages;					// 最大GameDefine::GD_STAGE_MAX_NUM
		std::vector<int> _cards;					// GameDefine::GD_STAGE_HERO_MAX
		std::vector<tBaseItemProb> _shopitems;		// GameDefine::GD_STAGE_SHOP_ITEM_MAX


		cfg_Copy()
		{
			id = 0;
			req_lvl = 1;
		}

	};



	// 关卡数据表
	struct cfg_Stage
	{
		int id;
		int req_lvl;
		int req_stage_id;									// 前置副本id
		char szDesc[BaseDefine::STRING_LENGTH];				// 关卡描述
		char szNpcPic[BaseDefine::COMMON_LENGTH];			// npc头像
		int phys_cost;										// 体力消耗
		int reward_gold;									// 金币奖励
		char stage_path[BaseDefine::COMMON_LENGTH];			// 关卡数据
		int* drops;											// 掉落表
		int* monsters;										// 怪物表


		cfg_Stage()
		{
			memset(this,0,sizeof(cfg_Stage));
		}


		~cfg_Stage()
		{
			CC_SAFE_DELETE_ARRAY(drops);
			CC_SAFE_DELETE_ARRAY(monsters);
		}

	};


	//
	struct tDropItemInfo
	{
		float drop_prob;
		int drop_item_id;

		tDropItemInfo()
		{
			memset(this,0,sizeof(tDropItemInfo));
		}
	};

	// 掉落表
	struct cfg_DropInfo
	{
		int id;	
		int drop_group_cnt;												// 掉落物品组数
		int lbounds;													// 掉落下限
		int ubounds;													// 掉落上限
		int reward_gold;												// 掉落金币
		tDropItemInfo m_drop_items[GameDefine::GD_DROP_GROUP_CNT];		// 掉落物品组

		cfg_DropInfo()
		{
			memset(this,0,sizeof(cfg_DropInfo));
		}
	};


	// 资源载入内存类型
	enum ASSETS_LOAD_TYPE
	{
		ALT_STATIC= 1,			// 静态类型，常驻
		ALT_DYNAMIC				// 动态类型，会销毁
	};


	// 资源类型
	enum ASSETS_TYPE
	{
		AT_ORIGINAL = 1,		// 原生资源 png
		AT_PLIST,				// plist资源
		AT_ARMATURE,			// armature 动画资源
	};


	// 资源载入信息
	//struct tAssetDetailInfo
	//{
	//	union unAssetDetail
	//	{
	//		struct
	//		{
	//			//
	//			char plist_path[BaseDefine::COMMON_LENGTH];
	//			char png_path[BaseDefine::COMMON_LENGTH];

	//		} multi_asset_path;
	//		//
	//		char png_path[BaseDefine::COMMON_LENGTH*2];
	//	
	//	} adi;


	//	tAssetDetailInfo()
	//	{
	//		memset(this,0,sizeof(tAssetDetailInfo));
	//	}	
	//};


	// 资源集信息
	struct cfg_AssetsInfo
	{
		int id;
		ASSETS_LOAD_TYPE asset_load_type;				// 资源载入类型
		ASSETS_TYPE	asset_type;
		int asset_id;									// 所属资源集id
		std::string base_path;							// 资源文件夹路径
		std::vector<std::string> files;					// 资源文件集

		cfg_AssetsInfo()
		{
			id = 0;
			asset_load_type = ALT_STATIC;
			asset_type = AT_ORIGINAL;
		}
	};


	// 装备数据






	// 选择过滤器
	struct TargetSelectorFilter
	{
		TargetSelectorFilter()
		{
			select_mask = 0;
			filter_dis = 0;
			sel_num = 0;
			bAdjustY = false;
		}


		int select_mask;					// 选择obj类型，是hero,zombie还是all
		float filter_dis;					// 选择范围
		int sel_num;						// 选择个数
		bool bAdjustY;						// 由于GameEntity已经偏移了0.42H,基于其再偏移就需要修正
	};



	// 自定义事件
	struct sttCustomEvent
	{
		enum CE_TYPE
		{
			CE_VAL_MAX = 3,


			CE_BATTLE_REWARD_UPDATE = 1,			// 奖励动画事件
			CE_MAIN_UI_UDPATE,						// 主UI刷新
			CE_MAIN_UI_ATTR_UPDATE,					// 刷新属性
		};

		int ce_type;
		float _val[CE_VAL_MAX];

		sttCustomEvent()
		{
			memset(this,0,sizeof(sttCustomEvent));
		}
	};










	// 奖励刷新
	extern const char* REWARD_UPDATE_EVENT;
	extern const char* BATTLE_HERO_INFO_UPDATE_EVENT;
	extern const char* MAIN_UI_UPDATE_EVENT;
	//static const char* ANIMATION_EVENT = "_anim_event";
	extern const float MIN_FLOAT_VALUE;
	extern const char* ROLE_SAVE_FILE;


}

