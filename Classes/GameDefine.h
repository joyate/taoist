#pragma once
#include "BaseDefine.h"
#include "cocos2d.h"
#include <string>
#include "utility/TaoIStream.h"
#include "utility/TaoOStream.h"

USING_NS_CC;


namespace GameDefine
{

	// ʵ��id��
	enum ID_FIELDS
	{
		ITEM_ID			= 1000001,
	};



	// ���ñ�id�ֶ�
	enum CFG_ID_FIELDS
	{
		// ����id
		CFG_COPY_ID		= 101,

		// stage id = copy_id * 100 ?


		// ��Ʒid
		CFG_ITEM_ID		= 100001,


		// ���ڿ��ƣ�װ����������Ʒ�����������id����ֻ�������ϵ�
		// ���֣������ͳһ��һ������ȥ��

		// ����id
		CFG_CARD_ID		= 200001,

		// װ��id
		CFG_EQUIP_ID	= 300001,


		//
		CFG_SKILL_ID	= 900001,



		// ����id
		CFG_OBJ_ID		= 1000001,

	};



	enum Dir
	{
		DIR_L,		// ��
		DIR_R,		// ��
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
		ER_EXPIRE = -2,					// ʱ�䵽
		ER_EXIT = -1,					// ����ʧЧ
		ER_CHECKFAIL = 0,				// ���ʧ��
		ER_OK,							// 

	};



	// ��Ϸ����
	enum E_GAME_DEFINE_VAR
	{
		GD_STAGE_NUM_MAX = 256,
		//ÿ���߹����жϻ�׼
		GD_LINE_DISTANCE_MAX_LIMIT = 10,
		// Ʈ��ƫ��ֵ
		GD_BLOOD_OFFSET_BODY_LEN = 5,
		// ���ܸ���
		GD_SKILL_NUM_MAX = 5,
		// obj��Я����buff��
		GD_BUFF_NUM_MAX = 5,
		GD_SKILL_SELECT_VAR_MAX = 2,
		// ������˺�����
		GD_SKILL_VAR_MAX = 3,
		// ����id�����ʼ
		GD_MONSTER_OBJ_ID_BEGIN = 0x10000,
		// �ӵ�id��ſ�ʼ
		GD_BULLET_OBJ_ID_BEGIN = 0x100000,
		// buff �������Ϊ3��
		GD_BUFF_VAL_MAX = 3,
		// ����������״̬��˼���ļ����
		GD_NPC_THINK_INTERVAL = 3,
		// ���Ĺؿ���
		GD_STAGE_MAX_NUM = 100,
		// �ؿ�Ӣ��������
		GD_STAGE_HERO_MAX = 10,
		// �ؿ��̵������Ʒ��
		GD_STAGE_SHOP_ITEM_MAX = 8,
		// ÿ�����Ļغ���
		GD_ROUND_NUM_MAX = 10,
		// ����ϳ�����
		GD_ARMY_ON_ROUND_NUM_MAX = 8,
		// ������Ǽ�
		GD_CARD_STAR_LVL_MAX = 5,
		// �����������
		GD_DROP_GROUP_CNT = 5,
		// �����������
		GD_REWARD_CNT_MAX = 10,
		// ���ӵ�Ԫ����ۼ���Ŀ
		GD_ITEM_GRID_CNT = 999,
		
		// -- ��ɫ��ʼ����
		// ��ʼ�����
		GD_PLAYER_INIT_GOLD			= 1000,
		// ��ʼ����ʯ
		GD_PLAYER_INIT_DIAMOND		= 100,
		// ��ʼ��������
		GD_PLAYER_INIT_BAG_NUM		= 40,
		// ��ʼ������
		GD_PLAYER_PHYS_CNT			= 100,
		// ���������ļ��
		GD_PHYS_INCR_INTERVAL		= 900,

		// ���ж���������룩
		GD_ARDER_INTERVAL_TIME		= 2,

	};


	// �ؿ��÷ֵȼ�
	enum
	{
		E_STAGE_LVL_NONE,
		E_STAGE_LVL_ONE,
		E_STAGE_LVL_TWO,
		E_STAGE_LVL_THREE,
	};


	
	// �����ͷ�����
	enum SKILL_TYPE
	{
		ST_PASSIVE			= 1,				// ����
		ST_AUTO,								// �Զ��ͷţ���ͨ����
		ST_POSITIVE_IM,							// ����������ͷ�
		ST_POSITIVE_DRAG,						// �������Ϸ�
	};



	// ս���Ľ��
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



	// װ������
	enum EQUIP_TYPE
	{
		ET_HELMET = 1,		// ͷ��
		ET_NECKLACE,		// ����
		ET_CLOTHES,			// �·�
		ET_WEAPON,			// ����
		ET_ORNAMENT,		// ��Ʒ
		ET_SHOES,			// ѥ��
		ET_MAX = ET_SHOES,
	};



	// ��������
	enum TASK_TYPE
	{
		TT_MT_EVENT			= 0x010000,			// �����¼���Ʃ��μӼ���ս����
		TT_MT_COLLECT		= 0x020000,			// �ռ�



		TT_ST_ITEM			= 1,				// ��Ʒ
		TT_ST_FIGHT_COPY	= 2,				// ս������
		TT_ST_LOGIN			= 4,
		TT_ST_FIGHT_OBJ		= 8,
	};




	// obj����
	struct cfg_Obj_Attr
	{
		int id;
		char name[BaseDefine::COMMON_LENGTH];			// object name
		char head_path[BaseDefine::PATH_LENGTH];		// head pic path
		char path[BaseDefine::PATH_LENGTH];				// Armature path
		float speed;									// �ƶ��ٶ�
		float scale;									// Ϊͳһ�ߴ磬��������
		int hp;											// Ѫ��
		int hp_max;										// ���Ѫ��
		int ghost;										// �ٻ��ĳɱ���Ŀǰ�л���
		float ghost_speed;								// ���������ٶȣ�һ��ֻ��Ӣ�۲����������
		int ghost_drop;									// ���ǵ���ֵ
		int buy_cd;										// ѡ���������ȴʱ��
		int hero_ctrl;									// ͳ����
		float strength;									// ����
		float wise;										// ����
		float agility;									// ����
		int phy_atk;									// ����
		int mag_atk;
		int atk_cri;									// ����
		int phy_def;									// ����
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
		SAM_SHAKE			= 0x0001,	// ��Ч��
		SAM_BULLET_TIME		= 0x0002,	// �ӵ�ʱ��
	};


	// �����˺�����
	enum SKILL_DMG_TYPE
	{
		SK_DMG_PHY	= 1,						// �����������
		SK_DMG_MAG,								// ������������
	};



	// ��������
	struct cfg_Skill_Info
	{
		int id;
		SKILL_TYPE sk_type;										// �����ͷŲ�������
		SKILL_DMG_TYPE sk_dmg_type;								// �����˺�����
		int sk_exec_type;										// ����ִ������
		char sk_name[BaseDefine::COMMON_LENGTH];				// ��������		
		char szSkillDesc[BaseDefine::STRING_LENGTH];			// ��������
		char szSkillIcon[BaseDefine::COMMON_LENGTH];			// ����ͼ��
		int affect_mask;										// һЩ����Ч������
		int emit_id;											// ����ID
		int req_lvl;											// �ȼ�����
		int req_ling;											// ��������
		float atk_interval;										// �������
		float ling_speed;										// ���������ٶ�
		int tar_sel_type;										// Ŀ��ѡ������
		int tar_num;											// Ŀ��������-1����
		float ts_vals[GameDefine::GD_SKILL_SELECT_VAR_MAX];		// Ŀ��ѡ�����Ͳ���1
		char src_act_name[BaseDefine::MIN_COMMON_LENGTH];		// ��������
		char hit_effect[BaseDefine::COMMON_LENGTH];				// Ŀ����Ч
		int damage_type;										// �˺�����
		float sk_vals[GameDefine::GD_SKILL_VAR_MAX];			// ���ܲ���
		int buff_id;											// buffID

		cfg_Skill_Info()
		{
			memset(this,0,sizeof(cfg_Skill_Info));
		}
	};



	struct cfg_Bullet_Info
	{
		int id;														
		float scale;											// ��������
		float speed;											// �ٶ�
		float distance;											// ������þ���
		char path[BaseDefine::MIN_COMMON_LENGTH];				// sprite
		char tar_hit_effect[BaseDefine::MIN_COMMON_LENGTH];		// ���е���Ч


		cfg_Bullet_Info()
		{
			memset(this,0,sizeof(cfg_Bullet_Info));
		}

	};



	// ��Ϸʵ������
	struct stGameEntityAttr
	{
		// ��������
		int m_card_id;					// ����id
		int m_obj_id;					//  obj_attr_id ��������
		int m_hp;
		int m_hp_max;
		int m_phy_atk;					// ����
		int m_mag_atk;
		int m_atk_cri;					// ����
		int m_phy_def;					// ����
		int m_mag_def;

		float m_speed;
		char m_szName[BaseDefine::COMMON_LENGTH];


		stGameEntityAttr()
		{
			memset(this,0,sizeof(stGameEntityAttr));
		}

	};





	/*
	 * ״̬���ݵ�����	
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


	// �����¼�
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
		int buff_type;									// buff���ͣ������ͣ�dot��
		unsigned int event_mask;						// �¼�����,��ӦBuffMgr::BuffEventMask
		float active_time;								// ����ʱ��
		char eff_name[BaseDefine::COMMON_LENGTH];		// 
		float first_time;								// ��һ������ʱ��
		float act_interval;								// �������
		float bd_vals[GD_BUFF_VAL_MAX];					// buff����
		
		cfg_Buff_Data()
		{
			memset(this,0,sizeof(cfg_Buff_Data));
		}
	};



	struct tBuffData 
	{
		int m_buff_id;					// buff id
		float m_elapse;					// ��ȥʱ��
		int	m_act_num;					// ���ô���
		//unsigned int m_em;			// �¼�����
		int src_id;						// buff�ͷ���

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


	// ����������Ϣ
	struct tGuideMaskInfo
	{
		GUIDE_TIP_TYPE tip_type;							// ������ʾ���ͣ��ޣ����֣�ͼƬ�ȣ�
		int desc_id;										// ��������id,��Ӧmsg��id
		int event_mask;										// �¼����룬���е���һ����������Ĭ����
		Rect rect;											// ������Ϣ
		char ani_name[BaseDefine::MIN_COMMON_LENGTH];		// ������

		tGuideMaskInfo()
		{
			memset(ani_name,0,sizeof(ani_name));
		}
	};


	// �������ݱ�
	struct cfg_Guide_Info
	{
		enum
		{
			GUIDE_INFO_NUM = 4,
		};


		enum eGuideEventMask
		{
			GEM_NONE,
			GEM_DONE,			// ȷ�����
		};


		//
		int id;
		int op_type;										// һЩ����Ĳ�������									
		int req_guide_id;									// ǰ������id
		std::vector<tGuideMaskInfo> mask_infos;				// ������Ϣ
		char ani_path[BaseDefine::COMMON_LENGTH];			// �����ļ�·��
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



	// ÿ������
	struct cfg_DailyTask_Info
	{
		int id;						
		int task_type;								// �������� TASK_TYPE
		char task_desc[BaseDefine::PATH_LENGTH];	// ��������
		int task_target;							// ����Ŀ��
		int task_num;								// ��������
		std::vector<int> rewards;					// ����
	};



	// ------------ ��ͼ���� ------------------


	// ��������Ϣ
	struct tTriggerInfo 
	{
		enum TRIG_METHOD_TYPE
		{
			TMT_ONCE,
			TMT_REPEAT,
		};

		int ti_id;			// ������ID
		int nTrigType;		// ����������
		int nCount;			// ��������
		Rect m_rect;		// ����


		tTriggerInfo()
		{
			memset(this,0,sizeof(tTriggerInfo));
		}

	};


	// �����������
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

	
	// �غ���ʾ��Ϣ
	struct tHintInfo
	{
		int round_num;							// �ܻغ���
		int cur_round;							// ��ǰ�غ�
		float round_offset[GD_ROUND_NUM_MAX];	// �غ�ƫ��ֵ


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
	// ������ҵ���Ϸ���ݽṹ


	// ʵ����Ʒ����
	struct tItemInfo
	{
		int item_id;				// ʾ��ID
		int item_temp_id;			// itemģ��ID
		int item_num;				// ����

		tItemInfo()
		{
			item_id = 0;
			item_temp_id = 0;
			item_num = 1;
		}

		virtual void serialize(TaoOStream& _stream);
		virtual void unserialize(TaoIStream& _stream);

	};


	// ��ʵ��
	struct tCardInfo : public tItemInfo
	{
		int m_lvl;					// �ȼ���ʵ�ʵĵȼ�
		int m_star;					// �Ǽ�
		int m_intense_lvl;			// ǿ���ȼ�
		unsigned int m_exp;			// ����
		int m_fight;				// ս����

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



	// װ��ʵ����Ϣ
	struct tEquipInfo : public tItemInfo
	{
		int m_intense_lvl;			// ǿ���ȼ� 


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
		int m_grid_num;							// ��Ч������
		std::map<int,tItemInfo*> m_items;		// ��Ʒ����

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


	// �����̵���Ʒ��Ϣ
	struct tCopyShopItemInfo
	{
		int last_update_time;			// ����ʱ��
		unsigned int u_bought_mask;		// ��������
		std::vector<int> _item_ids;		// ��Ʒid

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


	// ʵ����������
	struct tCopyInfo
	{
		enum
		{
			STAR_SHIFT = 30,
		};

		std::vector<unsigned int> m_data;
		// �����̵�ˢ��ʱ��
		std::map<int,tCopyShopItemInfo> m_copy_shop_infos;

		
		void serialize(TaoOStream& _stream);
		void unserialize(TaoIStream& _stream);


		// ��ȡ����ս�������Ǽ�
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



	// ��������
	struct tBaseAttr 
	{
		enum BA_TYPE
		{
			BA_LVL,						// �ȼ�
			BA_VIP,						// vip�ȼ�
			BA_GOLD,					// ���
			BA_DIAMOND,					// ��ʯ
			BA_PHYSICAL,				// ����
			BA_PHYSICAL_UPDATE,			// ��������ʱ��
			BA_MAX,
		};

		std::vector<unsigned int> m_data;

		void serialize(TaoOStream& _stream);
		void unserialize(TaoIStream& _stream);


		// ע�ⷵ�ص���Чֵ
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


	// ��Ʒid + ��Ʒ����
	struct tBaseItemCnt
	{
		int id;
		int cnt;

		tBaseItemCnt()
		{
			memset(this,0,sizeof(tBaseItemCnt));
		}
	};


	// ��Ʒid + ��Ʒ����
	struct tBaseItemProb
	{
		int id;
		float prob;

		tBaseItemProb()
		{
			memset(this,0,sizeof(tBaseItemProb));
		}
	};



	//ս����Ӣ�۵�����
	struct tBattleHero
	{						
		int base_ghost;						// �����������ٻ�С��
		float ghost_base_speed;				// ���������ٶ�

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


	// ��ʱ��ս�������Ϣ
	struct tTempFightInfo
	{

		enum
		{
			// Ӣ������
			ARMY_HERO_INDEX = 0,
		};

		// ս������ѡ����Ϣ
		int army_inst_id[GD_ARMY_ON_ROUND_NUM_MAX];
		// ��ǰ�ؿ�
		int curr_stage_id;
		// ������Ϣ
		tBaseItemCnt rewards[GD_REWARD_CNT_MAX];
		// �������
		int rewardGold;
		// ��������������
		unsigned char defender_dead_cnt;
		// ս����������Ǽ�
		unsigned char star_cnt;
		// Ӣ�۵�ʵʱ����
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
		 * @desc ��ӱ���ѡ��id����
		 * @param _id ����ʵ��id
		 * @return >=0 ʵ�ʵ�λ������, -1,���ˣ�-2���ظ� 
		 *	
		 */
		int addArmyId(int _id)
		{
			int sel_index = -1; // û�п�λ
			// ����Ӣ��λ
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



	// ��Ϸ�浵�汾��Ϣ
	enum GAME_VERSION_DATA
	{
		VER_A = 1,
		VER_B = 1,
		VER_C = 1,


		GVD_FACTOR = 100,
	};


	// ȫ������
	struct tGlobalData 
	{
		unsigned int version;			// �汾��Ϣ( A*10000 + B*100 + C)
		int structSize;					// �浵�ṹ��С��Ϣ
		int lastItemId;					// ���һ��itemID


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


	// ��������
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


	// ÿ������ʵ������
	struct tDailyTaskInfo
	{
		int tid;							// ����Id
		TASK_STATE ts;						// ��ǰ����״̬
		int cur_num;						// ��ǰ��Ч����
		unsigned int last_time;				// �ϴ�ʱ��



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





	// ��Ʒ����
	enum ITEM_TYPE
	{
		IT_ITEM = 1,
		IT_EQUIP,
		IT_FRAG,
		IT_CARD,
	};


	// ����
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
		AT_NONE,			// ��
		AT_ARMY_SOLDIER,	// С��
		AT_ARMY_HERO,		// Ӣ��
	};




	// ��Ʒ�ȼ�
	enum ITEM_LVL
	{
		IL_WHITE = 1,
		IL_GREEN,
		IL_BLUE,
		IL_PURPLE,
		IL_ORANGE,
	};


	// ��������
	enum COST_TYPE
	{
		CT_GOLD = 1,
		CT_DIAMOND,
	};


	// ��Ʒģ�����
	struct cfg_Item
	{
		int id;												//
		ITEM_TYPE item_type;								// ��Ʒ����
		ITEM_LVL item_lvl;									// ��Ʒ�ȼ����ף��̣������ϣ���

		// ��ʾ���
		char szName[BaseDefine::COMMON_LENGTH];				// ��Ʒ����
		char szItemPic[BaseDefine::COMMON_LENGTH];			// ͼƬ·����98*98��
		// ��ֵ
		COST_TYPE ct_type;									// ��ֵ����(��ң���ʯ)
		unsigned int cost;									// ��ֵ


		cfg_Item()
		{
			memset(this,0,sizeof(cfg_Item));
		}

	};



	// װ��
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




	// ��
	struct cfg_Card : public cfg_Item
	{
		ARMY_TYPE arm_type;									// С����Ӣ��
		int desc_id;										// ��Ӧmsg���ñ��id,��������
		char card_pic[BaseDefine::COMMON_LENGTH];			// ��ͼƬ����
		CARD_ATTR_TYPE cat;									// ��������
		unsigned int exchange_ghost;						// ���Ƕһ�����
		unsigned int exchange_prestige;						// �����һ�����
		int req_ctrl;										// ͳ��������
		int obj_id;											// ����Ӧ�Ľ�ɫid

		cfg_Card()
		{
			memset(this,0,sizeof(cfg_Card));
		}

	};



	// ����������
	struct cfg_Copy
	{
		int id;
		int req_lvl;
		std::vector<int> _stages;					// ���GameDefine::GD_STAGE_MAX_NUM
		std::vector<int> _cards;					// GameDefine::GD_STAGE_HERO_MAX
		std::vector<tBaseItemProb> _shopitems;		// GameDefine::GD_STAGE_SHOP_ITEM_MAX


		cfg_Copy()
		{
			id = 0;
			req_lvl = 1;
		}

	};



	// �ؿ����ݱ�
	struct cfg_Stage
	{
		int id;
		int req_lvl;
		int req_stage_id;									// ǰ�ø���id
		char szDesc[BaseDefine::STRING_LENGTH];				// �ؿ�����
		char szNpcPic[BaseDefine::COMMON_LENGTH];			// npcͷ��
		int phys_cost;										// ��������
		int reward_gold;									// ��ҽ���
		char stage_path[BaseDefine::COMMON_LENGTH];			// �ؿ�����
		int* drops;											// �����
		int* monsters;										// �����


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

	// �����
	struct cfg_DropInfo
	{
		int id;	
		int drop_group_cnt;												// ������Ʒ����
		int lbounds;													// ��������
		int ubounds;													// ��������
		int reward_gold;												// ������
		tDropItemInfo m_drop_items[GameDefine::GD_DROP_GROUP_CNT];		// ������Ʒ��

		cfg_DropInfo()
		{
			memset(this,0,sizeof(cfg_DropInfo));
		}
	};


	// ��Դ�����ڴ�����
	enum ASSETS_LOAD_TYPE
	{
		ALT_STATIC= 1,			// ��̬���ͣ���פ
		ALT_DYNAMIC				// ��̬���ͣ�������
	};


	// ��Դ����
	enum ASSETS_TYPE
	{
		AT_ORIGINAL = 1,		// ԭ����Դ png
		AT_PLIST,				// plist��Դ
		AT_ARMATURE,			// armature ������Դ
	};


	// ��Դ������Ϣ
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


	// ��Դ����Ϣ
	struct cfg_AssetsInfo
	{
		int id;
		ASSETS_LOAD_TYPE asset_load_type;				// ��Դ��������
		ASSETS_TYPE	asset_type;
		int asset_id;									// ������Դ��id
		std::string base_path;							// ��Դ�ļ���·��
		std::vector<std::string> files;					// ��Դ�ļ���

		cfg_AssetsInfo()
		{
			id = 0;
			asset_load_type = ALT_STATIC;
			asset_type = AT_ORIGINAL;
		}
	};


	// װ������






	// ѡ�������
	struct TargetSelectorFilter
	{
		TargetSelectorFilter()
		{
			select_mask = 0;
			filter_dis = 0;
			sel_num = 0;
			bAdjustY = false;
		}


		int select_mask;					// ѡ��obj���ͣ���hero,zombie����all
		float filter_dis;					// ѡ��Χ
		int sel_num;						// ѡ�����
		bool bAdjustY;						// ����GameEntity�Ѿ�ƫ����0.42H,��������ƫ�ƾ���Ҫ����
	};



	// �Զ����¼�
	struct sttCustomEvent
	{
		enum CE_TYPE
		{
			CE_VAL_MAX = 3,


			CE_BATTLE_REWARD_UPDATE = 1,			// ���������¼�
			CE_MAIN_UI_UDPATE,						// ��UIˢ��
			CE_MAIN_UI_ATTR_UPDATE,					// ˢ������
		};

		int ce_type;
		float _val[CE_VAL_MAX];

		sttCustomEvent()
		{
			memset(this,0,sizeof(sttCustomEvent));
		}
	};










	// ����ˢ��
	extern const char* REWARD_UPDATE_EVENT;
	extern const char* BATTLE_HERO_INFO_UPDATE_EVENT;
	extern const char* MAIN_UI_UPDATE_EVENT;
	//static const char* ANIMATION_EVENT = "_anim_event";
	extern const float MIN_FLOAT_VALUE;
	extern const char* ROLE_SAVE_FILE;


}

