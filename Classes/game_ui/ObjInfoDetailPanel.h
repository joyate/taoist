#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../GameDefine.h"

USING_NS_CC;
using namespace ui;


/*
 * 游戏对象详细信息面板
 * 
 */



class ObjInfoDetailPanel : public Widget
{
public:
	ObjInfoDetailPanel(void);
	~ObjInfoDetailPanel(void);

	// skill tips tag
	enum
	{
		SUI_SKILL_DESC_TAG = 0x0f01,
	};

	enum
	{
		ODP_VIEW_ATTR,
		ODP_VIEW_SKILL,
		ODP_VIEW_WHERE,
	};


	bool init();
	
	/*
	 * @desc 从对象id初始化，
	 * @param _id 对象id，目前是模板id
	 * @return
	 *	目前还没有实例数据，后面调整
	 */
	bool initFromInstId(int _inst_id);


	//
	void showSkillTips(int _sk_id,const Vec2& _pos);


	CREATE_FUNC(ObjInfoDetailPanel);
protected:

	// 基本属性
	void initBaseAttr(GameDefine::tCardInfo* _inst_card,GameDefine::cfg_Card* _cfg_card);
	// 技能相关
	void initSkill(GameDefine::tCardInfo* _inst_card,GameDefine::cfg_Card* _cfg_card);
	// 出处？
	void initWhere(GameDefine::tCardInfo* _inst_card,GameDefine::cfg_Card* _cfg_card);

	// 切换视图
	void updateSubView(int _vi);
	

	// 图片点击事件
	void imgTouchEvent(Ref *pSender, Widget::TouchEventType type);

private:
	Layout* m_layout;
	int m_cur_view_index;
	int m_inst_id;
};

