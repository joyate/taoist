#include "StageDescLayer.h"
#include "cocostudio/CocoStudio.h"
#include "NewStageDesc.h"
#include "StageArmySel.h"
#include "../utility/StackLayerMgr.h"
#include "../data/LocalPlayer.h"

StageDescLayer::StageDescLayer(void):
	m_stage_id(0),
	m_cur_page_index(TAG_STAGE_DESC)
{
}


StageDescLayer::~StageDescLayer(void)
{

}

bool StageDescLayer::initFromStageId( int _stage_id )
{
	if (_stage_id <= 0)
	{
		return false;
	}

	m_stage_id = _stage_id;
	auto win_size = Director::getInstance()->getWinSize();

	// 描述
	auto stage_desc = NewStageDesc::create();
	stage_desc->setTag(TAG_STAGE_DESC);
	stage_desc->initFromStageId(m_stage_id);
	stage_desc->setPosition(Vec2(win_size.width/2,win_size.height/2));

	this->addChild(stage_desc);


	// 选兵
	auto stage_sel = StageArmySel::create();
	stage_sel->setTag(TAG_STAGE_SEL);
	stage_sel->setCurStageId(m_stage_id);
	stage_sel->setPosition(Vec2(-win_size.width,win_size.height/2));


	// 保存一下
	LocalPlayer::getInstance()->m_temp_fight_info.curr_stage_id = _stage_id;

	//
	this->addChild(stage_sel);

	return true;
}


bool StageDescLayer::init()
{

	if (!LayerColor::initWithColor(Color4B(0,0,0,200)))
	{
		return false;
	}

	auto win_size = Director::getInstance()->getWinSize();

	//
	auto btn_back = Button::create("Common/btn_cube_left.png","Common/btn_cube_left.png");

	auto stage_desc = (Widget*)this->getChildByTag(TAG_STAGE_DESC);
	btn_back->setPosition(Vec2(btn_back->getContentSize().width/2 + BUTTON_MARGIN,win_size.height/2));
	btn_back->setTag(TAG_STAGE_BACK);
	btn_back->addTouchEventListener(CC_CALLBACK_2(StageDescLayer::btnTouchEvent,this));

	this->addChild(btn_back);



	auto btn_next = Button::create("Common/btn_cube_left.png","Common/btn_cube_left.png");
	btn_next->setScaleX(-1.0f);
	auto stage_sel = (Widget*)this->getChildByTag(TAG_STAGE_SEL);
	btn_next->setPosition(Vec2(win_size.width - btn_next->getContentSize().width/2 - BUTTON_MARGIN,win_size.height/2));
	btn_next->setTag(TAG_STAGE_NEXT);
	btn_next->addTouchEventListener(CC_CALLBACK_2(StageDescLayer::btnTouchEvent,this));


	this->addChild(btn_next);


	return true;
}



void StageDescLayer::btnTouchEvent( Ref *pSender, Widget::TouchEventType type )
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
			if (btn->getTag() == TAG_STAGE_BACK)
			{
				if(m_cur_page_index <= TAG_STAGE_DESC)
				{
					StackLayerMgr::getInstance()->popLayer();

					// 重置一下数据
					LocalPlayer::getInstance()->m_temp_fight_info.reset();
				}
				else
				{
					scrollStageView(SD_DIR_LEFT);
				}
				
			}
			else if( btn->getTag() == TAG_STAGE_NEXT)
			{
				scrollStageView(SD_DIR_RIGHT);
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}



void StageDescLayer::scrollStageView( int _dir /*= SD_DIR_RIGHT*/ )
{

	auto win_size = Director::getInstance()->getWinSize();

	switch (_dir)
	{
	case SD_DIR_LEFT:
		{
			if (m_cur_page_index <= TAG_STAGE_DESC)
			{
				return;
			}

			auto stage_desc = this->getChildByTag(TAG_STAGE_SEL);
			if (stage_desc)
			{
				stage_desc->runAction(EaseSineIn::create(MoveBy::create(0.6f,Vec2(-win_size.width,0))));
			}

			auto stage_sel = this->getChildByTag(TAG_STAGE_DESC);
			if (stage_sel)
			{
				stage_sel->runAction(EaseSineIn::create(MoveTo::create(0.6f,Vec2(win_size.width/2,win_size.height/2))));
			}

			auto btn = this->getChildByTag(TAG_STAGE_NEXT);
			if (btn)
			{
				btn->setVisible(true);
			}

			m_cur_page_index--;
		}
		break;
	case SD_DIR_RIGHT:
		{

			if (m_cur_page_index >= TAG_STAGE_SEL)
			{
				return;
			}

			auto stage_desc = this->getChildByTag(TAG_STAGE_DESC);
			if (stage_desc)
			{
				stage_desc->runAction(EaseSineIn::create(MoveBy::create(0.6f,Vec2(win_size.width,0))));
			}

			auto stage_sel = this->getChildByTag(TAG_STAGE_SEL);
			if (stage_sel)
			{
				stage_sel->runAction(EaseSineIn::create(MoveTo::create(0.6f,Vec2(win_size.width - stage_sel->getContentSize().width/2 - 10 ,win_size.height/2))));
			}

			auto btn = this->getChildByTag(TAG_STAGE_NEXT);
			if (btn)
			{
				btn->setVisible(false);
			}

			m_cur_page_index++;
		}
		break;
	default:
		break;
	}

}

