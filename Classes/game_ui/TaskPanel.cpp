#include "TaskPanel.h"
#include "cocostudio/CocoStudio.h"
#include "../utility/Utility.h"
#include "../data/LocalPlayer.h"
#include "TaskItem.h"

using namespace cocostudio;

TaskPanel::TaskPanel(void)
{
}


TaskPanel::~TaskPanel(void)
{
}




bool TaskPanel::init()
{
	if (!Widget::init())
	{
		return false;
	}


	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("TaskPanel/TaskPanel.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);


	Utility::registerTouchEvent(m_layout,"pl_root/btn_close",CC_CALLBACK_2(TaskPanel::touchEvent,this));
	
	return true;
}



void TaskPanel::touchEvent( Ref *pSender, Widget::TouchEventType type )
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
			if (btn->getName() == "btn_close")
			{
				this->removeFromParent();
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}



bool TaskPanel::initFromPlayer()
{

	auto& dt = LocalPlayer::getInstance()->m_daily_task;
	int dt_size = dt.size();

	auto lv_tasks = (ListView*)Utility::findWidget(m_layout,"pl_root/lv_tasks");
	if (!lv_tasks)
	{
		return false;
	}

	for (int i = 0; i < dt_size; i++)
	{
		auto ti = UITaskItem::create();
		ti->initFromTask(dt[i]);

		lv_tasks->addChild(ti);
	}

	return true;
}
