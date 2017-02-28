#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


/*
 *	英雄查看面板主界面
 *
 */



class ObjInfoDetailPanel;

class HeroInfoMain : public Widget
{
public:
	HeroInfoMain();
	~HeroInfoMain();



	bool init();


	/*
	 * @desc 从实例id初始化
	 * @param _inst_id 卡牌实例id
	 * @return
	 *	
	 */
	void initWithInstId(int _inst_id);


	// 设置等级
	void setLevel(int _lvl);
	// 设置经验
	void setExp(unsigned int _exp);
	// 设置战斗力
	void setFight(int _ft);
	// 设置五行
	void setFeType(int _fe);
	// 设置魂石
	void setGhost(int _gh, int _gh_max);
	// 设置全身像
	void setFullPic(const char* _path);


	CREATE_FUNC(HeroInfoMain);

protected:


	// 按钮点击事件
	void btnTouchEvent(Ref *pSender, Widget::TouchEventType type);
	
	
	// 图片点击事件
	void imgTouchEvent(Ref *pSender, Widget::TouchEventType type);


	//
	void WidgetCallback( Node* sender );

private:
	Layout* m_layout;

	//
	ObjInfoDetailPanel* m_info_detail;
};

