#pragma once
#include <map>
#include <assert.h>


template <typename T>
class ObjectManager
{
public:
	~ObjectManager(void)
	{
		for(auto _iter = m_data.begin(); _iter != m_data.end(); _iter++)
		{
			delete _iter->second;
		}

		m_data.clear();
	}


	const T* getObject(int _key) const
	{
		return m_data.at(_key);
	}

	T* getObject(int _key)
	{
		auto _iter = m_data.find(_key);
		if (_iter == m_data.end())
		{
			return nullptr;
		}
		return _iter->second;
	}


	bool addObject(T* _key)
	{
		if (!_key)
		{
			assert(false);
			return false;
		}

#ifdef _DEBUG
		auto _iter = m_data.find(_key->id);
		if (_iter != m_data.end())
		{
			assert(false);
			return false;
		}
#endif

		m_data.insert(std::make_pair(_key->id,_key));
		return true;
	}


	void removeObj(int _index)
	{
		auto _iter = m_data.find(_index);
		if (_iter != m_data.end())
		{
			delete _iter->second;
			m_data.erase(_index);
		}	
	}



	bool replaceObj(int id, T* _obj)
	{
		assert(m_data[id]);
		if (m_data.find(id) == m_data.end())
		{
			return false;
		}
		delete m_data[id];
		m_data[id] = _obj;
		return true;
	}


	int getSize()
	{
		return m_data.size();
	}

protected:
	std::map<int,T*> m_data;

};

