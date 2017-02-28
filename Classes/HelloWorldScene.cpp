#include "HelloWorldScene.h"
#include "MyBodyParser.h"
#include "TestPhysicScene.h"
#include "VisibleRect.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = TestPhysicScene::create();

	//enable debug draw
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);



	auto node = Node::create();
	node->setPhysicsBody(PhysicsBody::createEdgeBox(VisibleRect::getVisibleRect().size));
	node->setPosition(VisibleRect::center());
	scene->addChild(node);


    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    // auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    // sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    // this->addChild(sprite, 0);


	// ejoy add ------
	status_label = Label::create("Touch anywhere!", "Arial", 36);
	status_label->setPosition(Point(origin.x + visibleSize.width/2, 1.2*status_label->getContentSize().height));
	this->addChild(status_label);


	// add "2dx.png"
	sp_2dx = Sprite::create("2dx.png");

	// position the sprite on the center of the screen
	sp_2dx->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	//load
	MyBodyParser::getInstance()->parseJsonFile("test.json");

	//bind physicsbody to sprite
	auto _body = MyBodyParser::getInstance()->bodyFormJson(sp_2dx, "2dx");
	if (_body != nullptr) {
		//_body->setDynamic(false); //set it static body.
		//_body->setCollisionBitmask(0x000000); //don't collision with anybody.
		sp_2dx->setPhysicsBody(_body);
	}

	// add the sprite as a child to this layer
	this->addChild(sp_2dx, 0);
	 
	//add touchListener
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);



    
    return true;
}



bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	auto current_node = nodeUnderTouch(touch);

	//get it!
	if (current_node == sp_2dx)
	{
		status_label->setColor(Color3B::GREEN);
		status_label->setString("Ohoo, U catch me!");
	}
	else
	{
		status_label->setColor(Color3B::RED);
		status_label->setString("Haha, touch outside!");
	}

	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	status_label->setColor(Color3B::WHITE);
	status_label->setString("Touch anywhere!");
}


Node* HelloWorld::nodeUnderTouch(cocos2d::Touch *touch)
{
	Node* node = nullptr;
	//ת����layer�ڵ�����
	auto location = this->convertTouchToNodeSpace(touch);
	//�õ���ǰ���·�������shapes
	auto scene = Director::getInstance()->getRunningScene();
	auto arr = scene->getPhysicsWorld()->getShapes(location);

	//������ǰ�����������shapes, ������û�����ǵ�2dx!
	for (auto& obj : arr)
	{
		//find it
		if ( obj->getBody()->getNode() == sp_2dx)
		{
			node = obj->getBody()->getNode();
			break;
		}
	}
	return node;
}




void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
