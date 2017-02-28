#include "HeroInfoMain.h"
#include "cocostudio/CocoStudio.h"
#include "ObjInfoDetailPanel.h"
#include "../utility/Utility.h"
#include "../GameDefine.h"
#include "../data/LocalPlayer.h"
#include "../data/GameData.h"
#include "../component/GuideFilterMgr.h"

using namespace cocostudio;


HeroInfoMain::HeroInfoMain():
	m_info_detail(nullptr)
{
}


HeroInfoMain::~HeroInfoMain()
{
}


bool HeroInfoMain::init()
{

	if (!Widget::init())
	{
		return false;
	}


	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("HeroMainPanel/HeroMainPanel.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);


	m_info_detail = ObjInfoDetailPanel::create();
	m_info_detail->setPosition(Vec2(-m_info_detail->getContentSize().width/2,this->getContentSize().height/2));
	this->addChild(m_info_detail);



#ifndef IMPL_IMAGE_EVENT
#define IMPL_IMAGE_EVENT(root,_name)	\
	do{\
	Widget* _name = (Widget*)Helper::seekWidgetByName(root,#_name);		\
	_name->setTouchEnabled(true);											\
	_name->addTouchEventListener(CC_CALLBACK_2(HeroInfoMain::imgTouchEvent,this)); \
	}while(0)


#undef IMPL_IMAGE_EVENT
#endif


	//
	for (int i = GameDefine::ET_HELMET; i < GameDefine::ET_MAX; i++)
	{
		if(i < GameDefine::ET_WEAPON)
			Utility::registerTouchEvent(m_layout,
			StringUtils::format("pl_root/pl_equip_left/img_equip_%d/img_equip",i),
			CC_CALLBACK_2(HeroInfoMain::imgTouchEvent,this));
		else
			Utility::registerTouchEvent(m_layout,
			StringUtils::format("pl_root/pl_equip_right/img_equip_%d/img_equip",i),
			CC_CALLBACK_2(HeroInfoMain::imgTouchEvent,this));
	}


#ifndef IMPL_BTN_EVENT
#define IMPL_BTN_EVENT(_root,_name)	\
	do{\
	Button* btn = (Button*)Helper::seekWidgetByName(_root,#_name); \
	btn->addTouchEventListener(CC_CALLBACK_2(HeroInfoMain::btnTouchEvent,this)); \
	}while(0)

	IMPL_BTN_EVENT(m_layout,btn_exit);

#undef IMPL_BTN_EVENT
#endif


	//
	Utility::registerTouchEvent(m_layout,
		"pl_root/pl_base_attr/btn_upgrade",
		CC_CALLBACK_2(HeroInfoMain::btnTouchEvent,this));


	return true;
}




void HeroInfoMain::btnTouchEvent( Ref *pSender, Widget::TouchEventType type )
{
	auto btn = (Button*)pSender;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			if (btn->getName() == "btn_exit")
			{
				// 战斗流程教学
				GuideFilterMgr::getInstance().checkGuideFilter(GuideFilterMgr::GFN_BATTLE_PRATICE);

				this->removeFromParent();
			}
			else if(btn->getName() == "btn_upgrade")
			{
				//
			}

		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

}






void HeroInfoMain::imgTouchEvent( Ref *pSender, Widget::TouchEventType type )
{
	auto img_equip = (ImageView*)pSender;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			std::string img_name = img_equip->getName();


		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}



void HeroInfoMain::WidgetCallback( Node* sender )
{
	auto panel = (Widget*)sender;
	panel->setVisible(!panel->isVisible());
}




void HeroInfoMain::initWithInstId( int _inst_id )
{
	auto& bag = LocalPlayer::getInstance()->m_bag;

	auto inst_card_info = (tCardInfo*)bag.getItemById(_inst_id);
	if (!inst_card_info)
	{
		CCLOG("instance id %d no found info",_inst_id);
		return;
	}


	auto cfg_card_info = (cfg_Card*)g_ItemInfoMgr.getObject(inst_card_info->item_temp_id);
	if (!cfg_card_info)
	{
		CCLOG("card id %d has no data",inst_card_info->item_temp_id);
		return;
	}


	// 设置名称
	auto lb_name = (Text*)Utility::findWidget(m_layout,"lb_name");
	if (lb_name)
	{
		lb_name->setString(cfg_card_info->szName);
		lb_name->setFontName("fzyh.ttf");
	}


	setLevel(inst_card_info->m_lvl);
	setExp(inst_card_info->m_exp);
	setFeType(cfg_card_info->cat);
	setFight(inst_card_info->m_fight);
	setFullPic(cfg_card_info->card_pic);

	// 初始化详细信息面板
	if (m_info_detail)
	{
		m_info_detail->initFromInstId(_inst_id);
	}

}

void HeroInfoMain::setLevel( int _lvl )
{
	auto bl_lvl = (TextBMFont*)Utility::findWidget(m_layout,"pl_root/pl_base_attr/img_base_bg/bl_lvl");
	if (bl_lvl)
	{
		bl_lvl->setString(StringUtils::format("%d",_lvl));
	}
}

void HeroInfoMain::setExp( unsigned int _exp )
{
	auto bl_exp = (TextBMFont*)Utility::findWidget(m_layout,"pl_root/pl_base_attr/img_exp/bl_exp");
	if (bl_exp)
	{
		bl_exp->setString(StringUtils::format("%d",_exp));
	}
}

void HeroInfoMain::setFight( int _ft )
{
	auto bl_fight = (TextBMFont*)Utility::findWidget(m_layout,"pl_root/pl_base_attr/img_exp/bl_fight");
	if (bl_fight)
	{
		bl_fight->setString(StringUtils::format("%d",_ft));
	}
}

void HeroInfoMain::setFeType( int _fe )
{
	auto img_fe_type = (ImageView*)Utility::findWidget(m_layout,"pl_root/pl_base_attr/img_fe_type");
	if (img_fe_type)
	{
		img_fe_type->loadTexture(StringUtils::format("Common/fe_type_%d.png",_fe));
	}
}

void HeroInfoMain::setGhost( int _gh, int _gh_max )
{
	auto pb_ghost = (LoadingBar*)Utility::findWidget(m_layout,"pl_root/pl_base_attr/img_ghost_bg/pb_ghost");
	if (!pb_ghost)
	{
		return;
	}


	auto bl_ghost = (TextBMFont*)Utility::findWidget(m_layout,"pl_root/pl_base_attr/img_ghost_bg/bl_ghost");
	if (!bl_ghost)
	{
		return;
	}

	if (_gh_max == 0)
	{
		return;
	}

	bl_ghost->setString(StringUtils::format("%d/%d",_gh,_gh_max));
	pb_ghost->setPercent((float)_gh/_gh_max);

}

void HeroInfoMain::setFullPic( const char* _path )
{
	auto img_hero = (ImageView*)Utility::findWidget(m_layout,"pl_root/img_hero");
	if (img_hero)
	{
		img_hero->loadTexture(_path);
	}
}




