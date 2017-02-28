#include "PokerMenu.h"
#include "StateMenuItemSprite.h"

PokerMenu::PokerMenu(void)
{
}


PokerMenu::~PokerMenu(void)
{
}

PokerMenu* PokerMenu::createWithArray( const Vector<MenuItem*>& arrayOfItems )
{
	auto ret = new PokerMenu();
	if (ret && ret->initWithArray(arrayOfItems))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}

	return ret;
}

bool PokerMenu::initWithArray( const Vector<MenuItem*>& arrayOfItems )
{
	if (Node::init())
	{
		_enabled = true;

		float width = 0.0f;
		float height = 0.0f;
		int z=0;
		for(auto _iter = arrayOfItems.begin(); _iter != arrayOfItems.end(); _iter++)
		//for (auto& item : arrayOfItems)
		{
			auto item = (StateMenuItemSprite*)*_iter;
			width += item->getContentSize().width + MENU_ITEM_PADDING;
			if(height < item->getContentSize().height)
			{
				height = item->getContentSize().height;
			}

			item->setPosition(Vec2(width - item->getContentSize().width/2,height/2));
			item->setOriginalPos(item->getPosition());
			this->addChild(item, z);
			z++;
		}

		this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
		this->setContentSize(Size(width,height));

		_selectedItem = nullptr;
		_state = State::WAITING;

		// enable cascade color and opacity on menus
		setCascadeColorEnabled(true);
		setCascadeOpacityEnabled(true);


		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);

		touchListener->onTouchBegan = CC_CALLBACK_2(PokerMenu::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(PokerMenu::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(PokerMenu::onTouchEnded, this);
		touchListener->onTouchCancelled = CC_CALLBACK_2(PokerMenu::onTouchCancelled, this);

		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

		return true;

	}

	return false;
}

MenuItem* PokerMenu::getItemForTouch( Touch * touch )
{
	Vec2 touchLocation = touch->getLocation();

	if (!_children.empty())
	{
		for (auto iter = _children.crbegin(); iter != _children.crend(); ++iter)
		{
			MenuItem* child = dynamic_cast<MenuItem*>(*iter);
			if (child && child->isVisible() && child->isEnabled())
			{
				Vec2 local = child->convertToNodeSpace(touchLocation);
				Rect r = child->rect();
				r.origin = Vec2::ZERO;

				if (r.containsPoint(local))
				{
					return child;
				}
			}
		}
	}

	return nullptr;
}

bool PokerMenu::onTouchBegan( Touch* touch, Event* event )
{
	if (_state != State::WAITING || ! _visible || !_enabled)
	{
		return false;
	}

	for (Node *c = this->_parent; c != nullptr; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}

	_selectedItem = this->getItemForTouch(touch);
	if (_selectedItem)
	{
		_state = State::TRACKING_TOUCH;
		_selectedItem->selected();

		return true;
	}

	return false;
}

void PokerMenu::onTouchEnded( Touch* touch, Event* event )
{
	CCASSERT(_state == State::TRACKING_TOUCH, "[Menu ccTouchEnded] -- invalid state");
	this->retain();
	if (_selectedItem)
	{
		_selectedItem->unselected();
		_selectedItem->activate();
	}
	_state = State::WAITING;
	this->release();
}

void PokerMenu::onTouchCancelled( Touch* touch, Event* event )
{
	CCASSERT(_state == State::TRACKING_TOUCH, "[Menu ccTouchCancelled] -- invalid state");
	this->retain();
	if (_selectedItem)
	{
		_selectedItem->unselected();
	}
	_state = State::WAITING;
	this->release();
}

void PokerMenu::onTouchMoved( Touch* touch, Event* event )
{
	CCASSERT(_state == State::TRACKING_TOUCH, "[Menu ccTouchMoved] -- invalid state");
	MenuItem *currentItem = this->getItemForTouch(touch);
	if (currentItem != _selectedItem)
	{
		if (_selectedItem)
		{
			_selectedItem->unselected();
		}
		_selectedItem = currentItem;
		if (_selectedItem)
		{
			_selectedItem->selected();
		}
	}
}

void PokerMenu::onExit()
{
	if (_state == State::TRACKING_TOUCH)
	{
		if (_selectedItem)
		{
			_selectedItem->unselected();
			_selectedItem = nullptr;
		}

		_state = State::WAITING;
	}

	Node::onExit();
}




void PokerMenu::show()
{
	//this->runAction(ScaleTo::create(0.1f,1));
	this->setVisible(true);

	for(const auto &child : _children) 
	{
		child->runAction(
			Sequence::create(DelayTime::create(0.1f),
			EaseElasticOut::create(MoveTo::create(0.3f, static_cast<StateMenuItemSprite*>(child)->getOriginalPos()), 0.35f),
			nullptr) );
	}

}

void PokerMenu::hide()
{
	for(const auto &child : _children) 
	{
		float offset_x = _dest_hiden_pos.x - child->getPosition().x;

		child->runAction(
			EaseCubicActionIn::create(MoveBy::create(0.3f, Vec2(offset_x,0)))
			);
	}

	//this->runAction(Sequence::create(DelayTime::create(0.5f),ScaleTo::create(0.1f,0),nullptr));
	//this->setVisible(false);
}
