#pragma once
#include "cocos2d.h"


USING_NS_CC;


class PokerMenu : public Node
{
public:
	PokerMenu(void);
	~PokerMenu(void);

	enum class State
	{
		WAITING,
		TRACKING_TOUCH,
	};

	enum
	{
		MENU_ITEM_PADDING = 1,
	};


	static PokerMenu* createWithArray(const Vector<MenuItem*>& arrayOfItems);



	void show();
	void hide();

	inline void setHidePosition(const Vec2& _dest)			{ _dest_hiden_pos = _dest;}



	virtual void onExit() override;

public:

	virtual bool isEnabled() const { return _enabled; }
	virtual void setEnabled(bool value) { _enabled = value; };

	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	virtual void onTouchCancelled(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);



protected:

	bool initWithArray(const Vector<MenuItem*>& arrayOfItems);

	MenuItem* getItemForTouch(Touch * touch);

	Vec2 _dest_hiden_pos;
	State _state;
	bool _enabled;
	MenuItem *_selectedItem;

};

