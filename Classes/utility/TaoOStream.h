#pragma once
#include <vector>
#include <assert.h>

class TaoOStream
{
public:
	TaoOStream(char* _buff,int _len):
		m_data_ptr(_buff),
		m_data_len(_len),
		m_cur_index(0)
	{}


	~TaoOStream(void)
	{}




	template<typename T>
	TaoOStream& operator << (const T& _var)
	{
		assert(m_cur_index+(short)sizeof(T) <= m_data_len);
		memmove( m_data_ptr + m_cur_index,&_var,sizeof(T));
		m_cur_index += sizeof(T);

		return *this;
	}


	TaoOStream& operator << (const char* buff)
	{
		unsigned short len = strlen(buff);
		assert(m_cur_index + len + (int)sizeof(short) <= m_data_len);
		memmove(m_data_ptr + m_cur_index,&len,sizeof(unsigned short));
		m_cur_index += sizeof(unsigned short);

		memmove(m_data_ptr + m_cur_index,buff,len);
		m_cur_index += len;

		return *this;
	}



	/*
	 * ���ػ�������С
	 */
	int GetSize() const
	{
		return m_cur_index;
	}



private:
	int m_cur_index;		// ��ǰ����ָ��λ��
	int m_data_len;			// ���ݳ���
	char* m_data_ptr;		// ����ָ��
};

