#pragma once
#include <vector>
#include "../GameDefine.h"


class GameEntity;

class BuffMgr
{
public:
	BuffMgr(GameEntity* _owner);
	~BuffMgr(void);

	typedef std::vector<GameDefine::tBuffData>::iterator buff_iter;



	//
	enum BuffEventMask
	{
		// һ�������buff,����������buff,dot buff,��
		BEM_EVENT_TIME	= 0x00000001,	// ʱ���¼�

		// ����������ʱ����
		BEM_EVENT_DEAD  = 0x00000002,	// �����¼�

		// ����������ʱ����
		BEM_EVENT_FADE	= 0x00000004,	// �����¼�

		// ������ɱ������ʱ����
		BEM_EVENT_KILL  = 0x00000008,	// ɱ���¼�
	};



	/*
	 * @desc ������buff
	 * @param _b_id buff id
	 * @param _tar �ͷ�buff��GameEntity
	 * @return
	 *	
	 */
	bool handleGotBuff(int _b_id,GameEntity* _tar); 




	// buff mgr ����
	void update(float _dt);


	/*
	* @desc �¼����
	* @param _em �¼�����
	* @param _tar �¼�Ŀ�����
	* @return
	*	
	*/
	void onEvent(unsigned int _em,GameEntity* _tar = nullptr);


protected:

	/*
	 * @desc ����buff�ǲ��ǿ��Լ�������buff��
	 * @param _b_id buff id
	 * @return ���ؿ��Է����������������ܷ��뷵��-1
	 *	
	 */
	int tryGotBuff(int _b_id);
	

private:
	GameEntity* m_owner;
	std::vector<GameDefine::tBuffData> m_buffs;
};

