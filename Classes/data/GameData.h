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


// �����
typedef GameData<cfg_Obj_Attr> ObjInfoMgr;
extern ObjInfoMgr g_ObjInfoMgr;


// ��ʾ��Ϣ���ݱ�
typedef GameData<cfg_Msg> MsgInfoMgr;
extern MsgInfoMgr g_MsgInfoMgr;


typedef GameData<cfg_Skill_Info> SkillInfoMgr;
extern SkillInfoMgr g_SkillInfoMgr;


// buff���ݱ�
typedef GameData<cfg_Buff_Data> BuffInfoMgr;
extern BuffInfoMgr g_BuffInfoMgr;


// �ӵ����ݱ�
typedef GameData<cfg_Bullet_Info> BulletInfoMgr;
extern BulletInfoMgr g_BulletInfoMgr;


// ��Ʒ���ݱ�
typedef GameData<cfg_Item> ItemInfoMgr;
extern ItemInfoMgr g_ItemInfoMgr;


// �������ݱ�
typedef GameData<cfg_Card> CardInfoMgr;
extern CardInfoMgr g_CardInfoMgr;


// �������ݱ�
typedef GameData<cfg_Copy> CopyInfoMgr;
extern CopyInfoMgr g_CopyInfoMgr;


//
typedef GameData<cfg_Stage> StageInfoMgr;
extern StageInfoMgr g_StageInfoMgr;


// װ�����ݱ�
typedef GameData<cfg_EquipItem> EquipInfoMgr;
extern EquipInfoMgr g_EquipInfoMgr;


// �������ݱ�
typedef GameData<cfg_DropInfo> DropInfoMgr;
extern DropInfoMgr g_DropInfoMgr;


// �ַ������ݱ�
typedef GameData<cfg_Msg> MsgInfoMgr;
extern MsgInfoMgr g_MsgInfoMgr;

// �������ݱ�
typedef GameData<cfg_Guide_Info> GuideInfoMgr;
extern GuideInfoMgr g_GuideInfoMgr;


// ÿ������
typedef GameData<cfg_DailyTask_Info> DailyTaskMgr;
extern DailyTaskMgr g_DailyTaskMgr;


// ��Դ������Ϣ
typedef GameData<cfg_AssetsInfo> AssetInfoMgr;
extern AssetInfoMgr g_AssetInfoMgr;