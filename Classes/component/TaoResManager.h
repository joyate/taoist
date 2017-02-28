#pragma once
#include "cocos2d.h"
#include "../GameDefine.h"

USING_NS_CC;


/*
 * 资源预处理管理器
 * 
 * 由于asset id 基本对应scene id来的，所以
 * asset id 与 scene id 一一对应。
 */



class TaoResManager
{
public:
	TaoResManager(void);
	~TaoResManager(void);



	static TaoResManager& getInstance();


	//
	void parseCfgAssetInfo(const GameDefine::cfg_AssetsInfo* _asset_info);


	// 获取_asset_id 对应的资源总数
	int getAssetCntByAssetId(int _asset_id)
	{
		if (m_asset_cnt.count(_asset_id) > 0)
		{
			return m_asset_cnt[_asset_id];
		}
		return 0;
	}



	//
	std::list<int> getAssetInfoByAssetId(int _asset_id)
	{
		if (m_assets_data.count(_asset_id) == 0)
		{
			throw "ASSET_NOT_FOUND";
		}
		return m_assets_data[_asset_id];
	}


private:
	static TaoResManager* s_inst;

	// asset_id => res_ids
	std::map<int,std::list<int> > m_assets_data;
	// asset_id -> res_cnt
	std::map<int,int> m_asset_cnt;
};

