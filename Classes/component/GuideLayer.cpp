#include "GuideLayer.h"
#include "ui/CocosGUI.h"
#include "../data/GameData.h"
#include "../data/LocalPlayer.h"
#include "cocostudio/CocoStudio.h"
#include "../data/MsgManager.h"


const char* pngExt = ".png";
const int PNG_EXT_SIZE = 4;



using namespace cocostudio;
using namespace ui;

GuideLayer::GuideLayer(void):
	m_guide_id(0),
	m_step(0)
{
}


GuideLayer::~GuideLayer(void)
{
}


bool GuideLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GuideLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	return true;
}



bool GuideLayer::initConfig( int _guide_id )
{

	auto guide_info = g_GuideInfoMgr.getObject(_guide_id);
	if (!guide_info)
	{
		return false;
	}

	// 引导id
	m_guide_id = _guide_id;
	m_step = 0;

	m_act_rect = guide_info->mask_infos[m_step].rect;
	fixedRect(m_act_rect);


	//
	auto pClip = ClippingNode::create();
	pClip->setInverted(true);
	pClip->setTag(TAG_CLIP_NODE);
	addChild(pClip);


	auto color_layer = LayerColor::create(Color4B(0,0,0,TIPS_OPACITY));
	pClip->addChild(color_layer);


	//float sx = Director::getInstance()->getOpenGLView()->getScaleX();
	//float sy = Director::getInstance()->getOpenGLView()->getScaleY();
	float sx = 1.0f;
	float sy = 1.0f;

	//
	auto stencil = DrawNode::create();
	Color4F green(0,1,0,1);
	float width = m_act_rect.size.width*sx;
	float height = m_act_rect.size.height*sy;
	float x = m_act_rect.getMinX()*sx;
	float y = m_act_rect.getMinY()*sy;
	Vec2 rect1[4] = {Vec2(0,height),Vec2(width,height),Vec2(width,0),Vec2(0,0)};
	stencil->drawPolygon(rect1,4,green,0,green);
	stencil->setPosition(Vec2(x,y));
	pClip->setStencil(stencil);


	if(guide_info->mask_infos[m_step].ani_name[0] != 0)
	{
		float x = m_act_rect.getMidX();
		float y = m_act_rect.getMidY();

		auto _ani = Armature::create(guide_info->ani_path);
		_ani->setPosition(Vec2(x,y));
		_ani->setTag(TAG_ANIM_NODE);
		this->addChild(_ani,9);

		_ani->getAnimation()->play(guide_info->mask_infos[m_step].ani_name);
	}
	
	// 说明tips
	appendGuideTips(guide_info->mask_infos[m_step]);

	return true;
}




bool GuideLayer::onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* event )
{
	 Point touchPoint = touch->getLocation();
	 if (m_act_rect.containsPoint(touchPoint))
	 {
		 if(nextStep() != GLR_CONTINUE)
		 {
			 auto& gi = LocalPlayer::getInstance()->m_guide_info;
			 if (gi.last_guide_id < m_guide_id)
			 {
				 gi.last_guide_id = m_guide_id;
				 LocalPlayer::getInstance()->save(GameDefine::ROLE_SAVE_FILE);
			 }

			 this->removeFromParent();
		 }
		 return false;
	 }
	 return true;
}


void GuideLayer::fixedRect( Rect& _rect )
{
	Size win_size = Director::getInstance()->getWinSize();
	_rect.origin.y = win_size.height - _rect.origin.y - _rect.size.height;
}



GuideLayer::GLResult GuideLayer::nextStep(int nEvent /*= 0*/)
{
	auto guide_info = g_GuideInfoMgr.getObject(m_guide_id);
	if (!guide_info)
	{
		return GLR_FAILED;
	}

	//
	auto tips = this->getChildByTag(TAG_TIPS_NODE);
	if (tips)
	{
		tips->removeFromParent();
	}

	// 如果约定进行下一步条件控制，检查条件
	if (guide_info->mask_infos[m_step].event_mask != 0)
	{
		if (!(guide_info->mask_infos[m_step].event_mask & nEvent))
		{
			return GLR_CONTINUE;
		}
	}

	m_step++;
	if (m_step >= (int)guide_info->mask_infos.size())
	{
		return GLR_OVER;
	}

	m_act_rect = guide_info->mask_infos[m_step].rect;
	fixedRect(m_act_rect);


	auto clip_node = (ClippingNode*)this->getChildByTag(TAG_CLIP_NODE);
	if (!clip_node)
	{
		return GLR_FAILED;
	}

	Color4F green(0,1,0,1);
	float width = m_act_rect.size.width;
	float height = m_act_rect.size.height;
	float x = m_act_rect.getMinX();
	float y = m_act_rect.getMinY();
	Vec2 rect1[4] = {Vec2(0,height),Vec2(width,height),Vec2(width,0),Vec2(0,0)};

	auto stencil = (DrawNode*)clip_node->getStencil();
	stencil->clear();
	stencil->drawPolygon(rect1,4,green,0,green);
	stencil->setPosition(Vec2(x,y));


	auto _ani = (Armature*)this->getChildByTag(TAG_ANIM_NODE);
	if (_ani)
	{
		float x = m_act_rect.getMidX();
		float y = m_act_rect.getMidY();
		_ani->setPosition(Vec2(x,y));
		if (strcmp(guide_info->mask_infos[m_step].ani_name,"null"))
		{
			_ani->getAnimation()->play(guide_info->mask_infos[m_step].ani_name);
		}
		else
		{
			_ani->setVisible(false);
		}
	}


	// 说明tips
	appendGuideTips(guide_info->mask_infos[m_step]);

	return GLR_CONTINUE;
}


void GuideLayer::appendGuideTips( const GameDefine::tGuideMaskInfo& _gmi )
{

	switch (_gmi.tip_type)
	{
	case GTT_TEXT:
		{
			// 有描述
			if (_gmi.desc_id > 0)
			{
				const auto msg = MsgManager::getInstance().getMsg(_gmi.desc_id);
				if (msg)
				{
					Size win_size = Director::getInstance()->getWinSize();

					TTFConfig ttf;
					ttf.fontFilePath = "yuan.ttf";
					ttf.fontSize = 24;
					auto tips = Label::createWithTTF(ttf,msg);
					tips->setTag(TAG_TIPS_NODE);
					this->addChild(tips,9);

					// 有指示动画
					if(strcmp(_gmi.ani_name,"null"))
					{
						adjustTipsPos(_gmi.ani_name[0]);
					}
				}
			}
		}
		break;
	case GTT_IMAGE:
		{
			if (_gmi.desc_id > 0)
			{
				std::string msg = MsgManager::getInstance().getMsg(_gmi.desc_id);
				if (msg.length() > PNG_EXT_SIZE && !msg.compare(msg.length() - PNG_EXT_SIZE,PNG_EXT_SIZE,pngExt))
				{
					auto tip_image = ImageView::create(msg);
					tip_image->setTag(TAG_TIPS_NODE);
					this->addChild(tip_image,9);

					// 有指示动画
					//if(strcmp(_gmi.ani_name,"null"))
					//{
						adjustTipsImgPos(_gmi);
					//}

				}
			}
		}
	default:
		break;
	}

	
}


void GuideLayer::adjustTipsPos(char _dir )
{
	auto win_size = Director::getInstance()->getWinSize();
	auto label_tips = (Label*)this->getChildByTag(TAG_TIPS_NODE);
	if (!label_tips)
	{
		return;
	}
	Size tips_content_size = label_tips->getContentSize();
	
	auto _ani = this->getChildByTag(TAG_ANIM_NODE);
	if (!_ani)
	{
		return;
	}
	Vec2 _anim_pos = _ani->getPosition();

	switch (_dir)
	{
	case 'u':	// up
		{
			Vec2 pos;
			CC_ASSERT(_anim_pos.y + tips_content_size.height + TIPS_POS_OFFSET_Y + TIPS_POS_PADDING_Y < win_size.height);				
			pos.y = _anim_pos.y + tips_content_size.height/2 + TIPS_POS_OFFSET_Y;

			
			pos.x = _anim_pos.x - tips_content_size.width/2 < TIPS_POS_PADDING_X ? 
				tips_content_size.width/2 + TIPS_POS_PADDING_X : _anim_pos.x;
			
			label_tips->setPosition(pos);
		}
		break;
	case 'b':
		{
			Vec2 pos;
			CC_ASSERT(_anim_pos.y - tips_content_size.height - TIPS_POS_PADDING_Y - TIPS_POS_OFFSET_Y > 0);				
			pos.y = _anim_pos.y - tips_content_size.height/2 - TIPS_POS_OFFSET_Y;


			pos.x = _anim_pos.x - tips_content_size.width/2 < TIPS_POS_PADDING_X ? 
				tips_content_size.width/2 + TIPS_POS_PADDING_X : _anim_pos.x;

			label_tips->setPosition(pos);
		}
		break;
	case 'l':
		{

		}
		break;
	case 'r':
		{

		}
		break;
	default:
		break;
	}
}

void GuideLayer::adjustTipsImgPos(const GameDefine::tGuideMaskInfo& _gmi)
{
	if (_gmi.desc_id <= 0)
	{
		return;
	}

	auto win_size = Director::getInstance()->getWinSize();
	auto tips_img = (ImageView*)this->getChildByTag(TAG_TIPS_NODE);
	if (!tips_img)
	{
		return;
	}
	Size tips_content_size = tips_img->getContentSize();

	/*auto _ani = this->getChildByTag(TAG_ANIM_NODE);
	if (!_ani)
	{
	return;
	}
	Vec2 _anim_pos = _ani->getPosition();*/

	char _dir = win_size.height/2 > m_act_rect.getMidY() ? 'u' : 'b';
	switch (_dir)
	{
	case 'u':
		{
			CC_ASSERT(tips_content_size.height +m_act_rect.getMaxY() + TIPS_POS_PADDING_Y < win_size.height);
			tips_img->setPosition(Vec2(win_size.width/2,m_act_rect.getMaxY() + TIPS_POS_OFFSET_Y + tips_content_size.height/2));
		}
		break;
	case 'b':
		{
			CC_ASSERT(m_act_rect.getMinY() - tips_content_size.height - TIPS_POS_PADDING_Y > 0);
			tips_img->setPosition(Vec2(win_size.width/2,m_act_rect.getMinY() - tips_content_size.height/2 - TIPS_POS_PADDING_Y ));
		}
		break;
	default:
		break;
	}
}

