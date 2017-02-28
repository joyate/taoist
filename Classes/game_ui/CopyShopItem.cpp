#include "CopyShopItem.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"
#include "../data/LocalPlayer.h"
#include "../component/ObjFactory.h"

using namespace cocostudio;

CopyShopItem::CopyShopItem(void)
{
}


CopyShopItem::~CopyShopItem(void)
{
}



bool CopyShopItem::init()
{

	if (!Widget::init())
	{
		return false;
	}


	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("CopyShopItem/CopyShopItem.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);


#ifndef IMPL_IMAGE_EVENT
#define IMPL_IMAGE_EVENT(_name)	\
	do{\
	Widget* _name = (Widget*)Helper::seekWidgetByName(m_layout,#_name);		\
	_name->setTouchEnabled(true);											\
	_name->addTouchEventListener(CC_CALLBACK_2(CopyShopItem::touchEvent,this)); \
	}while(0)


	IMPL_IMAGE_EVENT(img_item_bg);


#undef IMPL_IMAGE_EVENT
#endif


	return true;
}

void CopyShopItem::touchEvent( Ref *pSender, Widget::TouchEventType type )
{

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			int si_id = this->getTag();
			if (si_id > 0)
			{

			}

			// 是不是已经卖掉了
			auto mask = (Widget*)Helper::seekWidgetByName(m_layout,"img_item_mask");
			if (mask && mask->isVisible())
			{
				CCLOG("this item %d has sold");
				return;
			}

			auto& copy_info = LocalPlayer::getInstance()->m_copy_info;
			auto _iter = copy_info.m_copy_shop_infos.find(m_copy_id);
			if( _iter == copy_info.m_copy_shop_infos.end())
			{
				CCLOG("copy id %d has no shop",m_copy_id);
				return;
			}

			
			auto item = ObjFactory::getInstance().createItem(si_id);
			if (item)
			{
				_iter->second.maskBought(m_item_index);

				auto& bag = LocalPlayer::getInstance()->m_bag;
				bag.addTempItem(si_id);
			}

			mask->setVisible(true);
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

}

bool CopyShopItem::initFromShopItemId( int _item_id )
{
	auto item = g_ItemInfoMgr.getObject(_item_id);
	if (!item)
	{
		CCLOG("item %d info not found",_item_id);
		return false;
	}

	auto item_name = (Text*)m_layout->getChildByName("item_name");
	if (item_name)
	{
		item_name->setString(item->szName);
		item_name->setFontName("fzyh.ttf");
		//item_name->setFontSize(20);
	}


	auto item_pic = (ImageView*)m_layout->getChildByName("img_item_pic");
	if (item_pic)
	{
		item_pic->loadTexture(item->szItemPic);
	}


	auto item_frame = (ImageView*)m_layout->getChildByName("img_item_frame");
	if (item_frame)
	{
		char ch = 'A' + item->item_lvl - 1;
		item_frame->loadTexture(StringUtils::format("Common/99%c.png",ch));
	}
	
	do 
	{

		auto pl_price = (Layout*)m_layout->getChildByName("pl_price");
		if (!pl_price)
		{
			break;
		}

		// 价格类型
		auto img_price_type = (ImageView*)Helper::seekWidgetByName(pl_price,"img_price_type");
		if (img_price_type)
		{
			switch (item->ct_type)
			{
			case CT_GOLD:
				{
					img_price_type->loadTexture("Common/102B.png");
				}
				break;
			case CT_DIAMOND:
				{
					img_price_type->loadTexture("Common/102A.png");
				}
				break;
			default:
				break;
			}
		}


		// 价格
		auto price = (TextBMFont*)Helper::seekWidgetByName(pl_price,"bl_price");
		if (price)
		{
			price->setString(StringUtils::format("%d",item->cost));
		}

	} while (false);
	

	return true;
}

void CopyShopItem::onEnter()
{
	Widget::onEnter();

	int item_id = this->getTag();
	if (item_id <= 0)
	{
		CCLOG("item id %d is invalid",item_id);
		return;
	}

	initFromShopItemId(item_id);
}




void CopyShopItem::setBoughtState( bool _bought )
{
	auto mask = (Widget*)Helper::seekWidgetByName(m_layout,"img_item_mask");
	if (mask)
	{
		mask->setVisible(_bought);
	}
}
