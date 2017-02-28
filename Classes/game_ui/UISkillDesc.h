#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


class UISkillDesc : public Widget
{
public:
	UISkillDesc(void);
	~UISkillDesc(void);


	enum
	{
		SD_FONT_SIZE = 16,
	};



	bool init();


	/*
	 * @desc ³õÊ¼»¯
	 * @param _id Ä£°åid
	 * @param _lvl
	 * @return
	 *	
	 */
	void initWithSkillId(int _sk_id,int _lvl = 1);



	CREATE_FUNC(UISkillDesc);
private:
	Layout* m_layout;
};

