#include "StateMenuItemSprite.h"


const unsigned int    kStateTag = 0x4;


StateMenuItemSprite::StateMenuItemSprite(void):
	m_bActive(false),
	_stateImage(nullptr)
{
}


StateMenuItemSprite::~StateMenuItemSprite(void)
{
}



void StateMenuItemSprite::setStateImage( Node* image )
{
	if (image != _stateImage)
	{
		if (image)
		{
			// ·ÅÔÚÓÒÉÏ½Ç
			image->setPosition(
				Vec2(this->getContentSize().width - image->getContentSize().width,
				this->getContentSize().height - image->getContentSize().height/2));

			addChild(image, 0, kStateTag);
			image->setVisible(m_bActive);
			//image->setAnchorPoint(Vec2(0, 0));
		}

		if (_stateImage)
		{
			removeChild(_stateImage, true);
		}

		_stateImage = image;
		this->updateImagesVisibility();
	}
}

void StateMenuItemSprite::setActiveState( bool bActive )
{
	if (bActive != m_bActive)
	{		
		if(_stateImage) _stateImage->setVisible(bActive);
		m_bActive = bActive;
	}
}

StateMenuItemSprite * StateMenuItemSprite::create( Node* normalSprite, Node* selectedSprite, Node* stateSprite,const ccMenuCallback& callback )
{
	return StateMenuItemSprite::create(normalSprite,selectedSprite,nullptr,stateSprite,callback);
}



StateMenuItemSprite * StateMenuItemSprite::create( Node* normalSprite, Node* selectedSprite, Node* disabledSprite, Node* stateSprite,const ccMenuCallback& callback )
{
	StateMenuItemSprite *ret = new StateMenuItemSprite();
	ret->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, callback);

	if (stateSprite)
	{
		ret->setStateImage(stateSprite);
	}
	
	ret->autorelease();
	return ret;
}



