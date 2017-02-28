#include "UISkillDesc.h"
#include "cocostudio/CocoStudio.h"
#include "../data/GameData.h"
#include "../utility/Utility.h"

using namespace cocostudio;

UISkillDesc::UISkillDesc(void)
{
}


UISkillDesc::~UISkillDesc(void)
{
}



bool UISkillDesc::init()
{
	if (!Widget::init())
	{
		return false;
	}


	m_layout = (Layout*)GUIReader::getInstance()->widgetFromJsonFile("SkillDesc/SkillDesc.ExportJson");
	this->setContentSize(m_layout->getContentSize());

	this->addChild(m_layout);


	return true;
}




void UISkillDesc::initWithSkillId( int _sk_id,int _lvl /*= 1*/ )
{

	auto sk_info = g_SkillInfoMgr.getObject(_sk_id);
	if (!sk_info)
	{
		CCLOG("skill id %d no data",_sk_id);
		return;
	}


	auto sk_desc = (Text*)Utility::findWidget(m_layout,"sk_desc");
	if (sk_desc)
	{
		sk_desc->setString(sk_info->szSkillDesc);
		sk_desc->setFontSize(SD_FONT_SIZE);
		sk_desc->setTextAreaSize(Size(240,50));
	}
}
