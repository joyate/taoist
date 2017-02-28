#include "Loading.h"
#include "../BaseDefine.h"
#include "cocostudio/CocoStudio.h"

#include "../frame/GameScene.h"
#include "../data/GameData.h"
#include "../component/TaoResManager.h"

using namespace cocostudio;

const char* TAG_LOADING = "loading";


// ---- 配置资源路径 --------
const char* ROLE_ATTR_PATH = "config/role_attr.json"; 
const char* SKILL_PATH = "config/skill.json";
const char* BUFF_PATH = "config/buff.json";
const char* BULLET_PATH = "config/bullet.json";
const char* ITEM_PATH = "config/item.json";
const char* CARD_PATH = "config/card.json";
const char* COPY_PATH = "config/copy.json";
const char* STAGE_PATH = "config/stage.json";
const char* DROP_PATH = "config/drop.json";
const char* MSG_PATH = "config/msg.json";
const char* GUIDE_PATH = "config/guide.json";
const char* DAILYTASK_PATH = "config/dailytask.json";
const char* ASSET_PATH = "config/res.json";
// ------------------------




Loading::Loading(void):
	m_layout(nullptr),
	m_curloaded_num(0),
	m_total_load_num(0),
	m_bLoading(false),
	m_loadingUpdate(true)
{
}


Loading::~Loading(void)
{
}

bool Loading::init()
{
	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("loading/loading.json");
	this->addChild(m_layout);

	

	// 定时器事件
	scheduleUpdate();
	
	return true;
}

void Loading::changeLoadingBg( const char* pic_l,const char* pic_r )
{

}

void Loading::update( float delta )
{

	Scene::update(delta);

	if (!m_asset_list.empty())
	{
		do 
		{	
			//
			if (m_loadingUpdate)
			{
				// 更新UI
				float per = m_curloaded_num / (float)m_total_load_num;
				CCLOG("cur percent:%f",per);

				auto loading = (LoadingBar*)Helper::seekWidgetByName(m_layout,TAG_LOADING);
				loading->setPercent(per * BaseDefine::HUNDRED_BASE);

				m_loadingUpdate = false;
			}


			if (m_bLoading)
			{
				break;
			}

			// 
			auto _iter_asset = m_asset_list.front();
			{
				auto asset_item = g_AssetInfoMgr.getObject(_iter_asset);
				if (!asset_item)
				{
					CCLOG("res id %d has no config",_iter_asset);
					continue;
				}

				// 子批处理
				m_batch_num = asset_item->files.size();

				for (auto _file : asset_item->files)
				{
					std::string full_path = asset_item->base_path + _file;
					switch (asset_item->asset_type)
					{
					case AT_ORIGINAL:
						{
							Director::getInstance()->getTextureCache()->addImageAsync(full_path,  
								CC_CALLBACK_1(Loading::imageAsyncCallback, this));
						}
						break;
					case AT_PLIST:
						{
							Director::getInstance()->getTextureCache()->addImageAsync(full_path,  
								CC_CALLBACK_1(Loading::plistImageAsyncCallback, this));
						}
						break;
					case AT_ARMATURE:
						{
							ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(full_path,  
								this, schedule_selector(Loading::armatureAsyncCallback));
						}
						break;
					default:
						break;
					}
				}
				m_bLoading = true;
			}

		} while (false);
	}

	// ok了
	if (m_curloaded_num >= m_total_load_num)
	{
		switch (m_to_scene_id)
		{
		case SceneMain::SCENE_ID:
			{
				auto scene = SceneMain::create();
				Director::getInstance()->replaceScene(scene);
			}
			break;
		default:
			{

			}
			break;
		}
		
	}

}


void Loading::imageAsyncCallback( cocos2d::Texture2D* texture )
{
	m_batch_num--;
	m_curloaded_num++;
	m_loadingUpdate = true;
	
	if (m_batch_num <= 0)
	{
		m_asset_list.pop_front();
		m_bLoading = false;
	}

}



void Loading::plistImageAsyncCallback( cocos2d::Texture2D* texture )
{
	auto as_id = m_asset_list.front();
	auto cfg_asset_info = g_AssetInfoMgr.getObject(as_id);
	if (cfg_asset_info)
	{
		//CC_ASSERT(cfg_asset_info->files.size() == 1);
		int cfg_asset_file_cnt = cfg_asset_info->files.size();
		std::string file_path = cfg_asset_info->base_path + cfg_asset_info->files[cfg_asset_file_cnt - m_batch_num];
		size_t pos = file_path.find_last_of('.');
		if (pos != std::string::npos)
		{
			std::string file = file_path.substr(0,pos+1);

			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(file.append("plist"), texture);  
			m_curloaded_num++;  
		}
	}

	m_loadingUpdate = true;
	m_batch_num--;
	if (m_batch_num <= 0)
	{
		m_asset_list.pop_front();
		m_bLoading = false;
	}
}


void Loading::armatureAsyncCallback( float f )
{
	m_curloaded_num++;
	m_loadingUpdate = true;
	m_batch_num--;
	if (m_batch_num <= 0)
	{
		m_asset_list.pop_front();
		m_bLoading = false;
	}
}





bool Loading::initConfig()
{
	// 配置载入
	if(!g_ObjInfoMgr.load(ROLE_ATTR_PATH))
	{
		CCLOG("obj info load failed");
		return false;
	}

	// 技能载入
	if (!g_SkillInfoMgr.load(SKILL_PATH))
	{
		CCLOG("skill info load failed");
		return false;
	}

	// buff 载入
	if (!g_BuffInfoMgr.load(BUFF_PATH))
	{
		CCLOG("buff info load failed");
		return false;
	}

	// 子弹载入
	if (!g_BulletInfoMgr.load(BULLET_PATH))
	{
		CCLOG("bullet info load failed");
		return false;
	}


	// 物品载入
	if (!g_ItemInfoMgr.load(ITEM_PATH))
	{
		CCLOG("item info load failed");
		return false;
	}


	// 卡牌载入
	if (!g_CardInfoMgr.load(CARD_PATH))
	{
		CCLOG("card info load failed");
		return false;
	}


	// 副本载入
	if (!g_CopyInfoMgr.load(COPY_PATH))
	{
		CCLOG("copy info load failed");
		return false;
	}


	// 关卡载入
	if (!g_StageInfoMgr.load(STAGE_PATH))
	{
		CCLOG("stage info load failed");
		return false;
	}

	// 掉落载入
	if (!g_DropInfoMgr.load(DROP_PATH))
	{
		CCLOG("drop info load failed");
		return false;
	}


	// 字符串信息载入
	if (!g_MsgInfoMgr.load(MSG_PATH))
	{
		CCLOG("msg info load failed");
		return false;
	}


	// 引导信息导入
	if (!g_GuideInfoMgr.load(GUIDE_PATH))
	{
		CCLOG("guide info load failed");
		return false;
	}


	// 日常任务载入
	if (!g_DailyTaskMgr.load(DAILYTASK_PATH))
	{
		CCLOG("daily task info load failed");
		return false;
	}


	// 资源配置信息
	if (!g_AssetInfoMgr.load(ASSET_PATH))
	{
		CCLOG("asset info load failed");
		return false;
	}


	return true; 
}



bool Loading::initTargetSceneId( int _sid )
{
	bool bRet = false;

	try 
	{
		m_asset_list = TaoResManager::getInstance().getAssetInfoByAssetId(_sid);
		if (m_asset_list.empty())
		{
			CCLOG("warning! asset empty");
		}

		m_total_load_num = TaoResManager::getInstance().getAssetCntByAssetId(_sid);
		
		m_to_scene_id = _sid;
		bRet = true;
	}
	catch(const std::string& e)
	{
		CCLOG("asset id %d loading error: %s",_sid,e.c_str());
	}

	return bRet;
}





