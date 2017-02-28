#pragma once
#include "cocos2d.h"


USING_NS_CC;


class StackLayer : public Node
{
public:
	StackLayer()
	{
	}


	~StackLayer(void)
	{
		m_vec_items.clear();
	}



	void pushNode(Node* _node)
	{
		if (!_node)
		{
			return;
		}

		// �������㣬������
		if (!m_vec_items.empty())
		{
			auto item = m_vec_items.back();
			item ->setVisible(false);
		}

		m_vec_items.pushBack(_node);
	}


	void popNode()
	{
		if (m_vec_items.empty())
		{
			return;
		}

		// ��remove����ǰ�㣬
		auto ret = m_vec_items.back();
		m_vec_items.popBack();
		ret->removeFromParent();
		
		
		// ��ʾ��һ��
		if (!m_vec_items.empty())
		{
			auto item = m_vec_items.back();
			item ->setVisible(true);
		}
	}



	bool empty()
	{
		return m_vec_items.empty();
	}



	Node* getNodeByIndex(int _index)
	{
		return m_vec_items.at(_index);
	}


	CREATE_FUNC(StackLayer);

private:

	Vector<Node*> m_vec_items;
};

