#include "HeroPanel.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"
#include "../data/LocalPlayer.h"
#include "HeroInfoPanel.h"
#include "../utility/Utility.h"
#include "HeroInfoMain.h"


using namespace cocostudio;




HeroPanel::HeroPanel(void):
	m_show_type(HP_SHOWTYPE_HERO)
{
}


HeroPanel::~HeroPanel(void)
{
}



bool HeroPanel::init()
{
	if (!Widget::init())
	{
		return false;
	}

	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("HeroPanel/HeroPanel.ExportJson");
	auto layout_main = (Layout*)m_layout->getChildByName("pl_main");
	if (layout_main)
	{
		layout_main->setBackGroundImageScale9Enabled(true);
	}

	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);

	//	
	Utility::registerTouchEvent(m_layout,"pl_root/btn_close",CC_CALLBACK_2(HeroPanel::touchEvent,this));
	Utility::registerTouchEvent(m_layout,"pl_root/img_hero",CC_CALLBACK_2(HeroPanel::touchEvent,this));
	Utility::registerTouchEvent(m_layout,"pl_root/img_soldier",CC_CALLBACK_2(HeroPanel::touchEvent,this));

	return updatePanelInfo(m_show_type);
}

void HeroPanel::touchEvent( Ref *pSender, Widget::TouchEventType type )
{
	auto wg = (Widget*)pSender;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			int cur_show_type = 0;

			if (wg->getName() == "btn_close")
			{
				this->removeFromParent();
			}
			else if(wg->getName() == "img_hero")
			{
				cur_show_type = HP_SHOWTYPE_HERO;
			}
			else if(wg->getName() == "img_soldier")
			{
				cur_show_type = HP_SHOWTYPE_ARMY;
			}

			// 有改动，刷新
			if (cur_show_type && m_show_type != cur_show_type)
			{		
				updatePanelInfo(cur_show_type);	
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}


bool HeroPanel::updatePanelInfo(int cur_show_type)
{
	switch (cur_show_type)
	{
	case HP_SHOWTYPE_ARMY:
		{
			auto img = (ImageView*)Utility::findWidget(m_layout,"pl_root/img_hero");
			if (img)
			{
				img->loadTexture("HeroPanel/img_hero_nor.png");
			}

			img = (ImageView*)Utility::findWidget(m_layout,"pl_root/img_soldier");
			if (img)
			{
				img->loadTexture("HeroPanel/img_soldier_act.png");
			}
		}
		break;
	case HP_SHOWTYPE_HERO:
		{
			auto img = (ImageView*)Utility::findWidget(m_layout,"pl_root/img_hero");
			if (img)
			{
				img->loadTexture("img_hero_act.png",Widget::TextureResType::PLIST);
			}

			img = (ImageView*)Utility::findWidget(m_layout,"pl_root/img_soldier");
			if (img)
			{
				img->loadTexture("img_soldier_nor.png",Widget::TextureResType::PLIST);
			}
		}
		break;
	default:
		break;
	}
	m_show_type = cur_show_type;


	auto lv_cards = (ListView*)Utility::findWidget(m_layout,"pl_root/lv_items");
	if (!lv_cards)
	{
		CCLOG("hero panel pl_heros error");
		return false;
	}
	lv_cards->removeAllChildren();

	Layout* line_layout = nullptr;
	int nCount = 0;

	const tBagInfo& _bag = LocalPlayer::getInstance()->m_bag.getBagInfo();
	for (tBagInfo::const_item_iter _iter = _bag.m_items.begin(); _iter != _bag.m_items.end(); _iter++)
	{
		CC_ASSERT(_iter->second->item_temp_id > 0);
		auto item_info = g_ItemInfoMgr.getObject(_iter->second->item_temp_id);
		CC_ASSERT(item_info);
		if (item_info)
		{
			if (item_info->item_type != IT_CARD)
			{
				continue;
			}


			auto card_info = (cfg_Card*)item_info;
			if (card_info->arm_type != m_show_type)
			{
				continue;
			}


			if (nCount++%LINE_COUNT_MAX == 0)
			{
				line_layout = Layout::create();
				line_layout->setLayoutType(LayoutType::HORIZONTAL);
				line_layout->setContentSize(Size(770,120));
				lv_cards->addChild(line_layout);
			}
			
			auto hero_info_panel = HeroInfoPanel::create();
			hero_info_panel->initFromInstCardInfo(_iter->second);
			hero_info_panel->setTag(_iter->first);

			hero_info_panel->setTouchEnabled(true);
			hero_info_panel->addTouchEventListener(CC_CALLBACK_2(HeroPanel::cardTouchEvent,this));

			/*auto llp = LinearLayoutParameter::create();
			llp->setMargin(Margin(5,5,5,5));
			hero_info_panel->setLayoutParameter(llp);*/


			if(line_layout)
				line_layout->addChild(hero_info_panel);
		}
	}


	return true;
}




void HeroPanel::cardTouchEvent( Ref *pSender, Widget::TouchEventType type )
{
	auto hip = (HeroInfoPanel*)pSender;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			auto win_size = Director::getInstance()->getWinSize();

			auto inst_id = hip->getTag();

			auto him = HeroInfoMain::create();
			him->initWithInstId(inst_id);
			him->setPosition(Vec2(win_size.width*2/3,win_size.height/2));
			this->getParent()->addChild(him);
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}



