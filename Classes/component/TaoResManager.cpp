#include "TaoResManager.h"


TaoResManager* TaoResManager::s_inst = nullptr;


TaoResManager::TaoResManager(void)
{
}


TaoResManager::~TaoResManager(void)
{
}


TaoResManager& TaoResManager::getInstance()
{
	if (!s_inst)
	{
		s_inst = new TaoResManager();
	}

	return *s_inst;
}


void TaoResManager::parseCfgAssetInfo( const GameDefine::cfg_AssetsInfo* _asset_info )
{
	if (!_asset_info)
	{
		return;
	}

	if (_asset_info->asset_type != GameDefine::AT_ARMATURE)
	{
		m_assets_data[_asset_info->asset_id].push_front(_asset_info->id);
		m_asset_cnt[_asset_info->asset_id] += _asset_info->files.size();
	}
	else
	{
		m_assets_data[_asset_info->asset_id].push_back(_asset_info->id);
		m_asset_cnt[_asset_info->asset_id] += _asset_info->files.size();
	}
}


