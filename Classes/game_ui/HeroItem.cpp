#include "HeroItem.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"
#include "../data/LocalPlayer.h"
#include "../utility/Utility.h"

using namespace cocostudio;

HeroItem::HeroItem(void):
	m_layout(nullptr)
{
}


HeroItem::~HeroItem(void)
{
}





bool HeroItem::init()
{
	if (!Widget::init())
	{
		return false;
	}


	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("HeroItem/HeroItem.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);

	//
	auto img_val_bg = m_layout->getChildByName("img_val_bg");
	if (img_val_bg)
	{
		img_val_bg->setVisible(false);
	}

	//
	auto img_lvl_bg = m_layout->getChildByName("img_lvl_bg");
	if (img_lvl_bg)
	{
		img_lvl_bg->setVisible(false);
	}

	// 隐藏
	showStar(5,false);

	return true;
}



bool HeroItem::initFromCfgItemInfo(const GameDefine::cfg_Card* _card,  int mask )
{
	
	auto widget_pic = (ImageView*)m_layout->getChildByName("img_pic");
	if (widget_pic)
	{
		widget_pic->loadTexture(_card->szItemPic);
	}

	setFrameType(_card->item_lvl);


	// 要不要显示统御力
	if (mask & HI_MASK_CTRL)
	{

		auto img_val_bg = m_layout->getChildByName("img_val_bg");
		if (img_val_bg)
		{
			img_val_bg->setVisible(true);
		}

		auto bl_ctrl = (TextBMFont*)Utility::findWidget(m_layout,"img_val_bg/bl_val_cnt");
		if (bl_ctrl)
		{
			bl_ctrl->setString(StringUtils::format("%d",_card->req_ctrl));
		}
	}


	return true;
}

void HeroItem::setFrameType( int _lvl )
{
	if (!m_layout)
	{
		return;
	}

	auto widget_item = (ImageView*)Helper::seekWidgetByName(m_layout,"img_frame");
	if (widget_item)
	{
		char ch = 'E';
		std::string name = StringUtils::format("Common/107%c.png",ch-_lvl+1);
		widget_item->loadTexture(name);
	}
}



bool HeroItem::initFromInstId( int _inst_id, int mask /*= 0*/ )
{
	auto lp = LocalPlayer::getInstance();
	auto item_info = lp->m_bag.getItemById(_inst_id);


	const auto cfg_item_info = g_ItemInfoMgr.getObject(item_info->item_temp_id);
	if (!cfg_item_info)
	{
		CCLOG("card id %d no data",item_info->item_temp_id);
		return false;
	}


	if (cfg_item_info->item_type != IT_CARD)
	{
		CCLOG("[HeroItem::initFromInstId] type no compatable: %d",cfg_item_info->item_type);
		return false;
	}

	auto _card = (tCardInfo*)item_info;


	// 显示等级
	if (mask & HI_MASK_LVL)
	{
		auto img_lvl_bg = m_layout->getChildByName("img_lvl_bg");
		if (img_lvl_bg)
		{
			img_lvl_bg->setVisible(true);
		}

		auto bl_lvl = (TextBMFont*)Utility::findWidget(m_layout,"img_lvl_bg/bl_lvl");
		if (bl_lvl)
		{
			bl_lvl->setString(StringUtils::format("%d",_card->m_lvl));
		}
	}

	return initFromCfgItemInfo((GameDefine::cfg_Card*)cfg_item_info, mask);
}



void HeroItem::showStar( int _star_lvl,bool bShow /*= true*/ )
{
	for (int i = 1; i <= _star_lvl; i++)
	{
		auto img = (ImageView*)m_layout->getChildByName(StringUtils::format("star_%d",i));
		if (img)
		{
			img->setVisible(bShow);
		}
	}
}
