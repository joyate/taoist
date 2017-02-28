#include "Utility.h"
//#include "cocostudio/CocoStudio.h"
//
//
//using namespace cocostudio;





bool Utility::intersectsRect( const Rect& _lh,const Rect& _rh,int type)
{
	Rect lh = _lh;
	Rect rh = _rh;

	shrinkRect(lh,type);
	shrinkRect(rh,type);

	return lh.intersectsRect(rh);
}



void Utility::registerTouchEvent( Widget* _root,const std::string& widget_path,Widget::ccWidgetTouchCallback _callback )
{
	if (!_root || widget_path.empty() || !_callback)
	{
		return;
	}


	Widget* last_widget = findWidget(_root,widget_path);
	if (last_widget)
	{
		if(!last_widget->isTouchEnabled())
		{
			last_widget->setTouchEnabled(true);
		}
		last_widget->addTouchEventListener(_callback);
	}
}


Widget* Utility::findWidget( Widget* _root,const std::string& widget_path )
{

	if (!_root || widget_path.empty())
	{
		return nullptr;
	}

	size_t last_pos = 0;
	Widget* last_widget = _root;
	do 
	{
		size_t cur_pos = widget_path.find_first_of('/',last_pos);
	
		// 当cur_pos == npos 意味着到了最后一个节点
		last_widget = (Widget*)last_widget->getChildByName(widget_path.substr(last_pos,cur_pos - last_pos));
		if (!last_widget)
		{
			break;
		}

		if (cur_pos == std::string::npos)
		{
			break;
		}

		last_pos = cur_pos + 1;

	} while (true);

	return last_widget;
}



bool Utility::parseEffect(const std::string strCfgEffect,std::vector<std::string>& out)
{
	if (strCfgEffect.empty() || strCfgEffect == "null")
	{
		return false;
	}


	int lpos = strCfgEffect.find_first_of('.');
	int rpos = strCfgEffect.find_last_of('.');

	if (lpos != rpos)
	{
		CCLOG("effect parse failed,config error: %s",strCfgEffect.c_str());
		return false;
	}


	out.push_back(strCfgEffect.substr(0,lpos));
	out.push_back(strCfgEffect.substr(lpos+1));

	return true;
}


