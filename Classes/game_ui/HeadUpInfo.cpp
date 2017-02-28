#include "HeadUpInfo.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"
#include "../frame/BattleScene.h"
#include "FightUI.h"
#include "CardTip.h"

using namespace cocostudio;

HeadUpInfo::HeadUpInfo(void):
	m_layout(nullptr),
	m_owner_id(0)
{
}


HeadUpInfo::~HeadUpInfo(void)
{
}



bool HeadUpInfo::init()
{
	if (!Widget::init())
	{
		return false;
	}


	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("HeadUpInfo/HeadUpInfo.ExportJson");
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);

	return true;
}



void HeadUpInfo::onEnter()
{
	Widget::onEnter();


	m_layout->setScale(0.1f);
	m_layout->runAction(EaseSineOut::create(ScaleTo::create(0.2f,1.0f)));

	auto btn = (Button*) m_layout->getChildByName("btn_info");
	if (btn)
	{
		btn->setScale(0.1f);
		btn->runAction(Sequence::create(DelayTime::create(0.2f),EaseSineOut::create(ScaleTo::create(0.2f,1.0f)),nullptr));

		btn->addTouchEventListener(CC_CALLBACK_2(HeadUpInfo::btnTouchEvent,this));
	}

}

void HeadUpInfo::btnTouchEvent( Ref *pSender, Widget::TouchEventType type )
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			//
			if (m_owner_id > 0)
			{
				auto bs = (BattleScene*)Director::getInstance()->getRunningScene();
				if (!bs)
				{
					return;
				}

				auto ft_ui = (FightUI*)bs->getChildByTag(BattleScene::TAG_FIGHT_UI);
				if (!ft_ui)
				{
					return;
				}

				auto card_tip = CardTip::create();
				card_tip->initFrom(m_owner_id);
				Vec2 pos = Vec2(this->getRightBoundary() + card_tip->getContentSize().width/2,
					this->getPosition().y - card_tip->getContentSize().height/3);
				card_tip->setPosition(pos);
				card_tip->setTag(FightUI::TAG_CARD_TIP_NODE);
				ft_ui->addChild(card_tip);

			}

			this->removeFromParent();
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
