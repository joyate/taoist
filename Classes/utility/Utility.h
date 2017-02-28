#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;



namespace Utility
{

	enum
	{
		RECT_BOUND_VALUE_1 = 3,	// 放缩大小因子
		RECT_BOUND_VALUE_2 = 20,
	};

	enum SR_TYPE
	{
		SR_SHRINK,	// 缩小
		SR_AMPLIFY,	// 放大
	};


	// 缩小rect,周围各 5 pixel
	inline void shrinkRect(Rect& _rect, int type = SR_SHRINK)
	{
		
		if(type == SR_SHRINK)
		{
			/*Rect bound(RECT_BOUND_VALUE_1,RECT_BOUND_VALUE_1,RECT_BOUND_VALUE_1,RECT_BOUND_VALUE_1);
			_rect.origin += bound.origin;
			_rect.size = _rect.size - bound.size;*/
		}
		else
		{
			Rect bound(RECT_BOUND_VALUE_2,RECT_BOUND_VALUE_2,RECT_BOUND_VALUE_2,RECT_BOUND_VALUE_2);
			_rect.origin -= bound.origin;
			_rect.size = _rect.size + bound.size;
		}
	}


	/*
	 * @desc 判断2个rect是否相交
	 * @param _lh
	 * @param _rh
	 * @return 
	 *	
	 */
	bool intersectsRect(const Rect& _lh,const Rect& _rh,int type = SR_SHRINK);



	/*
	 * @desc 判断_base里是否含有_mask
	 * @param _base 被判断的
	 * @param _mask 掩码位
	 * @return 有 返回true, 没有返回false
	 *	
	 */
	inline bool hasEvent(unsigned int _base,unsigned int _mask)
	{
		return (_base & _mask) == _mask;
	}



	/*
	 * @desc 找到路径widget_path的widget，为其注册_callback事件
	 * @param _root
	 * @param widget_path widget的路径， 如："pl_root/widget"
	 * @param _callback 待注册的touch事件
	 * @return
	 *	
	 */
	void registerTouchEvent(Widget* _root,const std::string& widget_path,Widget::ccWidgetTouchCallback _callback);




	/*
	 * @desc 找到widget_path的widget
	 * @param _root widget根节点
	 * @param widget_path widget的路径
	 * @return widget_path路径的widget
	 *	
	 */
	Widget* findWidget(Widget* _root,const std::string& widget_path);





	/*
	 * @desc 解析strCfgEffect
	 * @param strCfgEffect
	 * @param out 返回结果集
	 * @return 是否解析成功
	 * @mark strCfgEffect的格式形如 effect_file.effect_name	
	 */
	bool parseEffect(const std::string strCfgEffect,std::vector<std::string>& out);

}


