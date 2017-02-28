#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;



class SkillIcon : public Widget
{
public:
	SkillIcon(void);
	~SkillIcon(void);



	//
	static SkillIcon* create(const std::string& skillIcon,const std::string& skillMask);


	//
	void loadTextures(const std::string& skillIcon, const std::string& skillMask,
		TextureResType texType = TextureResType::LOCAL);



	void loadTextureSkillIcon(const std::string& skillIcon,TextureResType texType = TextureResType::LOCAL);
	void loadTextureSkillMask(const std::string& skillMask,TextureResType texType = TextureResType::LOCAL);



	void setPercent(float _per);


	void onEnterColddown();

	// 是否正在冷却
	bool isBusy() const				{ return _bMaskDoing;}

protected:

	//
	bool init(const std::string& skillIcon,const std::string& skillMask,TextureResType texType = TextureResType::LOCAL);


	
	//virtual void onPressStateChangedToPressed() override;
	void cdover();

	virtual void initRenderer() override;

protected:
	//
	Node* _skillIconRender;
	Node* _skillMaskRender;

	//
	std::string _skillIconName;
	std::string _skillMaskName;

	//
	Size _skillIconTextureSize;
	Size _skillMaskTextureSize;
	
	//
	TextureResType _skillIconTexType;
	TextureResType _skillMaskTexType;


	// 遮罩正在走
	bool _bMaskDoing;
};

