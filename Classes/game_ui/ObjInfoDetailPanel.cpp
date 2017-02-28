#include "ObjInfoDetailPanel.h"
#include "cocostudio/CocoStudio.h"
#include "../data/LocalPlayer.h"
#include "../data/GameData.h"
#include "../utility/Utility.h"
#include "../data/MsgManager.h"
#include "SkillUpItem.h"
#include "UISkillDesc.h"


using namespace cocostudio;

ObjInfoDetailPanel::ObjInfoDetailPanel(void):
	m_layout(nullptr),
	m_cur_view_index(-1),
	m_inst_id(0)
{
}


ObjInfoDetailPanel::~ObjInfoDetailPanel(void)
{
}



bool ObjInfoDetailPanel::init()
{
	if (!Widget::init())
	{
		return false;
	}


	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("ObjInfoDetailPanel/ObjInfoDetailPanel.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);



#ifndef IMPL_IMAGE_EVENT
#define IMPL_IMAGE_EVENT(root,_name)	\
	do{\
	Widget* _name = (Widget*)Helper::seekWidgetByName(root,#_name);		\
	_name->setTouchEnabled(true);											\
	_name->addTouchEventListener(CC_CALLBACK_2(ObjInfoDetailPanel::imgTouchEvent,this)); \
	}while(0)


	IMPL_IMAGE_EVENT(m_layout,img_attr);
	IMPL_IMAGE_EVENT(m_layout,img_where);
	IMPL_IMAGE_EVENT(m_layout,img_skill);
	IMPL_IMAGE_EVENT(m_layout,img_help);


#undef IMPL_IMAGE_EVENT
#endif

	updateSubView(ODP_VIEW_SKILL);


	auto sd = UISkillDesc::create();
	sd->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	//sk_desc->setTag(SUI_SKILL_DESC_TAG);
	sd->setVisible(false);
	this->addChild(sd,99,SUI_SKILL_DESC_TAG);
	

	return true;
}

void ObjInfoDetailPanel::imgTouchEvent( Ref *pSender, Widget::TouchEventType type )
{
	auto img = (ImageView*)pSender;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			int cur_index = ODP_VIEW_ATTR;
			if (img->getName().find("skill") != std::string::npos)
			{
				cur_index = ODP_VIEW_SKILL;
			}
			else if(img->getName().find("where") != std::string::npos)
			{
				cur_index = ODP_VIEW_WHERE;
			}

			if (m_cur_view_index != cur_index)
			{
				updateSubView(cur_index);
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}



bool ObjInfoDetailPanel::initFromInstId( int _inst_id )
{

	auto& bag = LocalPlayer::getInstance()->m_bag;
	auto inst_card_info = (tCardInfo*)bag.getItemById(_inst_id);
	if (!inst_card_info)
	{
		CCLOG("instance id %d has no data",_inst_id);
		return false;
	}


	auto cfg_card_info = (cfg_Card*)g_ItemInfoMgr.getObject(inst_card_info->item_temp_id);
	if (!cfg_card_info)
	{
		CCLOG("card id %d has no config",cfg_card_info->id);
		return false;
	}


	initBaseAttr(inst_card_info,cfg_card_info);
	initSkill(inst_card_info,cfg_card_info);


	return true;
}




void ObjInfoDetailPanel::updateSubView( int _vi )
{
	switch (_vi)
	{
	case ODP_VIEW_ATTR:
		{
			auto img = (ImageView*)m_layout->getChildByName("img_attr");
			if (img)
			{
				img->loadTexture("ObjInfoDetailPanel/img_attr_act.png");
			}

			auto pl_attr = (Layout*)m_layout->getChildByName("pl_attr");
			if (pl_attr)
			{
				pl_attr->setVisible(true);
			}

		}
		break;
	case ODP_VIEW_SKILL:
		{
			auto img = (ImageView*)m_layout->getChildByName("img_skill");
			if (img)
			{
				img->loadTexture("img_skill_act.png",Widget::TextureResType::PLIST);
			}


			auto lv_skills = (ListView*)m_layout->getChildByName("lv_skills");
			if (lv_skills)
			{
				lv_skills->setVisible(true);
			}

		}
		break;
	case ODP_VIEW_WHERE:
		{
			auto img = (ImageView*)m_layout->getChildByName("img_where");
			if (img)
			{
				img->loadTexture("ObjInfoDetailPanel/img_where_act.png");
			}

			auto pl_where = (ListView*)m_layout->getChildByName("pl_where");
			if (pl_where)
			{
				pl_where->setVisible(true);
			}
		}
	default:
		break;
	}


	switch (m_cur_view_index)
	{
	case ODP_VIEW_ATTR:
		{
			auto pl_attr = (Layout*)m_layout->getChildByName("pl_attr");
			if (pl_attr)
			{
				pl_attr->setVisible(false);
			}


			auto img = (ImageView*)m_layout->getChildByName("img_attr");
			if (img)
			{
				img->loadTexture("img_attr_nor.png",Widget::TextureResType::PLIST);
			}

		}
		break;
	case ODP_VIEW_SKILL:
		{
			auto lv_skills = (ListView*)m_layout->getChildByName("lv_skills");
			if (lv_skills)
			{
				lv_skills->setVisible(false);
			}

			auto img = (ImageView*)m_layout->getChildByName("img_skill");
			if (img)
			{
				img->loadTexture("ObjInfoDetailPanel/img_skill_nor.png");
			}
		}
		break;
	case ODP_VIEW_WHERE:
		{
			auto img = (ImageView*)m_layout->getChildByName("img_where");
			if (img)
			{
				img->loadTexture("img_where_nor.png",Widget::TextureResType::PLIST);
			}


			auto pl_where = (ListView*)m_layout->getChildByName("pl_where");
			if (pl_where)
			{
				pl_where->setVisible(false);
			}
		}
		break;
	default:
		break;
	}

	m_cur_view_index = _vi;
}


void ObjInfoDetailPanel::initBaseAttr( GameDefine::tCardInfo* _inst_card,GameDefine::cfg_Card* _cfg_card )
{
	if (!_inst_card || !_cfg_card)
	{
		return;
	}

	auto lb_desc = (Text*)Utility::findWidget(m_layout,"pl_attr/pl_desc/lb_desc");
	if (lb_desc)
	{
		//lb_desc->ignoreContentAdaptWithSize(false);
		lb_desc->setString(MsgManager::getInstance().getMsg(_cfg_card->desc_id));
		lb_desc->setFontName("fzyh.ttf");
		//lb_desc->setContentSize(Size(300,100));
		lb_desc->setTextAreaSize(Size(300,100));

	}


	auto cfg_obj_info = g_ObjInfoMgr.getObject(_cfg_card->obj_id);
	if (!cfg_obj_info)
	{
		return;
	}


	// 设置力量
	auto lb_strength = (Text*)Utility::findWidget(m_layout,"pl_attr/pl_attr_bg/lb_strength");
	if (lb_strength)
	{
		lb_strength->setFontName("yuan.ttf");
		lb_strength->setString(StringUtils::format(MsgManager::getInstance().getMsg(MsgManager::STRENGTH_FMT),cfg_obj_info->strength));
	}

	// 设置智力
	auto lb_wit = (Text*)Utility::findWidget(m_layout,"pl_attr/pl_attr_bg/lb_wit");
	if (lb_wit)
	{
		lb_wit->setFontName("yuan.ttf");
		lb_wit->setString(StringUtils::format(MsgManager::getInstance().getMsg(MsgManager::WISE_FMT),cfg_obj_info->wise));
	}

	// 设置敏捷
	auto lb_agility = (Text*)Utility::findWidget(m_layout,"pl_attr/pl_attr_bg/lb_agility");
	if (lb_agility)
	{
		lb_agility->setFontName("yuan.ttf");
		lb_agility->setString(StringUtils::format(MsgManager::getInstance().getMsg(MsgManager::AGILITY_FMT),cfg_obj_info->agility));
	}

	// 设置统御力
	auto lb_ctrl = (Text*)Utility::findWidget(m_layout,"pl_attr/pl_attr_bg/lb_ctrl");
	if (lb_ctrl)
	{
		lb_ctrl->setFontName("yuan.ttf");
		lb_ctrl->setString(StringUtils::format(MsgManager::getInstance().getMsg(MsgManager::CONTROL_FMT),cfg_obj_info->hero_ctrl));
	}

	// 物理攻击
	auto lb_phys_atk = (Text*)Utility::findWidget(m_layout,"pl_attr/pl_attr_bg/lb_phys_atk");
	if (lb_phys_atk)
	{
		lb_phys_atk->setFontName("yuan.ttf");
		lb_phys_atk->setString(StringUtils::format(MsgManager::getInstance().getMsg(MsgManager::CARDTIP_PHYS_ATK_FMT),cfg_obj_info->phy_atk));
	}

	// 物理防御
	auto lb_phys_def = (Text*)Utility::findWidget(m_layout,"pl_attr/pl_attr_bg/lb_phys_def");
	if (lb_phys_def)
	{
		lb_phys_def->setFontName("yuan.ttf");
		lb_phys_def->setString(StringUtils::format(MsgManager::getInstance().getMsg(MsgManager::CARDTIP_PHYS_DEF_FMT),cfg_obj_info->phy_def));
	}

	// 法术攻击
	auto lb_mag_atk = (Text*)Utility::findWidget(m_layout,"pl_attr/pl_attr_bg/lb_mag_atk");
	if (lb_mag_atk)
	{
		lb_mag_atk->setFontName("yuan.ttf");
		lb_mag_atk->setString(StringUtils::format(MsgManager::getInstance().getMsg(MsgManager::CARDTIP_MAG_ATK_FMT),cfg_obj_info->mag_atk));
	}

	// 法术防御
	auto lb_mag_def = (Text*)Utility::findWidget(m_layout,"pl_attr/pl_attr_bg/lb_mag_def");
	if (lb_mag_def)
	{
		lb_mag_def->setFontName("yuan.ttf");
		lb_mag_def->setString(StringUtils::format(MsgManager::getInstance().getMsg(MsgManager::CARDTIP_MAG_ATK_FMT),cfg_obj_info->mag_def));
	}

	// 暴击
	auto lb_cri = (Text*)Utility::findWidget(m_layout,"pl_attr/pl_attr_bg/lb_cri");
	if (lb_cri)
	{
		lb_cri->setFontName("yuan.ttf");
		lb_cri->setString(StringUtils::format(MsgManager::getInstance().getMsg(MsgManager::CARDTIP_CRI_FMT),cfg_obj_info->atk_cri));
	}

}

void ObjInfoDetailPanel::initSkill( GameDefine::tCardInfo* _inst_card,GameDefine::cfg_Card* _cfg_card )
{

	if (!_inst_card || !_cfg_card)
	{
		return;
	}


	auto lv_skills = (ListView*)Utility::findWidget(m_layout,"lv_skills");
	if (!lv_skills)
	{
		return;
	}


	auto cfg_obj_attr = g_ObjInfoMgr.getObject(_cfg_card->obj_id);
	if (!cfg_obj_attr)
	{
		CCLOG("card id %d has no obj info",_cfg_card->id);
		return;
	}

	int i = 0;
	int zOrder = 9;
	do 
	{
		if (cfg_obj_attr->skill_ids[i] == 0)
		{
			break;
		}

		auto sui = SkillUpItem::create();
		if(!sui->initSkillId(cfg_obj_attr->skill_ids[i]))
		{
			break;
		}

		sui->initRootPtr(this);
		lv_skills->addChild(sui,zOrder-i);
		i++;

	} while (i < GameDefine::GD_SKILL_NUM_MAX);
}


void ObjInfoDetailPanel::showSkillTips( int _sk_id,const Vec2& _pos )
{
	auto sd = (UISkillDesc*)this->getChildByTag(SUI_SKILL_DESC_TAG);
	if (!sd)
	{
		return;
	}

	if (_sk_id < 0)
	{
		sd->setVisible(false);
		return;
	}

	sd->initWithSkillId(_sk_id);				
	Vec2 clk_pos = this->convertToNodeSpace(_pos);
	sd->setPosition(clk_pos + Vec2(15,0));
	sd->setVisible(true);
}
