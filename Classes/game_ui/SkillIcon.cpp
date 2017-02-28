#include "SkillIcon.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"

using namespace cocostudio;


SkillIcon::SkillIcon(void)
{
}


SkillIcon::~SkillIcon(void)
{
}



SkillIcon* SkillIcon::create( const std::string& skillIcon,const std::string& skillMask )
{
	SkillIcon *btn = new SkillIcon;
	if (btn && btn->init(skillIcon,skillMask)) {
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}



bool SkillIcon::init( const std::string& skillIcon,const std::string& skillMask,TextureResType texType /*= TextureResType::LOCAL*/ )
{
	bool ret = true;
	do {
		if (!Widget::init()) {
			ret = false;
			break;
		}

		this->loadTextures(skillIcon, skillMask,texType);

		//
		if (!_skillIconRender || !_skillMaskRender)
		{
			ret = false;
			break;
		}
		
	} while (0);

	return ret;
}

void SkillIcon::loadTextures( const std::string& skillIcon, const std::string& skillMask, TextureResType texType /*= TextureResType::LOCAL*/ )
{
	loadTextureSkillIcon(skillIcon,texType);
	loadTextureSkillMask(skillMask,texType);
}




void SkillIcon::loadTextureSkillIcon( const std::string& skillIcon,TextureResType texType /*= TextureResType::LOCAL*/ )
{
	if (skillIcon.empty())
	{
		return;
	}
	_skillIconName = skillIcon;
	_skillIconTexType = texType;


	Sprite* skillIconRenderer = static_cast<Sprite*>(_skillIconRender);
	switch (_skillIconTexType)
	{
	case TextureResType::LOCAL:	
		skillIconRenderer->setTexture(_skillIconName);
		break;
	case TextureResType::PLIST:
		skillIconRenderer->setSpriteFrame(_skillIconName);
		break;
	default:
		break;
	}

	skillIconRenderer->setOpacity(80);
	skillIconRenderer->setPosition(Vec2(skillIconRenderer->getContentSize().width/2,skillIconRenderer->getContentSize().height/2));
	updateContentSizeWithTextureSize(skillIconRenderer->getContentSize());

}

void SkillIcon::loadTextureSkillMask( const std::string& skillMask,TextureResType texType /*= TextureResType::LOCAL*/ )
{
	if (skillMask.empty())
	{
		return;
	}

	_skillMaskName = skillMask;
	_skillMaskTexType = texType;


	ProgressTimer* skillMaskRenderer = static_cast<ProgressTimer*>(_skillMaskRender);
	switch (_skillIconTexType)
	{
	case TextureResType::LOCAL:
		{
			auto sprite = Sprite::create(skillMask);
			skillMaskRenderer->setSprite(sprite);
		}
		break;
	case TextureResType::PLIST:
		{
			auto sprite = Sprite::create();
			sprite->setSpriteFrame(skillMask);
			skillMaskRenderer->setSprite(sprite);
		}

		break;
	default:
		break;
	}

	skillMaskRenderer->setPosition(Vec2(skillMaskRenderer->getContentSize().width/2,skillMaskRenderer->getContentSize().height/2));
	updateContentSizeWithTextureSize(skillMaskRenderer->getContentSize());
}

void SkillIcon::setPercent( float _percent )
{
	ProgressTimer* skillMaskRenderer = static_cast<ProgressTimer*>(_skillMaskRender);
	if (skillMaskRenderer)
	{
		skillMaskRenderer->setPercentage(_percent);
	}

	if (_percent > 99.9f)
	{
		_bMaskDoing = false;
	}
}

//void SkillIcon::onPressStateChangedToPressed()
//{
//
//}

void SkillIcon::cdover()
{
	_bMaskDoing = false;
}

void SkillIcon::initRenderer()
{
	_skillIconRender = Sprite::create();
	auto sprite = Sprite::create();
	_skillMaskRender = ProgressTimer::create(sprite);

	addProtectedChild(_skillIconRender, -1, -1);
	addProtectedChild(_skillMaskRender, -2, -1);
}

void SkillIcon::onEnterColddown()
{
	if (_bMaskDoing)
	{
		CCLOG("skill is colding down");
		return;
	}


	//
	auto sk_info = g_SkillInfoMgr.getObject(this->getTag());
	if (!sk_info)
	{
		CCLOG("skill id %d no data",this->getTag());
		return;
	}



	ProgressTimer* skillMaskRenderer = static_cast<ProgressTimer*>(_skillMaskRender);
	if (skillMaskRenderer)
	{
		skillMaskRenderer->runAction(
			Sequence::create(ProgressTo::create(0,0),
			ProgressTo::create(sk_info->atk_interval,100.0f),
			CallFunc::create( CC_CALLBACK_0(SkillIcon::cdover,this)),
			nullptr));
	}

	_bMaskDoing = true;
}



