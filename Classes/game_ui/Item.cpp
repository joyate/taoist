#include "Item.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"
#include "../data/LocalPlayer.h"

using namespace cocostudio;



UIItem::UIItem(void)
{
}


UIItem::~UIItem(void)
{
}


bool UIItem::init()
{

	if (!Widget::init())
	{
		return false;
	}


	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("Item/Item.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);


	// 隐藏星级
	for (int i = 0; i < GameDefine::GD_CARD_STAR_LVL_MAX; i++)
	{
		std::string star_name = StringUtils::format("img_star_%d",i+1);
		auto star = Helper::seekWidgetByName(m_layout,star_name);

		if (star)
		{
			star->setVisible(false);
		}
	}


	return true;
}



bool UIItem::initFromItemTempId( int _item_id,  int _item_cnt /*= 1*/)
{

	auto item_info = g_ItemInfoMgr.getObject(_item_id);
	if (!item_info)
	{
		CCLOG("item template id %d not found",_item_id);
		return false;
	}


	// 命名规则要改
	auto img_frame = (ImageView*)m_layout->getChildByName("img_frame");
	if (img_frame)
	{
		if(item_info->item_type == IT_CARD)
		{
			char ch = 'E';
			ch -= item_info->item_lvl - 1;
			std::string img_frame_name = StringUtils::format("Common/107%c.png",ch);
			img_frame->loadTexture(img_frame_name);
		}
		else
		{
			char ch = 'A';
			ch += item_info->item_lvl - 1;
			std::string img_frame_name = StringUtils::format("Common/99%c.png",ch);
			img_frame->loadTexture(img_frame_name);
		}
	}


	//
	auto item_pic = (ImageView*)m_layout->getChildByName("img_pic");
	if (item_pic)
	{
		item_pic->loadTexture(item_info->szItemPic);
	}

	//
	setStarLvl(item_info->item_lvl);
	setItemCnt(_item_cnt);

	return true;
}


bool UIItem::initFromItemId( int _item_id)
{
	auto lp = LocalPlayer::getInstance();
	auto item_info = lp->m_bag.getItemById(_item_id);


	return initFromItemTempId(item_info->item_temp_id,item_info->item_num);
}




void UIItem::setStarLvl( int _lvl )
{
	for (int i = 0; i < _lvl; i++)
	{
		std::string star_name = StringUtils::format("img_star_%d",i+1);
		auto star = Helper::seekWidgetByName(m_layout,star_name);

		if (star)
		{
			star->setVisible(true);
		}
	}
}



void UIItem::setItemCnt( int _cnt )
{

	auto label_cnt = (TextBMFont*)m_layout->getChildByName("label_cnt");
	if (label_cnt)
	{
		if (_cnt <= 1)
		{
			label_cnt->setVisible(false);
		}
		else
		{
			label_cnt->setString(StringUtils::format("%d",_cnt));
			label_cnt->setVisible(true);
		}	
	}
}


