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
	 * @desc 根据实例id获取tItemInfo
	 * @param _inst_id 实例id
	 * @return 实例物品数据
	 *	
	 */
	tItemInfo* getItemById(int inst_id)
	{
		return m_bag.getItem(inst_id);
	}


	/*
	 * @desc 根据物品id移除物品
	 * @param _inst_id 实例id
	 * @return 是否移除成功
	 *	
	 */
	bool removeItemById(int inst_id)
	{
		return m_bag.removeItem(inst_id);
	}




	/*
	 * @desc 添加某个物品
	 * @param tItemInfo 物品数据
	 * @return 是否添加成功
	 *	
	 */
	bool addItem(tItemInfo* _item);



	/*
	 * @desc 根据物品模板id,添加物品，
	 * @param _item_temp_id 物品模板id
	 * @param _cnt 添加数量
	 * @return 添加数量
	 *	
	 */
	int addTempItem(int _item_temp_id,int _cnt = 1);




	// 背包是否满了
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
