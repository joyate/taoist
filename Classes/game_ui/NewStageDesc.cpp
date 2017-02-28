#include "NewStageDesc.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"
#include "../data/LocalPlayer.h"
#include "HeroItem.h"
#include "CardTip.h"
#include "Item.h"
#include "StageArmySel.h"

using namespace cocostudio;



NewStageDesc::NewStageDesc(void):
	m_layout(nullptr),
	m_stage_id(0)
{
}


NewStageDesc::~NewStageDesc(void)
{
}



bool NewStageDesc::init()
{
	if (!Widget::init())
	{
		return false;
	}


	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("StageDesc/StageDesc.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);


	return true;
}




bool NewStageDesc::initFromStageId( int _stage_id )
{
	auto stage_info = g_StageInfoMgr.getObject(_stage_id);
	if (!stage_info)
	{
		CCLOG("stage id %d has no data",_stage_id);
		return false;
	}

	m_stage_id = _stage_id;

	auto panel_root = m_layout->getChildByName("Panel_1");
	if (panel_root)
	{
		// ÉèÖÃÏûºÄ
		auto img_phys_cost = panel_root->getChildByName("img_phys_cost");
		if (img_phys_cost)
		{
			auto bl_phys_cost = (TextBMFont*)img_phys_cost->getChildByName("bl_phys_cost");
			if (bl_phys_cost)
			{
				bl_phys_cost->setString(StringUtils::format("%d",stage_info->phys_cost));
			}
		}


		//ÉèÖÃ¹ÖÎï
		auto lv_enemies = (ListView*)panel_root->getChildByName("lv_enemies");
		if (lv_enemies)
		{
			
			for (int i = 1; i < stage_info->monsters[0]; i++)
			{

				const auto _card = (GameDefine::cfg_Card*)g_ItemInfoMgr.getObject(stage_info->monsters[i]);
				if (!_card)
				{
					CCLOG("card id %d no config",stage_info->monsters[i]);
					continue;
				}

				auto item = HeroItem::create();
				item->initFromCfgItemInfo(_card,0);
				item->setTag(stage_info->monsters[i]);

				item->setTouchEnabled(true);
				item->addTouchEventListener(CC_CALLBACK_2(NewStageDesc::showDetailTip,this));

				lv_enemies->addChild(item);

			}
		}


		// ÉèÖÃµôÂä
		auto pl_drops = panel_root->getChildByName("pl_drops");
		if (pl_drops)
		{
			auto lv_drops = (ListView*)pl_drops->getChildByName("lv_drops");
			for (int i = 0; i < stage_info->drops[0]; i++)
			{
				auto item_info = g_ItemInfoMgr.getObject(stage_info->drops[i+1]);
				if (item_info)
				{
					auto item = UIItem::create();
					item->initFromItemTempId(item_info->id);

					lv_drops->addChild(item);
				}

			}
		}
		

		// ÉèÖÃÃèÊö
		auto lb_stage_desc = (Text*)panel_root->getChildByName("lb_stage_desc");
		if (lb_stage_desc)
		{
			lb_stage_desc->setString(stage_info->szDesc);
		}


	}

	return true;
}



void NewStageDesc::showDetailTip( Ref *pSender, Widget::TouchEventType type )
{
	auto _item = (HeroItem*)pSender;
	int _item_id = _item->getTag();

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		{
			auto card_tip = CardTip::create();
			card_tip->initFrom(_item_id);
			card_tip->setTag(TAG_TIP_NODE);

			Vec2 item_pos = _item->convertToWorldSpace(Vec2(0,0));
			Vec2 pos = this->convertToNodeSpace(item_pos);
			card_tip->setPosition(pos + Vec2(_item->getContentSize().width/2 + card_tip->getContentSize().width/2,-(card_tip->getContentSize().height/3)));

			this->addChild(card_tip);
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			auto card_tip = (CardTip*)this->getChildByTag(TAG_TIP_NODE);
			if (card_tip)
			{
				card_tip->removeFromParent();
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		{
			auto card_tip = (CardTip*)this->getChildByTag(TAG_TIP_NODE);
			if (card_tip)
			{
				card_tip->removeFromParent();
			}
		}
		break;
	default:
		break;
	}
}
