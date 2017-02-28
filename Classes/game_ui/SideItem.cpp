#include "SideItem.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"
#include "../data/LocalPlayer.h"

using namespace cocostudio;


SideItem::SideItem(void):
	m_inst_id(0),
	cached_obj_id(0),
	m_layout(nullptr),
	m_mask(nullptr),
	m_bMaskRunning(false)
{
}


SideItem::~SideItem(void)
{
}

bool SideItem::init()
{

	if (!Widget::init())
	{
		return false;
	}

	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("SideItem/SideItem.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);


#ifndef IMPL_IMAGE_EVENT
#define IMPL_IMAGE_EVENT(root,_name)	\
	do{\
	Widget* item = (Widget*)Helper::seekWidgetByName(root,#_name);			\
	item->setTouchEnabled(true);											\
	item->addTouchEventListener(CC_CALLBACK_2(SideItem::touchEvent,this));	\
	}while(0)


	auto pl_head_pic = (Widget*)m_layout->getChildByName("pl_head_pic");
	if (pl_head_pic)
	{
		//IMPL_IMAGE_EVENT(img_bg,img_pic);

		// Òþ²ØÐÇ¼¶
		for (int i = 0; i < 5; i++)
		{
			std::string name = StringUtils::format("img_star_%d",i+1);
			auto star_item = (Widget*)pl_head_pic->getChildByName(name);
			if (star_item)
			{
				star_item->setVisible(false);
			}
		}
	}

	
#undef IMPL_IMAGE_EVENT
#endif

	return true;
}




void SideItem::touchEvent( Ref *pSender, Widget::TouchEventType type )
{






}




bool SideItem::initFromCardInstance( int inst_id )
{
	auto lp = LocalPlayer::getInstance();

	auto item = lp->m_bag.getItemById(inst_id);
	if (!item)
	{
		return false;
	}
	 
	auto cfg_card_info = (cfg_Card*)g_ItemInfoMgr.getObject(item->item_temp_id);
	m_inst_id= inst_id;
	cached_obj_id = cfg_card_info->obj_id;

	// ÉèÖÃÐÇ¼¶
	setStarLvl(cfg_card_info->item_lvl);

	// ÉèÖÃÍ·Ïñ
	auto pl_head_pic = (Widget*)m_layout->getChildByName("pl_head_pic");
	auto img_pic = (ImageView*)pl_head_pic->getChildByName("img_pic");
	if (img_pic)
	{
		img_pic->loadTexture(cfg_card_info->szItemPic);
		img_pic->setOpacity(80);

		m_mask = ProgressTimer::create(Sprite::create(cfg_card_info->szItemPic));
		m_mask->setType(ProgressTimer::Type::BAR);
		m_mask->setBarChangeRate(Vec2(0,1));
		m_mask->setMidpoint(Vec2(0,1));
		m_mask->setPercentage(100);

		m_mask->setPosition(img_pic->getPosition());
		pl_head_pic->addChild(m_mask,img_pic->getLocalZOrder()+1);
	}

	adjustLocalOrder(m_mask->getLocalZOrder());
	return true;
}

void SideItem::setStarLvl( int _lvl )
{
	auto pl_head_pic = (Widget*)m_layout->getChildByName("pl_head_pic");
	if (!pl_head_pic)
		return;

	for (int i = 0; i < _lvl; i++)
	{
		std::string name = StringUtils::format("img_star_%d",i+1);
		auto star_item = (Widget*)pl_head_pic->getChildByName(name);
		if (star_item)
		{
			star_item->setVisible(true);
		}
	}

	// ÉèÖÃ±ß¿ò
	char ch = 'E';
	ch -= _lvl - 1;
	auto item_frame = (ImageView*)pl_head_pic->getChildByName("img_pic_frame");
	if (item_frame)
	{
		item_frame->loadTexture(StringUtils::format("Common/107%c.png",ch));
	}

}

void SideItem::onEnterColddown()
{
	if (m_bMaskRunning)
	{
		CCLOG("side item is colddown");
		return;
	}


	auto obj_info = g_ObjInfoMgr.getObject(cached_obj_id);
	if (!obj_info)
	{
		CCLOG("obj id %d info not found",cached_obj_id);
		return;
	}

	m_mask->runAction(Sequence::create(ProgressTo::create(0,0),
		ProgressTo::create(obj_info->buy_cd,100.0f),
		CallFunc::create( CC_CALLBACK_0(SideItem::cdover,this)),
		nullptr));

	m_bMaskRunning = true;
}


void SideItem::cdover()
{
	m_bMaskRunning = false;
}



void SideItem::adjustLocalOrder(int base_order)
{
	
	auto pl_head_pic = (Widget*)m_layout->getChildByName("pl_head_pic");
	if (pl_head_pic)
	{
		for (int i = 1; i < 5; i++)
		{
			std::string name = StringUtils::format("img_star_%d",i);
			auto star_item = (Widget*)pl_head_pic->getChildByName(name);

			if (star_item)
			{
				star_item->setLocalZOrder(base_order++);
			}
		}


		auto img_pic_frame = (Widget*)pl_head_pic->getChildByName("img_pic_frame");
		if (img_pic_frame)
		{
			img_pic_frame->setLocalZOrder(base_order++);
		}
	}
}

void SideItem::setGhost( int _ghost,const Color3B& _color )
{
	auto label_price = (Text*)m_layout->getChildByName("label_price");
	if (label_price)
	{
		label_price->setFontName("brlnsr.ttf");
		label_price->setFontSize(32);
		label_price->setColor(_color);
		label_price->setString(StringUtils::format("%d",_ghost));
	}
}



void SideItem::updateGhostState( int _cur_ghost )
{
	auto obj_info = g_ObjInfoMgr.getObject(cached_obj_id);
	if (!obj_info)
	{
		CCLOG("obj id %d has no data",cached_obj_id);
		return;
	}

	if (obj_info->ghost > _cur_ghost)
	{
		setGhost(obj_info->ghost,Color3B::RED);
	}
	else
	{
		setGhost(obj_info->ghost,Color3B::GREEN);
	}
}

