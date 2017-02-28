#pragma once
#include "cocos2d.h"

USING_NS_CC;



class LoadingScene : public Scene
{
public:
	LoadingScene(void);
	~LoadingScene(void);


	enum 
	{
		TAG_LOADING_BG = 3,
		TAG_LOADING_BAR = 1,
		TAG_LOADING_ANI = 2,
	};


	bool init();
	void setTransSceneIDs(int _from_scene_id = -1,int _to_scene_id = -1);


	virtual void onEnter();
	virtual void update(float delta);
	virtual void onExit();


	CREATE_FUNC(LoadingScene);


protected:

	// 异步加载回调函数
	void imageAsyncCallback(cocos2d::Texture2D* texture);
	void plistImageAsyncCallback(cocos2d::Texture2D* texture);
	void pvrPlistImageAsyncCallback(cocos2d::Texture2D* texture);
	void jsonAsyncCallback(float f);




private:
	int m_from_scene_id;	// 来自场景ID,释放资源
	int m_to_scene_id;		// 目标场景ID,加载资源

	bool m_bloading;
	size_t m_curloaded_num;
	int m_total_load_num;


	std::vector<std::string> m_vec_loads;

};

