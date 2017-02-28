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


	// ����һ�������
	void beginStackLayer();
	
	// ѹ��ڵ�
	void pushLayer(Node* _node);
	void popLayer();


protected:

	// �����ϵͳ�Զ�����
	void endStackLayer();

private:
	Vector<StackLayer*> m_vec_sl;
};
