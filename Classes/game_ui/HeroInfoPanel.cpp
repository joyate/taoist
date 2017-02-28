#include "HeroInfoPanel.h"
#include "cocostudio/CocoStudio.h"
#include "../data/LocalPlayer.h"
#include "../utility/Utility.h"


using namespace cocostudio;

HeroInfoPanel::HeroInfoPanel(void):
	m_layout(nullptr)
{
}


HeroInfoPanel::~HeroInfoPanel(void)
{
}




bool HeroInfoPanel::init()
{
	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("HeroInfoPanel/HeroInfoPanel.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);

	
	// 隐藏星级
	auto head_pl = (Layout*)m_layout->getChildByName("head_pl");
	if (head_pl)
	{
		for (int i = 1; i <= GameDefine::GD_CARD_STAR_LVL_MAX; i++)
		{
			auto star = head_pl->getChildByName(StringUtils::format("star_%d",i));
			if (star)
			{
				star->setVisible(false);
			}
		}
	}


	return true;
}




bool HeroInfoPanel::initFromInstCardInfo(const GameDefine::tItemInfo* _item_info)
{

	// 检查类别
	auto cfg_item_info = g_ItemInfoMgr.getObject(_item_info->item_temp_id);
	if (!cfg_item_info || cfg_item_info->item_type != IT_CARD)
	{
		CCLOG("[HeroInfoPanel::initFromInstCardInfo] param type not compatible",_item_info->item_temp_id);
		return false;
	}


	const auto item_info = (const tCardInfo*)(_item_info);
	if (!item_info)
	{
		CCLOG("item type invalid");
		return false;
	}

	
	auto cfg_card_info = (cfg_Card*)cfg_item_info;
	auto obj_info = (cfg_Obj_Attr*)g_ObjInfoMgr.getObject(cfg_card_info->obj_id);
	if (!obj_info)
	{
		CCLOG("obj id %d no data",cfg_card_info->obj_id);
		return false;
	}

	// 设置星级
	setStarLvl(item_info->m_star);
	setHeadFrame(item_info->m_star);
	// 设置五行属性
	setFiveElement(cfg_card_info->cat);

	auto head_pl = (Layout*)m_layout->getChildByName("head_pl");
	
	// 头像
	auto hero_pic = (ImageView*)head_pl->getChildByName("hero_pic");
	if (hero_pic)
	{
		hero_pic->loadTexture(cfg_card_info->szItemPic);
	}


	// 等级
	auto bl_lvl = (TextBMFont*)m_layout->getChildByName("bl_lvl");
	if (bl_lvl)
	{
		bl_lvl->setString(StringUtils::format("lv %d",item_info->m_lvl));
	}


	// 名字
	auto label_name = (Text*)m_layout->getChildByName("label_name");
	if (label_name)
	{
		label_name->setString(cfg_card_info->szName);
		label_name->setFontName("fzyh.ttf");
		//label_name->setFontSize(32);
	}


	// 血量
	auto label_hp = (TextBMFont*)m_layout->getChildByName("label_hp");
	if (label_hp)
	{
		label_hp->setString(StringUtils::format("%d",obj_info->hp));
	}


	// 魂魄
	auto label_ghost = (TextBMFont*)m_layout->getChildByName("label_ghost");
	if (label_ghost)
	{
		label_ghost->setString(StringUtils::format("%d",obj_info->ghost));
	}


	// 统御力
	auto label_ctrl = (TextBMFont*)m_layout->getChildByName("label_ctrl");
	if (label_ctrl)
	{
		label_ctrl->setString(StringUtils::format("%d",obj_info->hero_ctrl));
	}


	return true;
}

void HeroInfoPanel::setStarLvl( int _lvl )
{

	auto head_pl = m_layout ? (Layout*)m_layout->getChildByName("head_pl") : nullptr;
	if (head_pl)
	{
		for (int i = 1; i <= GameDefine::GD_CARD_STAR_LVL_MAX; i++)
		{
			auto star = head_pl->getChildByName(StringUtils::format("star_%d",i));
			if (star)
			{
				star->setVisible(false);
			}
		}
	}
}


void HeroInfoPanel::setHeadFrame( int _lvl )
{
	auto head_pl = m_layout ? (Layout*)m_layout->getChildByName("head_pl") : nullptr;
	if (head_pl)
	{
		auto head_frame = (ImageView*)head_pl->getChildByName("head_frame");
		if (head_frame)
		{
			char ch = 'E';
			ch -= _lvl - 1;
			head_frame->loadTexture(StringUtils::format("Common/107%c.png",ch));
		}
	}
}



void HeroInfoPanel::setFiveElement( int fe_type )
{
	auto img_fe_type = (ImageView*)Utility::findWidget(m_layout,"img_fe_type");
	if (img_fe_type)
	{
		img_fe_type->loadTexture(StringUtils::format("Common/fe_type_%d.png",fe_type));
	}
}
