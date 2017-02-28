#include "LoadingScene.h"
#include "cocostudio/CocoStudio.h"
#include "VisibleRect.h"
#include "ui/CocosGUI.h"
#include "BaseDefine.h"
#include "BattleScene.h"


using namespace cocostudio;
using namespace cocos2d::ui;

LoadingScene::LoadingScene(void):
	m_bloading(false)
{

	m_total_load_num = 100;
	m_curloaded_num = 0;

}


LoadingScene::~LoadingScene(void)
{
}



bool LoadingScene::init()
{
	
	auto _bg = LayerColor::create(Color4B(59,58,64,255));
	this->addChild(_bg);

	auto _loading_bg = Sprite::create("ui/loading_bg.jpg");
	auto pos = VisibleRect::center() - Vec2(0,100);
	_loading_bg->setPosition(pos);
	_loading_bg->setTag(TAG_LOADING_BG);
	this->addChild(_loading_bg);

	LoadingBar* loadingBar = LoadingBar::create("ui/loading_bar.png");
	loadingBar->setPosition(pos);
	loadingBar->setTag(TAG_LOADING_BAR);
	this->addChild(loadingBar);



	//
	auto load_ani = Armature::create("jiangshi");
	load_ani->getAnimation()->play("walk");
	
	//
	auto offset = Vec2(_loading_bg->getContentSize().width/2, - _loading_bg->getContentSize().height/2 - 5);
	auto ani_pos = pos - offset;
	
	load_ani->setPosition(ani_pos);
	load_ani->setScale(0.2f);
	load_ani->setTag(TAG_LOADING_ANI);
	addChild(load_ani);


	// 定时器事件
	scheduleUpdate();

	return true;
}



void LoadingScene::onEnter()
{

	Scene::onEnter();

	auto _bar = (LoadingBar*)this->getChildByTag(TAG_LOADING_BAR);
	_bar->setPercent(0.0f);

}





void LoadingScene::update( float delta )
{

	Scene::update(delta);

	

	
#if 0
	do 
	{
		/*	auto _pAni = (Armature*)this->getChildByTag(TAG_LOADING_ANI);
		_pAni->update(delta);*/


		if (m_bloading)
		{
			continue;
		}

		assert(m_curloaded_num < m_vec_loads.size());
		std::string& file_path = m_vec_loads[m_curloaded_num];
		size_t pos = file_path.find_last_of('.');
		if (pos != std::string::npos)
		{
			std::string file_ext = file_path.substr(pos);

			if (file_ext == ".png")
			{
				Director::getInstance()->getTextureCache()->addImageAsync(file_path,  
					CC_CALLBACK_1(LoadingScene::imageAsyncCallback, this));
				m_bloading = true;
			}

			else if (file_ext == ".plist")
			{
				Director::getInstance()->getTextureCache()->addImageAsync(file_path,  
					CC_CALLBACK_1(LoadingScene::plistImageAsyncCallback, this));
				m_bloading = true;
			}

			else if(file_ext == ".ccz")
			{
				Director::getInstance()->getTextureCache()->addImageAsync(file_ext,  
					CC_CALLBACK_1(LoadingScene::pvrPlistImageAsyncCallback, this));
				m_bloading = true;
			}

			else if(file_ext == "ExportJson")
			{
				ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(file_path,  
					this, schedule_selector(LoadingScene::jsonAsyncCallback));
				m_bloading = true;
			}

		}

	} while (m_curloaded_num < m_total_load_num);


	if (m_to_scene_id != -1)
	{
		auto next_scene = Scene::create();
		Director::getInstance()->pushScene(next_scene);
	}

#endif

	static int cnt = 0;
	cnt++;
	if (cnt > 10)
	{
		m_curloaded_num++;
	}


	float per = m_curloaded_num / (float)m_total_load_num;

	CCLOG("cur percent:%f",per);

	auto _loading_bar = (LoadingBar*)this->getChildByTag(TAG_LOADING_BAR);
	_loading_bar->setPercent(per*BaseDefine::HUNDRED_BASE);


	// 重设动画位置
	auto _loading_bg = (Sprite*)this->getChildByTag(TAG_LOADING_BG);
	Vec2 pos = _loading_bg->getPosition();
	
	auto offset = Vec2(_loading_bg->getContentSize().width/2, - _loading_bg->getContentSize().height/2 - 5);
	auto ani_pos = pos - offset;
	ani_pos.x += _loading_bg->getContentSize().width * per;

	auto pAni = (Armature*)this->getChildByTag(TAG_LOADING_ANI);
	pAni->setPosition(ani_pos);


	// ok了
	if (m_curloaded_num > BaseDefine::HUNDRED_BASE)
	{
		//m_curloaded_num = 0;
		auto scene = BattleScene::create();
		Director::getInstance()->replaceScene(scene);
	}

}

void LoadingScene::onExit()
{
	unscheduleUpdate();

	Scene::onExit();
}

void LoadingScene::imageAsyncCallback(cocos2d::Texture2D* texture)
{
	m_curloaded_num++;
	m_bloading = false;
}

void LoadingScene::plistImageAsyncCallback( cocos2d::Texture2D* texture )
{

	std::string& file_path = m_vec_loads[m_curloaded_num];
	size_t pos = file_path.find_last_of('.');
	if (pos != std::string::npos)
	{
		std::string file = file_path.substr(0,pos);

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(file.append("plist"), texture);  
		m_curloaded_num++;  
	}


	m_bloading = false;
}

void LoadingScene::jsonAsyncCallback( float f )
{
	m_curloaded_num++;
	m_bloading = false;
}

void LoadingScene::pvrPlistImageAsyncCallback( cocos2d::Texture2D* texture )
{

	std::string& file_path = m_vec_loads[m_curloaded_num];
	size_t pos = file_path.find_last_of('.');
	if (pos != std::string::npos)
	{
		std::string file = file_path.substr(0,pos);

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(file.append("pvr.ccz"), texture);  
		m_curloaded_num++;  
	}

	m_bloading = false;
}

