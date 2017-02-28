#include "TaskItem.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"
#include "../data/LocalPlayer.h"
#include "../utility/Utility.h"
#include "Item.h"
#include "../frame/GameScene.h"
#include "../game_ui/GameWorldMap.h"
#include "../game_ui/StageDescLayer.h"
#include "../utility/StackLayerMgr.h"

using namespace cocostudio;



UITaskItem::UITaskItem(void):
	m_layout(nullptr),
	m_task_id(0)
{
}


UITaskItem::~UITaskItem(void)
{
}



bool UITaskItem::init()
{
	if (!Widget::init())
	{
		return false;
	}


	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("TaskItem/TaskItem.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);


	//
	/*auto img_frame_effect = (Widget*)Utility::findWidget(m_layout,"img_frame_effect");
	if (!img_frame_effect)
	{
	img_frame_effect->setVisible(false);
	}*/


	//
	Utility::registerTouchEvent(m_layout,"btn_go",CC_CALLBACK_2(UITaskItem::touchEvent,this));


	return true;
}



void UITaskItem::initFromTask( const tDailyTaskInfo& _dti )
{
	auto cfg_task_info = g_DailyTaskMgr.getObject(_dti.tid);
	if (!cfg_task_info)
	{
		return;
	}

	auto lb_desc = (Text*)Utility::findWidget(m_layout,"lb_desc");
	if (lb_desc)
	{
		lb_desc->setContentSize(Size(400,27));
		lb_desc->setString(cfg_task_info->task_desc);
		lb_desc->setFontName("fzyh.ttf");
	}


	auto bl_tips = (TextBMFont*)Utility::findWidget(m_layout,"bl_tips");
	if (bl_tips)
	{
		bl_tips->setString(StringUtils::format("%d/%d",_dti.cur_num,cfg_task_info->task_num));
	}


	if(!cfg_task_info->rewards.empty())
	{
		auto lv_rewards = (ListView*)Utility::findWidget(m_layout,"lv_rewards");
		if (lv_rewards)
		{
			int item_size = cfg_task_info->rewards.size();
			for (int i = 0; i < item_size; i++)
			{
				auto item = UIItem::create();
				item->initFromItemTempId(cfg_task_info->rewards[i]);

				lv_rewards->addChild(item);
			}	
		}
	}

	m_task_id = _dti.tid;

	updateState(_dti);
}

void UITaskItem::touchEvent( Ref *pSender, Widget::TouchEventType type )
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
			
			auto cfg_task_info = g_DailyTaskMgr.getObject(m_task_id);
			if (!cfg_task_info)
			{
				return;
			}

			if (btn->getName() == "btn_go")	 // 做任务
			{
				auto win_size = Director::getInstance()->getWinSize();
				auto scene = Director::getInstance()->getRunningScene();
				auto layer = scene->getChildByTag(SceneMain::TAG_POP_LAYER);

				if (!layer)
				{
					return;
				}

				// 战斗事件
				if (cfg_task_info->task_type & TT_ST_FIGHT_COPY)
				{
					// 不指定，就进入战斗地图
					if(cfg_task_info->task_target <= 0)
					{
						auto map = GameWorldMap::create();
						map->setPosition(Vec2((win_size.width - map->getContentSize().width)/2,
							(win_size.height - map->getContentSize().height)/2));
						layer->addChild(map);


						StackLayerMgr::getInstance()->beginStackLayer();
						StackLayerMgr::getInstance()->pushLayer(map);
					}
					else // 详细指定，就进入指定副本准备界面
					{
						auto stage_desc = StageDescLayer::create();
						stage_desc->initFromStageId(cfg_task_info->task_target);
						layer->addChild(stage_desc);

						StackLayerMgr::getInstance()->beginStackLayer();
						StackLayerMgr::getInstance()->pushLayer(stage_desc);
					}
				}


			}
			else if(btn->getName() == "btn_reward")		// 领奖
			{
				auto dti = LocalPlayer::getInstance()->getDailyTaskByTid(m_task_id);
				if (!dti)
				{
					return;
				}

			
				// 给奖励




				dti->ts = TS_DONE;
				LocalPlayer::getInstance()->save(GameDefine::ROLE_SAVE_FILE);

				// 隐藏领奖按钮
				btn->setVisible(false);
				// 隐藏完成任务特效
				auto img_frame_effect = (ImageView*)Utility::findWidget(m_layout,"img_frame_effect");
				if (img_frame_effect && img_frame_effect->isVisible())
				{
					img_frame_effect->setVisible(false);
				}

				// 刷新一下
				updateState(*dti);
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}


void UITaskItem::updateState( const GameDefine::tDailyTaskInfo& _dti )
{
	if (_dti.tid <= 0)
	{
		return;
	}

	auto cfg_task_info = g_DailyTaskMgr.getObject(_dti.tid);
	if (!cfg_task_info)
	{
		return;
	}

	switch (_dti.ts)
	{
	case TS_DONE:
		{
			auto bl_tips = (TextBMFont*)Utility::findWidget(m_layout,"bl_tips");
			if (bl_tips)
			{
				bl_tips->setVisible(false);
			}


			auto btn_go = (Button*)Utility::findWidget(m_layout,"btn_go");
			if (btn_go)
			{
				btn_go->setVisible(false);
			}


			auto img_state = (ImageView*)Utility::findWidget(m_layout,"img_state");
			if (img_state)
			{
				img_state->setVisible(true);
			}
		}
		break;
	default:
		{
			if (_dti.cur_num >= cfg_task_info->task_num)
			{
				auto btn_go = (Button*)Utility::findWidget(m_layout,"btn_go");
				if (btn_go)
				{
					btn_go->loadTextures("TaskItem/ui_rec_nor.png","TaskItem/ui_rec_act.png");
					btn_go->setName("btn_reward");
				}

				//
				auto img_frame_effect = (ImageView*)Utility::findWidget(m_layout,"img_frame_effect");
				if (img_frame_effect)
				{
					img_frame_effect->setVisible(true);
					img_frame_effect->runAction(RepeatForever::create(
						Sequence::create(FadeIn::create(1.0f),FadeOut::create(1.0f),nullptr)));
				}

			}
		}
		break;
	}

	
}




