#include "SideItemListView.h"
#include "../data/LocalPlayer.h"
#include "../game_ui/SideItem.h"
#include "../game_ui/FightUI.h"

SideItemListView::SideItemListView(void)
{
}


SideItemListView::~SideItemListView(void)
{
}


void SideItemListView::initFromLocalPlayer(FightUI* _owner)
{
	const tTempFightInfo& fsi = LocalPlayer::getInstance()->m_temp_fight_info;

	for (int i = 1; i < GameDefine::GD_ARMY_ON_ROUND_NUM_MAX; i++)
	{
		// 
		if (!fsi.army_inst_id[i])
		{
			continue;
		}

		// ±øÖÖÑ¡Ôñitem
		auto si = SideItem::create();
		si->initFromCardInstance(fsi.army_inst_id[i]);
		si->setTag(fsi.army_inst_id[i]);
		si->setTouchEnabled(true);
		si->addTouchEventListener(CC_CALLBACK_2(FightUI::touchShopItemEvent,_owner));


		//
		auto lp = LinearLayoutParameter::create();
		lp->setMargin(Margin(1.0f, 10.0f, 1.0f, 10.0f));
		lp->setGravity(LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
		si->setLayoutParameter(lp);

		this->addChild(si);		
	}
}

bool SideItemListView::init()
{	

	if (!ListView::init())
	{
		return false;
	}

	this->setDirection(ui::ScrollView::Direction::VERTICAL);
	this->setContentSize(Size(128,500));
	this->setTouchEnabled(true);

	return true;
}


void SideItemListView::interceptTouchEvent( Widget::TouchEventType event,Widget* sender,Touch* touch )
{
	// ½Ø¶ÏÏÂ
	if (m_op == DIR_SHOP_LIST_HORIZONTAL)
	{
		return;
	}

	ListView::interceptTouchEvent(event,sender,touch);
}
