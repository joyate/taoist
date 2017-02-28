#include "MainUI.h"
#include "cocostudio/CocoStudio.h"
#include "../ui_ext/StateMenuItemSprite.h"
#include "../ui_ext/PokerMenu.h"
#include "../data/LocalPlayer.h"
#include "HeroPanel.h"
#include "BagPanel.h"
#include "HeroInfoMain.h"
#include "TaskPanel.h"
#include "../component/MsgBox.h"
#include "../data/MsgManager.h"

#include "../ui_ext/TipUI.h"
#include "../component/GuideFilterMgr.h"
#include "../utility/Utility.h"

using namespace cocostudio;




MainUI::MainUI(void):
	m_bShow(true),
	m_layout(nullptr)
{
}


MainUI::~MainUI(void)
{
}




bool MainUI::init()
{

	if (!Layer::init())
	{
		return false;
	}

	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("MainUI/MainUI.ExportJson");
	this->addChild(m_layout);


	Button* btn_menu = (Button*)Helper::seekWidgetByName(m_layout,"btn_menu");
	btn_menu->addTouchEventListener(CC_CALLBACK_2(MainUI::touchEvent,this));


	Size win_size = Director::getInstance()->getWinSize();

	Vector<MenuItem*> vec_menuitems;

	// 下面的主功能面板
	for (int i = 23, j = 0; i <= 32; i += 2, j++ )
	{
		auto pic_state = Sprite::create("MainUI/38.png");

		//
		std::string pic_name = StringUtils::format("MainUI/%d.png",i);
		auto pic_select = Sprite::create(pic_name.c_str());
		//
		pic_name = StringUtils::format("MainUI/%d.png",i+1);
		auto pic_normal = Sprite::create(pic_name.c_str());

		//
		auto item1 = StateMenuItemSprite::create(pic_normal, pic_select, pic_state, CC_CALLBACK_1(MainUI::MainFuncCallback, this));
		item1->setTag(TAG_MENU_ITEM_HERO + j);
		item1->setActiveState(i%2 == 1);
		vec_menuitems.pushBack(item1);
	}
	

	auto menu = PokerMenu::createWithArray(vec_menuitems);
	menu->setPosition(Vec2(win_size.width - btn_menu->getContentSize().width,0));
	menu->setTag(TAG_MAIN_FUNC_MENU);
	menu->setHidePosition(btn_menu->getPosition());
	this->addChild(menu);


	m_ui_update_listener = EventListenerCustom::create(GameDefine::MAIN_UI_UPDATE_EVENT,
		[=](EventCustom* ec) {

			auto ce = (GameDefine::sttCustomEvent*)ec->getUserData();
			if (ce)
			{
				switch (ce->ce_type)
				{
				case GameDefine::sttCustomEvent::CE_MAIN_UI_UDPATE:
					{
						auto btn_item = (StateMenuItemSprite*)menu->getChildByTag(TAG_MENU_ITEM_HERO + ce->_val[0]);
						if (btn_item)
						{
							btn_item->runAction(Sequence::create(ScaleBy::create(0.2f,0.8f),ScaleTo::create(0.2f,1.0f),nullptr));
							GuideFilterMgr::getInstance().checkGuideFilter(GuideFilterMgr::GFN_ROLE_INTRODUCE);
						}
					}
					break;
				case GameDefine::sttCustomEvent::CE_MAIN_UI_ATTR_UPDATE:
					{
						initFromPlayer(LocalPlayer::getInstance());
					}
					break;
				default:
					break;
				}

			}

	});
	_eventDispatcher->addEventListenerWithFixedPriority(m_ui_update_listener,1);

	return true;
}

void MainUI::MainFuncCallback( Ref* _ref )
{
	auto menu_item = (StateMenuItemSprite*)_ref;
	auto win_size = Director::getInstance()->getWinSize();

	switch (menu_item->getTag())
	{
	case TAG_MENU_ITEM_HERO:
		{
			auto hp = HeroPanel::create();
			hp->setPosition(Vec2(win_size.width/2,win_size.height/2));
			this->addChild(hp);
		}
		break;
	case TAG_MENU_ITEM_BAG:
		{
			auto bp = BagPanel::create();
			bp->initFromPlayer();
			bp->setPosition(Vec2(win_size.width/2,win_size.height/2));
			this->addChild(bp);
		}
		break;
	case TAG_MENU_ITEM_UNK_1:
		{
			/*auto hm = HeroInfoMain::create();
			hm->setPosition(Vec2(win_size.width/2 + hm->getContentSize().width/3,win_size.height/2));
			this->addChild(hm);*/

			auto tip = MsgBox::create();
			tip->initMsg(MsgBox::MB_TYPE_TIP,0,MsgManager::FUNCTION_NOT_OPEN);
			this->addChild(tip);
		}
		break;
	case TAG_MENU_ITEM_UNK_2:
		{
//			auto tip = TipUI::create("123.png",Rect(20,20,20,20),250);
//#ifdef _DEBUG
//			tip->testTipUI();
//#endif
//			tip->setPosition(Vec2(win_size.width/2,win_size.height/2));
//			this->addChild(tip);

			auto tip = MsgBox::create();
			tip->initMsg(MsgBox::MB_TYPE_TIP,0,MsgManager::FUNCTION_NOT_OPEN);
			this->addChild(tip);
		}
		break;
	case TAG_MENU_ITEM_UNK_3:
		{
			auto tp = TaskPanel::create();
			tp->setPosition(Vec2(win_size.width/2,win_size.height/2));
			if(tp->initFromPlayer())
			{	
				this->addChild(tp);
			}	
		}
		break;
	default:
		break;
	}
}



void MainUI::touchEvent( Ref *pSender, Widget::TouchEventType type )
{
	auto btn = (Button*)pSender;
	auto win_size = Director::getInstance()->getWinSize();

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			if (m_bShow)
			{

				m_bShow = false;
				Button* btn_menu = (Button*)Helper::seekWidgetByName(m_layout,"btn_menu");
				if(btn_menu)
					btn_menu->setScaleX(-1);

				auto menu = (PokerMenu*)this->getChildByTag(TAG_MAIN_FUNC_MENU);
				if (menu)
				{
					menu->hide();
				}


				//
				auto img_menu_icon_bg = (ImageView*)m_layout->getChildByName("img_menu_icon_bg");
				if (img_menu_icon_bg)
				{
					img_menu_icon_bg->runAction(Sequence::create(DelayTime::create(0.2f),MoveBy::create(0.3f,Vec2(img_menu_icon_bg->getContentSize().width,0)),nullptr));
				}
			}
			else
			{
			
				m_bShow = true;
				Button* btn_menu = (Button*)Helper::seekWidgetByName(m_layout,"btn_menu");
				if(btn_menu)
					btn_menu->setScaleX(1);

				auto img_menu_icon_bg = (ImageView*)m_layout->getChildByName("img_menu_icon_bg");
				if (img_menu_icon_bg)
				{
					img_menu_icon_bg->runAction(Sequence::create(MoveTo::create(0.2f,Vec2(win_size.width,0)),nullptr));
				}

				auto menu = (PokerMenu*)this->getChildByTag(TAG_MAIN_FUNC_MENU);
				if (menu)
				{
					menu->show();
				}

			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void MainUI::initFromPlayer( LocalPlayer* _lp )
{
	if (!_lp)
	{
		return;
	}

	// vip
	auto vip =  (TextBMFont*)Utility::findWidget(m_layout,"pl_top_info/role_info/vip_val");
	if (vip)
	{	
		vip->setString(StringUtils::format("%d",_lp->m_base_attr.m_data[GameDefine::tBaseAttr::BA_VIP]));
	}


	// 钻石
	auto diamond = (TextBMFont*)Utility::findWidget(m_layout,"pl_top_info/diamond_info/diam_val");
	if (diamond)
	{
		diamond->setString(StringUtils::format("%d",_lp->m_base_attr.m_data[GameDefine::tBaseAttr::BA_DIAMOND]));
	}

	// 金币
	auto gold = (TextBMFont*)Utility::findWidget(m_layout,"pl_top_info/money_info/gold_val");
	if (gold)
	{	
		gold->setString(StringUtils::format("%d",_lp->m_base_attr.m_data[GameDefine::tBaseAttr::BA_GOLD]));
	}

	// 体力
	auto phys = (TextBMFont*)Utility::findWidget(m_layout,"pl_top_info/phys_info/phys_val");
	if (phys)
	{
		phys->setString(StringUtils::format("%d/%d",_lp->m_base_attr.m_data[GameDefine::tBaseAttr::BA_PHYSICAL],100));
	}


}

void MainUI::onEnter()
{
	Layer::onEnter();

	// 刷新数据
	initFromPlayer(LocalPlayer::getInstance());
}
