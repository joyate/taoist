#pragma once
#include <assert.h>
#include <vector>



class TaoIStream
{
public:
	TaoIStream(unsigned char* _buff,int _len):
		m_data_ptr(_buff),
		m_data_len(_len),
		m_cur_index(0)
	{
	}


	~TaoIStream(void)
	{
	}



	template<typename T>
	TaoIStream& operator >> (T& _var)
	{
		assert(m_cur_index+(short)sizeof(T) <= m_data_len);
		memmove(&_var,m_data_ptr+m_cur_index,sizeof(T));
		m_cur_index += sizeof(T);

		return *this;
	}
	

	TaoIStream& operator >> (char* _array)
	{
		unsigned short len = *(unsigned short*)(m_data_ptr+m_cur_index);
		assert(m_cur_index + len <= m_data_len);
		m_cur_index += sizeof(unsigned short);

		memmove(_array,m_data_ptr + m_cur_index, len);
		_array[len] = 0;
		m_cur_index += len;

		return *this;
	}



	/*
	 *	跳过_size大小缓存
	 */
	void Skip(int _size)
	{
		assert(m_cur_index + _size <= m_data_len);
		m_cur_index += _size;
	}


	/*
	 * 返回缓冲区大小
	 */
	int GetSize() const
	{
		return m_cur_index;
	}



private:
	int m_cur_index;			// 当前数据指针位置
	int m_data_len;				// 数据长度
	unsigned char* m_data_ptr;		// 数据指针
};

