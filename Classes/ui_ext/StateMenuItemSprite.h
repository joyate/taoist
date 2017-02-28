#pragma once
#include "cocos2d.h"


USING_NS_CC;


/*
 * ����״̬�Ĳ˵���
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


	// ���ü���״̬
	void setActiveState(bool bActive);
	
	
	void setOriginalPos(Vec2 _pos)			{ m_original_pos = _pos;}
	const Vec2& getOriginalPos() const		{ return m_original_pos;}

protected:
	Vec2 m_original_pos;			// ԭʼ�����
	bool m_bActive;
	Node* _stateImage;
};

