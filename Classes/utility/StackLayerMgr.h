#pragma once
#include "cocos2d.h"


USING_NS_CC;

class StackLayer;

class StackLayerMgr
{
public:
	StackLayerMgr(void);
	~StackLayerMgr(void);


	static StackLayerMgr* getInstance();


	// 开启一个层叠级
	void beginStackLayer();
	
	// 压入节点
	void pushLayer(Node* _node);
	void popLayer();


protected:

	// 这个有系统自动调用
	void endStackLayer();

private:
	Vector<StackLayer*> m_vec_sl;
};
