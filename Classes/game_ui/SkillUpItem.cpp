#include "SkillUpItem.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"
#include "../utility/Utility.h"
#include "UISkillDesc.h"

using namespace cocostudio;



SkillUpItem::SkillUpItem(void):
	m_layout(nullptr),
	m_sk_id(0)
{
}


SkillUpItem::~SkillUpItem(void)
{
}


bool SkillUpItem::init()
{
	if (!Widget::init())
	{
		return false;
	}


	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("SkillUpItem/SkillUpItem.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);

	// 注册回调
	Utility::registerTouchEvent(m_layout,"btn_upgrage",CC_CALLBACK_2(SkillUpItem::btnTouchEvent,this));
	Utility::registerTouchEvent(m_layout,"img_skill_bg/img_skill",CC_CALLBACK_2(SkillUpItem::showSkillDesc,this));
	
	return true;
}




void SkillUpItem::btnTouchEvent( Ref *pSender, Widget::TouchEventType type )
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
			// 技能升级
			if (btn->getName() == "btn_upgrage")
			{
				
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}



bool SkillUpItem::initSkillId( int _sk_id,int _sk_lvl /*= 1*/ )
{
	auto cfg_sk_info = g_SkillInfoMgr.getObject(_sk_id);
	if (!cfg_sk_info)
	{
		CCLOG("skill id %d has no data",_sk_id);
		return false;
	}

	setSkillIcon(cfg_sk_info->szSkillIcon);
	setSkillLvl(_sk_lvl);
	setSkillName(cfg_sk_info->sk_name);
	//setUpgradeCost(10);

	m_sk_id = _sk_id;
	// lvl ignore

	return true;
}

void SkillUpItem::setSkillIcon( const char* path )
{
	auto img_skill = (ImageView*)Utility::findWidget(m_layout,"img_skill_bg/img_skill");
	if (img_skill)
	{
		img_skill->loadTexture(path);
	}
}

void SkillUpItem::setUpgradeCost( int _cost )
{
	auto bl_up_cost = (TextBMFont*)Utility::findWidget(m_layout,"bl_up_cost");
	if (bl_up_cost)
	{
		bl_up_cost->setString(StringUtils::format("%d",_cost));
	}
}

void SkillUpItem::setSkillLvl( int _lvl )
{
	auto label_skill_lvl = (Text*)Utility::findWidget(m_layout,"label_skill_lvl");
	if (label_skill_lvl)
	{
		label_skill_lvl->setFontName("fzyh.ttf");
		label_skill_lvl->setString(StringUtils::format("lv. %d",_lvl));
	}
}



void SkillUpItem::setSkillName( const char* _sk_name )
{
	auto label_skill_name = (Text*)Utility::findWidget(m_layout,"label_skill_name");
	if (label_skill_name)
	{
		label_skill_name->setFontName("fzyh.ttf");
		label_skill_name->setString(StringUtils::format("%s",_sk_name));
	}
}



void SkillUpItem::showSkillDesc( Ref *pSender, Widget::TouchEventType type )
{
	
	auto icon = (ImageView*)pSender;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		{
			if (m_sk_id != 0 && m_panel_root)
			{
				m_panel_root->showSkillTips(m_sk_id,icon->getTouchBeganPosition());
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		{			
			if (m_panel_root)
			{
				m_panel_root->showSkillTips(m_sk_id,icon->getTouchMovePosition());
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		{
			if (m_panel_root)
			{
				m_panel_root->showSkillTips(-1,Vec2::ZERO);
			}
		}
		break;
	default:
		break;
	}

	
}

