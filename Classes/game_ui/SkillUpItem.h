#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ObjInfoDetailPanel.h"

USING_NS_CC;
using namespace ui;


/*
 * 技能子项，用于显示信息及升级	
 */


class SkillUpItem : public Widget
{
public:
	SkillUpItem(void);
	~SkillUpItem(void);


	enum
	{
		SUI_SKILL_DESC_TAG = 0x0f01,
	};



	bool init();


	/*
	 * @desc 从技能ID初始化
	 * @param _sk_id 技能id
	 * @param _sk_lvl 技能等级
	 * @return
	 *	
	 */
	bool initSkillId(int _sk_id,int _sk_lvl = 1);
	
	
	// 持有一下根面板，用来控制skill tips
	void initRootPtr(ObjInfoDetailPanel* _root)
	{
		m_panel_root = _root;
	}


	// 设置技能图标
	void setSkillIcon(const char* path);

	// 设置升级消耗
	void setUpgradeCost(int _cost);

	// 设置技能等级
	void setSkillLvl(int _lvl);

	// 设置技能名称
	void setSkillName(const char* _sk_name);


	CREATE_FUNC(SkillUpItem);
protected:

	//
	void btnTouchEvent(Ref *pSender, Widget::TouchEventType type);


	// 显示技能描述
	void showSkillDesc(Ref *pSender, Widget::TouchEventType type);

private:
	Layout* m_layout;
	int m_sk_id;
	ObjInfoDetailPanel* m_panel_root;
};

