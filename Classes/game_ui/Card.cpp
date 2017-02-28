#include "Card.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"

using namespace cocostudio;


UICard::UICard(void):
	m_layout(nullptr)
{
}


UICard::~UICard(void)
{
}

bool UICard::init()
{

	if (!Widget::init())
	{
		return false;
	}


	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("CardInfo/CardInfo.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);



	return true;
}

void UICard::setStarLvl( int _star_lvl )
{
	if (!m_layout)
	{
		CCLOG("no layout");
		return;
	}

	for (int i = 1; i <= _star_lvl; i++)
	{
		std::string star = StringUtils::format("img_star_%d",i);
		auto img = (ImageView*)m_layout->getChildByName(star.c_str());

		if (!img)
		{
			CCLOG("has no star component %s",star.c_str());
			break;
		}

		img->loadTexture("Common/79.png");
	}
}

void UICard::setCardLvl( int _card_lvl )
{
	// 卡默认是绿色
	/*if (_card_lvl != CARD_COLOR_GREEN)
	{
	auto img_frame = (ImageView*)m_layout->getChildByName("img_card_frame");
	if (img_frame)
	{
	std::string card_file = StringUtils::format("Common/card_frame_%d.png",1);
	img_frame->loadTexture(card_file);
	}
	}*/
}


void UICard::setCardImage( const char* sz_file_name )
{
	if (!sz_file_name)
	{
		CCLOG("card file null");
		return;
	}

	auto img_pic = (ImageView*)m_layout->getChildByName("img_card_pic");
	if (img_pic)
	{
		img_pic->loadTexture(sz_file_name);
	}
}


void UICard::onEnter()
{
	Widget::onEnter();

	int card_id = this->getTag();
	if (card_id < 0)
	{
		CCLOG("card id %d is invalid",card_id);
		return;
	}


	auto card_info = (cfg_Card*)g_ItemInfoMgr.getObject(card_id);
	if (card_info)
	{
		// 设置卡配对的图
		if (card_info->card_pic[0])
		{
			setCardImage(card_info->card_pic);
		}


		// 等级
		if (card_info->item_lvl > 0)
		{
			setCardLvl(card_info->item_lvl);

			// 这里注意
			setStarLvl(card_info->item_lvl);
		}

		// 需求
		setCardGhostReq(card_info->exchange_ghost);
		//setCardPrestigeReq(card_info->exchange_prestige);

	}
	
}

void UICard::setCardGhostReq( int _val )
{	
	auto label_ghost = (TextBMFont*)m_layout->getChildByName("bl_ghost");
	if (label_ghost)
	{
		label_ghost->setString(StringUtils::format("%d",_val));
	}
}

//void Card::setCardPrestigeReq( int _val )
//{
//	auto sub_item = m_layout->getChildByName("img_prestige");
//	if (sub_item)
//	{
//		auto label_prestige = (TextBMFont*)sub_item->getChildByName("label_prestige");
//		if (label_prestige)
//		{
//			label_prestige->setString(StringUtils::format("%d",_val));
//		}
//	}
//}

