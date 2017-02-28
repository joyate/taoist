#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


/*
 * ��Loadingʵ��
 *
 * ��������Ϊlayer����node���ݶ�
 */


class Loading : public Scene
{
public:
	Loading(void);
	~Loading(void);


	bool init();


	// ��ʼ��Ŀ�곡��id
	bool initTargetSceneId(int _sid);


	// ������
	void changeLoadingBg(const char* pic_l,const char* pic_r);


	//
	virtual void update(float delta) override;


	// ��ʼ��
	bool initConfig();


	//
	CREATE_FUNC(Loading);

protected:

	// ԭʼ��Դ�ص�
	void imageAsyncCallback(cocos2d::Texture2D* texture);
	
	// plist �ص�
	void plistImageAsyncCallback(cocos2d::Texture2D* texture);
	
	// �ݲ�ʵ��
	//void pvrPlistImageAsyncCallback(cocos2d::Texture2D* texture);
	
	// armature �ص�
	void armatureAsyncCallback(float f);


private:
	Layout* m_layout;

	// Ŀ�곡��id
	int m_to_scene_id;

	// ��ǰ���������Ŀ
	int m_curloaded_num;

	// ����һ���ﻹ��
	volatile int m_batch_num;

	// ��Ҫ�������Ŀ
	int m_total_load_num;

	// �Ƿ���������
	bool m_bLoading;
	// �Ƿ�Ҫ���Խ���
	bool m_loadingUpdate;

	// ��ǰҪ�������Դ
	std::list<int> m_asset_list;
};

