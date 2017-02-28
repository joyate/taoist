#include "CardTip.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"
#include "../data/MsgManager.h"

using namespace cocostudio;


CardTip::CardTip(void)
{
}


CardTip::~CardTip(void)
{
}



bool CardTip::init()
{
	if (!Widget::init())
	{
		return false;
	}


	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("CardTip/CardTip.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	m_layout->setBackGroundImageScale9Enabled(true);

	this->addChild(m_layout);
	

	return true;
}




void CardTip::initFrom( int _id,int _lvl /*= 1*/)
{
	auto item_info = (cfg_Card*)g_ItemInfoMgr.getObject(_id);
	if (!item_info)
	{
		CCLOG("item id %d has no data",_id);
		return;
	}

	auto obj_info = g_ObjInfoMgr.getObject(item_info->obj_id);
	if (!obj_info)
	{
		CCLOG("item id %d has no obj info,obj id: %d",_id,item_info->obj_id);
		return;
	}


	auto head_pic = (ImageView*)m_layout->getChildByName("head_pic");
	if (head_pic)
	{
		head_pic->loadTexture(item_info->szItemPic);
	}


	auto name = (Text*)m_layout->getChildByName("name");
	if (name && item_info->szName[0] != 0)
	{
		name->setFontName("fzyh.ttf");
		name->setColor(Color3B::YELLOW);
		name->setFontSize(25);
		name->setString(item_info->szName);
	}


	// 设置五行
	auto img_fe_type = (ImageView*)m_layout->getChildByName("img_fe_type");
	if (img_fe_type)
	{
		img_fe_type->loadTexture(StringUtils::format("Common/fe_type_%d.png",item_info->cat));
	}


	// 直接给值
#ifndef FORMAT_LABEL_INFO_BY_VALUE
#define FORMAT_LABEL_INFO_BY_VALUE(_ui_name,_fmt_id,_value,_font,_font_color,_font_size)		\
	do																							\
	{																							\
		auto ui_item = (Text*)m_layout->getChildByName(#_ui_name);								\
		if(ui_item)																				\
		{																						\
			ui_item->setFontName(_font);														\
			ui_item->setFontSize(_font_size);													\
			ui_item->setColor(_font_color);														\
			auto fmt = MsgManager::getInstance().getMsg(_fmt_id);								\
			ui_item->setString(StringUtils::format(fmt,_value));								\
		}																						\
	}while(false)

#endif


	// 值是根据MSG表取值
#ifndef FORMAT_LABEL_INFO_BY_MSG
#define FORMAT_LABEL_INFO_BY_MSG(_ui_name,_fmt_id,_msg_id,_font,_font_color,_font_size)			\
	do																							\
	{																							\
		auto ui_item = (Text*)m_layout->getChildByName(#_ui_name);								\
		if(ui_item)																				\
		{																						\
			ui_item->setFontName(_font);														\
			ui_item->setFontSize(_font_size);													\
			ui_item->setColor(_font_color);														\
			auto fmt = MsgManager::getInstance().getMsg(_fmt_id);								\
			auto _val = MsgManager::getInstance().getMsg(_msg_id);								\
			ui_item->setString(StringUtils::format(fmt,_val));									\
		}																						\
	}while(false)

#endif

	



	FORMAT_LABEL_INFO_BY_VALUE(lvl,MsgManager::CARDTIP_LVL_FMT,_lvl,"yuan.ttf",Color3B::GREEN,16);
	//auto fe_msg_id = MsgManager::CONST_FE_NAME_GOLD + item_info->cat - 1;
	//FORMAT_LABEL_INFO_BY_MSG(fe,MsgManager::CARDTIP_FE_FMT,fe_msg_id,"yuan.ttf",Color3B::GRAY,18);


	FORMAT_LABEL_INFO_BY_VALUE(hp,MsgManager::CARDTIP_HP_FMT,obj_info->hp,"yuan.ttf",Color3B::RED,18);
	FORMAT_LABEL_INFO_BY_VALUE(phys_atk,MsgManager::CARDTIP_PHYS_ATK_FMT,obj_info->phy_atk,"yuan.ttf",Color3B::ORANGE,18);
	FORMAT_LABEL_INFO_BY_VALUE(mag_atk,MsgManager::CARDTIP_MAG_ATK_FMT,obj_info->mag_atk,"yuan.ttf",Color3B::ORANGE,18);
	//FORMAT_LABEL_INFO_BY_VALUE(phys_cri,MsgManager::CARDTIP_PHYS_CRI_FMT,obj_info->phy_cri,"yuan.ttf",Color3B::ORANGE,18);
	FORMAT_LABEL_INFO_BY_VALUE(cri,MsgManager::CARDTIP_CRI_FMT,obj_info->atk_cri,"yuan.ttf",Color3B::ORANGE,18);



	if (obj_info->skill_ids[1] > 0)
	{
		auto sk_info = g_SkillInfoMgr.getObject(obj_info->skill_ids[1]);
		if (sk_info)
		{
			auto sk_name = (Text*)m_layout->getChildByName("sk_name");
			if (sk_name)
			{
				sk_name->setFontName("fzyh.ttf");
				sk_name->setFontSize(20);
				sk_name->setColor(Color3B::YELLOW);
				sk_name->setString(sk_info->sk_name);
			}
			

			auto sk_desc = (Text*)m_layout->getChildByName("sk_desc");
			if (sk_desc)
			{
				sk_desc->setFontName("yuan.ttf");
				sk_desc->setFontSize(16);
				sk_desc->setColor(Color3B::GRAY);
				//sk_desc->ignoreContentAdaptWithSize(true);
				sk_desc->setTextAreaSize(Size(this->getContentSize().width-30,48));
				//sk_desc->setContentSize(Size(this->getContentSize().width-30,48));
				sk_desc->setString(sk_info->szSkillDesc);
			}
		}
	}
	else
	{
		auto sk_name = (Text*)m_layout->getChildByName("sk_name");
		if (sk_name)
		{
			sk_name->setFontName("fzyh.ttf");
			sk_name->setFontSize(16);
			sk_name->setColor(Color3B::GRAY);
			sk_name->setString(MsgManager::getInstance().getMsg(MsgManager::NONE_SKILL_TIP));
		}

		//
		auto sk_desc = (Text*)m_layout->getChildByName("sk_desc");
		if (sk_desc)
		{
			sk_desc->setVisible(false);
		}
	}

}
