#pragma once
#include <map>

template<typename T>
class ObjectInstanceMgr
{
public:
	ObjectInstanceMgr(void) 
	{
		init();
	}

	~ObjectInstanceMgr(void)
	{
		for (typename std::map<int,T*>::iterator _iter = m_inst.begin();
			_iter != m_inst.end(); _iter++)
		{
			CC_SAFE_DELETE(_iter->second);
		}

		m_inst.clear();
		CC_SAFE_DELETE(m_s_instance);
	}


	static ObjectInstanceMgr* getInstance()
	{
		if (!m_s_instance)
		{
			m_s_instance = new ObjectInstanceMgr();
		}
		return m_s_instance;
	}


	void init();


	T* getHandler(int ts_type)
	{
		if (m_inst.empty())
		{
			return nullptr;
		}

		typename std::map<int,T*>::iterator _iter = m_inst.find(ts_type);
		if (_iter != m_inst.end())
		{
			return _iter->second;
		}
		return nullptr;
	}


private:
	std::map<int,T*> m_inst;
	static ObjectInstanceMgr* m_s_instance;
};
