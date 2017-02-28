#include "../GameDefine.h"
#include "../utility/TaoIStream.h"
#include "../utility/TaoOStream.h"


using namespace GameDefine;


class Bag
{
public:

	Bag();
	~Bag();



	void serialize(TaoOStream& _stream)
	{
		m_bag.serialize(_stream);	
	}


	void unserialize(TaoIStream& _stream)
	{
		m_bag.unserialize(_stream);
	}



	/*
	 * @desc ����ʵ��id��ȡtItemInfo
	 * @param _inst_id ʵ��id
	 * @return ʵ����Ʒ����
	 *	
	 */
	tItemInfo* getItemById(int inst_id)
	{
		return m_bag.getItem(inst_id);
	}


	/*
	 * @desc ������Ʒid�Ƴ���Ʒ
	 * @param _inst_id ʵ��id
	 * @return �Ƿ��Ƴ��ɹ�
	 *	
	 */
	bool removeItemById(int inst_id)
	{
		return m_bag.removeItem(inst_id);
	}




	/*
	 * @desc ���ĳ����Ʒ
	 * @param tItemInfo ��Ʒ����
	 * @return �Ƿ���ӳɹ�
	 *	
	 */
	bool addItem(tItemInfo* _item);



	/*
	 * @desc ������Ʒģ��id,�����Ʒ��
	 * @param _item_temp_id ��Ʒģ��id
	 * @param _cnt �������
	 * @return �������
	 *	
	 */
	int addTempItem(int _item_temp_id,int _cnt = 1);




	// �����Ƿ�����
	bool full()
	{
		return m_bag.full();
	}


	//
	const tBagInfo& getBagInfo()
	{
		return m_bag;
	}

	
private:
	tBagInfo m_bag;

	// instance_id -> item_index
	//std::map<int,int> m_item_map;
};
