#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


/*
 * 新Loading实现
 *
 * 到底是做为layer还是node，暂定
 */


class Loading : public Scene
{
public:
	Loading(void);
	~Loading(void);


	bool init();


	// 初始化目标场景id
	bool initTargetSceneId(int _sid);


	// 换背景
	void changeLoadingBg(const char* pic_l,const char* pic_r);


	//
	virtual void update(float delta) override;


	// 初始化
	bool initConfig();


	//
	CREATE_FUNC(Loading);

protected:

	// 原始资源回调
	void imageAsyncCallback(cocos2d::Texture2D* texture);
	
	// plist 回调
	void plistImageAsyncCallback(cocos2d::Texture2D* texture);
	
	// 暂不实现
	//void pvrPlistImageAsyncCallback(cocos2d::Texture2D* texture);
	
	// armature 回调
	void armatureAsyncCallback(float f);


private:
	Layout* m_layout;

	// 目标场景id
	int m_to_scene_id;

	// 当前已载入的数目
	int m_curloaded_num;

	// 由于一批里还有
	volatile int m_batch_num;

	// 需要载入的数目
	int m_total_load_num;

	// 是否正在载入
	bool m_bLoading;
	// 是否要属性进度
	bool m_loadingUpdate;

	// 当前要载入的资源
	std::list<int> m_asset_list;
};

