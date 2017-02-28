#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;



namespace Utility
{

	enum
	{
		RECT_BOUND_VALUE_1 = 3,	// ������С����
		RECT_BOUND_VALUE_2 = 20,
	};

	enum SR_TYPE
	{
		SR_SHRINK,	// ��С
		SR_AMPLIFY,	// �Ŵ�
	};


	// ��Сrect,��Χ�� 5 pixel
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
	 * @desc �ж�2��rect�Ƿ��ཻ
	 * @param _lh
	 * @param _rh
	 * @return 
	 *	
	 */
	bool intersectsRect(const Rect& _lh,const Rect& _rh,int type = SR_SHRINK);



	/*
	 * @desc �ж�_base���Ƿ���_mask
	 * @param _base ���жϵ�
	 * @param _mask ����λ
	 * @return �� ����true, û�з���false
	 *	
	 */
	inline bool hasEvent(unsigned int _base,unsigned int _mask)
	{
		return (_base & _mask) == _mask;
	}



	/*
	 * @desc �ҵ�·��widget_path��widget��Ϊ��ע��_callback�¼�
	 * @param _root
	 * @param widget_path widget��·���� �磺"pl_root/widget"
	 * @param _callback ��ע���touch�¼�
	 * @return
	 *	
	 */
	void registerTouchEvent(Widget* _root,const std::string& widget_path,Widget::ccWidgetTouchCallback _callback);




	/*
	 * @desc �ҵ�widget_path��widget
	 * @param _root widget���ڵ�
	 * @param widget_path widget��·��
	 * @return widget_path·����widget
	 *	
	 */
	Widget* findWidget(Widget* _root,const std::string& widget_path);





	/*
	 * @desc ����strCfgEffect
	 * @param strCfgEffect
	 * @param out ���ؽ����
	 * @return �Ƿ�����ɹ�
	 * @mark strCfgEffect�ĸ�ʽ���� effect_file.effect_name	
	 */
	bool parseEffect(const std::string strCfgEffect,std::vector<std::string>& out);

}


