#pragma once
#include "cocos2d.h"


USING_NS_CC;


/*
 * 带有状态的菜单项
 *
 *
 */





class StateMenuItemSprite : public MenuItemSprite
{
public:
	StateMenuItemSprite(void);
	~StateMenuItemSprite(void);


	//
	static StateMenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, Node* stateSprite,const ccMenuCallback& callback);

	//
	static StateMenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Node* stateSprite,const ccMenuCallback& callback);


	//
	void setStateImage(Node* image);
	inline Node* getStateImage() const		{ return _stateImage;}


	// 设置激活状态
	void setActiveState(bool bActive);
	
	
	void setOriginalPos(Vec2 _pos)			{ m_original_pos = _pos;}
	const Vec2& getOriginalPos() const		{ return m_original_pos;}

protected:
	Vec2 m_original_pos;			// 原始坐标点
	bool m_bActive;
	Node* _stateImage;
};

