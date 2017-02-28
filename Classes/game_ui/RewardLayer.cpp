#include "RewardLayer.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"
#include "../data/LocalPlayer.h"
#include "../utility/Utility.h"
#include "Item.h"

using namespace cocostudio;

RewardLayer::RewardLayer(void):
	m_br_star_cnt(0)
{

}


RewardLayer::~RewardLayer(void)
{

}



bool RewardLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(33,33,33,222)))
	{
		return false;
	}

	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("RewardPanel/RewardPanel.ExportJson");
	this->addChild(m_layout);


	Utility::registerTouchEvent(m_layout,"btn_close",CC_CALLBACK_2(RewardLayer::touchEvent,this));

	return true;
}

void RewardLayer::touchEvent( Ref *pSender, Widget::TouchEventType type )
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
				// 确认奖励
				LocalPlayer::getInstance()->conformReward();
				// 返回
				Director::getInstance()->popScene();
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

}



void RewardLayer::initBattleResult(int _stage_id )
{
	if (!m_layout)
	{
		return;
	}

	
	auto& tfi = LocalPlayer::getInstance()->m_temp_fight_info;
	tfi.star_cnt = calculateBRStar(tfi.defender_dead_cnt);
	m_br_star_cnt = tfi.star_cnt;

	// 金币奖励
	auto bl_gold = (TextBMFont*)Utility::findWidget(m_layout,"img_items_bg/bl_gold");
	if (bl_gold)
	{		
		bl_gold->setString(StringUtils::format("%d",tfi.rewardGold));
	}

	auto bl_diamond = (TextBMFont*)Utility::findWidget(m_layout,"img_special_bg/bl_diamond");
	if (bl_diamond)
	{
		bl_diamond->setString(StringUtils::format("%d",0));
		bl_diamond->setVisible(false);
	}

	//
	fillEquipReward();

	// 设置结果星级
	setBRStar();
}

int RewardLayer::calculateBRStar(int _defender_dead_cnt)
{
	if (_defender_dead_cnt < BR_TRI_STAR_LB)
	{
		return 3;
	}
	else if(_defender_dead_cnt < BR_TWO_STAR_LB)
	{
		return 2;
	}
	
	return 1;
}



void RewardLayer::setBRStar()
{
	for (int i = BR_STAR_NUM; i > 0; i--)
	{
		std::string star_file = StringUtils::format("star_%d/star_mask_%d",i,i);
		auto star = (ImageView*)Utility::findWidget(m_layout,star_file.c_str());
		if (star)
		{
			if(m_br_star_cnt < i)
				star->setVisible(false);
		}
	}
	
}



void RewardLayer::fillEquipReward()
{

	auto lv_equips = Utility::findWidget(m_layout,"lv_equips");
	if (!lv_equips)
	{
		return;
	}

	auto& tfi = LocalPlayer::getInstance()->m_temp_fight_info;


	for (int i = 0; i < GD_REWARD_CNT_MAX; i++)
	{
		if (tfi.rewards[i].id != 0)
		{
			auto item = UIItem::create();
			item->initFromItemTempId(tfi.rewards[i].id,tfi.rewards[i].cnt);
			lv_equips->addChild(item);
		}
	}
}
