#include "GameMain.h"
#include "cocostudio/CocoStudio.h"
#include "VisibleRect.h"
#include "GameScene.h"
//#include "LoadingScene.h"
#include "../GameDefine.h"
#include "../game_ui/GameWorldMap.h"
#include "../utility/StackLayerMgr.h"
#include "../component/GuideLayer.h"
#include "../game_ui/ReinforcePanel.h"
#include "../component/TaskManager.h"
#include "../data/LocalPlayer.h"

using namespace cocostudio;


GameMain::GameMain(void):
	_bTouchOK(false)
{
}


GameMain::~GameMain(void)
{
}

bool GameMain::init()
{
	if (!Layer::init())
	{
		return false;
	}


	Size size = Director::getInstance()->getWinSize();

	//auto map_layer = Layer::create();

	//_pNode = dynamic_cast<ui::Layout*>(GUIReader::getInstance()->widgetFromJsonFile("test_scene_1/test_scene_1.json"));
	_pNode = dynamic_cast<ui::Layout*>(GUIReader::getInstance()->widgetFromJsonFile("main_scene/main_scene.json"));

	_pNode->setAnchorPoint(Vec2::ZERO);
	_pNode->setPosition(Vec2::ZERO);

	//map_layer->addChild(_pNode);
	
	Size CC_UNUSED s = _pNode->getContentSize();
	CCLOG("Layout ContentSize: %f, %f", s.width,s.height);

	//map_layer->setContentSize(s);
	this->setContentSize(s);


#define IMPL_BTN_EVENT(_name)	\
	do{\
	Button* _name = (Button*)Helper::seekWidgetByName(_pNode,#_name); \
	_name->addTouchEventListener(CC_CALLBACK_2(GameMain::touchEvent,this)); \
	}while(0)


	IMPL_BTN_EVENT(ta);
	IMPL_BTN_EVENT(unk);
	IMPL_BTN_EVENT(miao);
	IMPL_BTN_EVENT(lu);
	IMPL_BTN_EVENT(cave);
	IMPL_BTN_EVENT(shop);


	addChild(_pNode);

	// 更新
	scheduleUpdate();

	return true;
}

//Scene* GameMain::scene()
//{
//	auto scene = Scene::create();
//
//	auto layer = GameMain::create();
//	scene->addChild(layer);
//
//	return scene;
//}




void GameMain::onEnter()
{

	Layer::onEnter();

#if 0
	Size win_size = Director::getInstance()->getWinSize();


	int nAniCnt = 0;
	int i = 0;
	do 
	{

		Armature *armature = Armature::create("Cowboy");
		if (!armature)
		{
			break;
		}

		if(nAniCnt <= 0)
			nAniCnt = armature->getAnimation()->getMovementCount();
		
		

		//
		armature->getAnimation()->playWithIndex(i);
		armature->setPosition(Vec2(VisibleRect::center().x + armature->getContentSize().width * i, armature->getContentSize().height/2));
		armature->setScale(0.3f);

		/*auto act = TintBy::create(1,255,0,0);
		auto act1 = act->reverse();
		armature->runAction(RepeatForever::create(Sequence::create(act,act1,nullptr)));*/

		
		addChild(armature);
		i++;

	} while (i < nAniCnt);

#endif

}

void GameMain::touchEvent( Ref *pSender, Widget::TouchEventType type )
{

	Size win_size = Director::getInstance()->getWinSize();

	switch (type)
	{
		case Widget::TouchEventType::ENDED:
			{
				// 触摸无效
				if (!_bTouchOK)
				{
					return;
				}

				Button* pObj = (Button*)pSender;

				auto _node_tag = pObj->getTag();
				switch (_node_tag)
				{
					// ta
				case TAG_TA:
					{

					}
					break;
				case TAG_UNK:
					{

					}
					break;
				case TAG_MIAO:
					{

					}
					break;
				case TAG_LU:
					{
						auto pop_menu = this->getParent()->getChildByTag(SceneMain::TAG_POP_LAYER);

						auto rf_ui = ReinforcePanel::create();
						rf_ui->setPosition(Vec2(win_size.width/2,win_size.height/2));
						pop_menu->addChild(rf_ui);

					}
					break;
				case TAG_CAVE:
					{
						auto pop_menu = this->getParent()->getChildByTag(SceneMain::TAG_POP_LAYER);
						CC_ASSERT(pop_menu);
						if (pop_menu)
						{
							if (pop_menu->getChildByTag(GameWorldMap::TAG_GAME_WORLD_MAP) != nullptr)
							{
								return;
							}

							// 副本
							auto map = GameWorldMap::create();
							map->setPosition(Vec2((win_size.width - map->getContentSize().width)/2,
								(win_size.height - map->getContentSize().height)/2));
							pop_menu->addChild(map);


							map->setScale(0.1f);
							map->runAction(EaseSineOut::create(ScaleTo::create(0.2f,1)));

							StackLayerMgr::getInstance()->beginStackLayer();
							StackLayerMgr::getInstance()->pushLayer(map);
						}


						auto gl = (GuideLayer*)Director::getInstance()->getRunningScene()->getChildByTag(GuideLayer::TAG_GUIDE_NODE);
						if (gl)
						{
							gl->nextStep(GameDefine::cfg_Guide_Info::GEM_DONE);
						}

					}
					break;
				case TAG_SHOP:
					{

					}
					break;
				default:
					break;
				}
				

			}
			break;


		case Widget::TouchEventType::MOVED:
			{
				Button* pObj = (Button*)pSender;
				auto winSize = VisibleRect::getVisibleRect().size;


				
				auto _delta = pObj->getTouchMovePosition() - _pos;
				_pos = pObj->getTouchMovePosition();
				if (_delta.lengthSquared() > TOUCH_IDENTIFY_INTERVAL)
				{
					CCLOG("delta:(%f,%f)",_delta.x,_delta.y);

					_bTouchOK = false;
					auto _cur_scene = Director::getInstance()->getRunningScene();
					if (!_cur_scene)
					{
						return;
					}

					auto _map = _cur_scene->getChildByTag(SceneMain::TAG_MAP_LAYER);
					auto currentPos = _map->getPosition();

					_delta.y = 0;
					// 做下边界处理
					if (_delta.x > 0 && currentPos.x <= 0)
					{
						_delta.x = MIN(_delta.x,-currentPos.x);
					}

					float dt = _map->getBoundingBox().size.width - winSize.width;
					if (_delta.x <= 0 && currentPos.x >= -dt)
					{	
						_delta.x = MAX(_delta.x,-dt - currentPos.x);
					}

					_map->setPosition(currentPos + _delta);
				}

			}
			break;

		case Widget::TouchEventType::BEGAN:
			{
				Button* pObj = (Button*)pSender;

				_pos = pObj->getTouchBeganPosition();
				_bTouchOK = true;
			}
			break;
		case Widget::TouchEventType::CANCELED:
			break;
	}
}

void GameMain::update( float fDelta )
{
	Layer::update(fDelta);

	// 每小时执行一次
	TaskManager::getInstance().update(fDelta);

	// 角色更新
	LocalPlayer::getInstance()->update(fDelta);
}

//void GameMain::onTouchesMoved( const std::vector<Touch*>& touches, Event *event )
//{
//
//}
//
//void GameMain::onTouchesBegan( const std::vector<Touch*>& touches, Event *event )
//{
//	auto pNode = event->getCurrentTarget();
//
//	auto _pick = touches[0]->getLocation();
//
//	auto pos = pNode->getPosition();
//
//	CCLOG("pos:(%f,%f)",pos.x,pos.y);
//
//}
//
//void GameMain::onTouchesEnded( const std::vector<Touch*>& touches, Event *event )
//{
//
//}



