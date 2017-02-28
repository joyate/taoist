#pragma once
#include "utility/ObjectManager.h"
#include "../GameDefine.h"


using namespace GameDefine;


template<typename T>
class GameData : public ObjectManager<T>
{
public:
	virtual ~GameData()	{}

	//
	virtual bool load(const char* file_name);
};


// 对象表
typedef GameData<cfg_Obj_Attr> ObjInfoMgr;
extern ObjInfoMgr g_ObjInfoMgr;


// 提示信息数据表
typedef GameData<cfg_Msg> MsgInfoMgr;
extern MsgInfoMgr g_MsgInfoMgr;


typedef GameData<cfg_Skill_Info> SkillInfoMgr;
extern SkillInfoMgr g_SkillInfoMgr;


// buff数据表
typedef GameData<cfg_Buff_Data> BuffInfoMgr;
extern BuffInfoMgr g_BuffInfoMgr;


// 子弹数据表
typedef GameData<cfg_Bullet_Info> BulletInfoMgr;
extern BulletInfoMgr g_BulletInfoMgr;


// 物品数据表
typedef GameData<cfg_Item> ItemInfoMgr;
extern ItemInfoMgr g_ItemInfoMgr;


// 卡牌数据表
typedef GameData<cfg_Card> CardInfoMgr;
extern CardInfoMgr g_CardInfoMgr;


// 副本数据表
typedef GameData<cfg_Copy> CopyInfoMgr;
extern CopyInfoMgr g_CopyInfoMgr;


//
typedef GameData<cfg_Stage> StageInfoMgr;
extern StageInfoMgr g_StageInfoMgr;


// 装备数据表
typedef GameData<cfg_EquipItem> EquipInfoMgr;
extern EquipInfoMgr g_EquipInfoMgr;


// 掉落数据表
typedef GameData<cfg_DropInfo> DropInfoMgr;
extern DropInfoMgr g_DropInfoMgr;


// 字符串数据表
typedef GameData<cfg_Msg> MsgInfoMgr;
extern MsgInfoMgr g_MsgInfoMgr;

// 引导数据表
typedef GameData<cfg_Guide_Info> GuideInfoMgr;
extern GuideInfoMgr g_GuideInfoMgr;


// 每日任务
typedef GameData<cfg_DailyTask_Info> DailyTaskMgr;
extern DailyTaskMgr g_DailyTaskMgr;


// 资源配置信息
typedef GameData<cfg_AssetsInfo> AssetInfoMgr;
extern AssetInfoMgr g_AssetInfoMgr;