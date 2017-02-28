#include "StageItem.h"
#include "cocostudio/CocoStudio.h"
#include "GameDefine.h"
#include "StageDesc.h"
#include "../frame/GameScene.h"
//#include "UICopySelect.h"
#include "../utility/StackLayerMgr.h"
#include "../data/GameData.h"
#include "../data/LocalPlayer.h"
#include "StageDescLayer.h"
#include "../utility/Utility.h"
#include "../data/MsgManager.h"
#include "../component/PopTipManager.h"

using namespace cocostudio;



StageItem::StageItem(void)
{
}


StageItem::~StageItem(void)
{
}

bool StageItem::init()
{
	if (!Widget::init())
	{
		return false;
	}

	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("StageItem/StageItem.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);

	this->setTouchEnabled(true);
	this->addTouchEventListener(CC_CALLBACK_2(StageItem::touchEvent,this));

	return true;
}

void StageItem::setStageStar( int _star_num )
{

	// 设置关卡通过级别
	auto stage_state = (ImageView*)m_layout->getChildByName("stage_state");
	if (stage_state)
	{
		std::string stage_file;
		if (_star_num > GameDefine::STAGE_NORMAL)
		{
			if (_star_num == GameDefine::STAGE_PERFECT)
			{
				stage_file = "Common/97A.png";
			}

			stage_state->loadTexture(stage_file);
		}
		else // 没通过
		{
			stage_state->setVisible(false);
		}	
	}

	// 设置星级
	for (int i = 1; i <= _star_num; i++)
	{
		std::string stage_file = StringUtils::format("img_star_%d",i);
		auto star = (ImageView*)m_layout->getChildByName(stage_file);
		if (star)
		{
			star->loadTexture("Common/79.png");
		}
	}
}

void StageItem::touchEvent( Ref *pSender, Widget::TouchEventType type )
{

	Size win_size = Director::getInstance()->getWinSize();
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			int stage_id = this->getTag();
			if (stage_id > 0)
			{
				// 检查是否可以打
				auto cfg_stage_info = g_StageInfoMgr.getObject(stage_id);
				if (!cfg_stage_info)
				{
					CCLOG("stage id %d has no info",stage_id);
					return;
				}

				// 有没有前置关卡
				if (cfg_stage_info->req_stage_id > 0)
				{
					const auto& stage_infos = LocalPlayer::getInstance()->m_stage_infos;
					if (stage_infos.count(cfg_stage_info->req_stage_id) == 0)
					{
						PopTipManager::getInstance()->popTips(MsgManager::BATTLE_STAGE_REQ);
						CCLOG("can't attack");
						return;
					}
				}
				

				auto stage_desc = StageDescLayer::create();
				stage_desc->initFromStageId(this->getTag());

				auto layer = getRootLayer();
				if(layer)
				{
					layer->getParent()->addChild(stage_desc);
	
					//
					StackLayerMgr::getInstance()->pushLayer(stage_desc);
					//layer->removeFromParent();

					stage_desc->setScale(0.1f);
					stage_desc->runAction(EaseSineOut::create(ScaleTo::create(0.2f,1)));

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

Layer* StageItem::getRootLayer()
{
	
	Node* _node = this;
	Node* _ret = nullptr;
	do 
	{
		_ret = _node->getParent();
		_node = dynamic_cast<Widget*>(_ret);	
	
	} while (_node);

	return dynamic_cast<Layer*>(_ret);
}



void StageItem::onEnter()
{
	
	Widget::onEnter();

	int stage_id = this->getTag();
	auto stage_info = g_StageInfoMgr.getObject(stage_id);
	if (stage_info)
	{

		// 设置等级限制
		auto lb_lvl_ctrl = (Text*)Utility::findWidget(m_layout,"pl_lvl_ctrl/lb_lvl_ctrl");
		if (lb_lvl_ctrl)
		{
			lb_lvl_ctrl->setString(StringUtils::format("%d",1));
		}


		auto bl_title = (TextBMFont*)Utility::findWidget(m_layout,"bl_title");
		if (bl_title)
		{

			auto copy_id = stage_id / BaseDefine::HUNDRED_BASE;
			auto chap = stage_id % BaseDefine::HUNDRED_BASE;

			auto fmt = MsgManager::getInstance().getMsg(MsgManager::STAGE_TITLE_FMT);
			bl_title->setString(StringUtils::format(fmt,
				MsgManager::getInstance().getMsg(copy_id),
				chap));

		}

	}


	// 设置副本星级
	int star_cnt = 0;
	const auto& stage_infos = LocalPlayer::getInstance()->m_stage_infos;
	std::map<int,int>::const_iterator _iter = stage_infos.find(stage_id);
	if (_iter != stage_infos.end())
	{
		star_cnt = _iter->second;
	}

	setStageStar(star_cnt);
}
