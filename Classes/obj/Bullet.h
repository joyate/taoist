#pragma once
#include "../ai/GameEntity.h"


/*
 * �ӵ���
 * 
 * ������������Ϸ��λ
 * ֧��sprite,armature
 *	
 */




class Bullet : public GameEntity
{
public:

	Bullet(void);
	virtual ~Bullet(void);


	// ��������
	enum BBT_TYPE
	{
		BODY_TYPE_SPRITE,
		BODY_TYPE_ARMATURE,
	};



	/*
	 * @desc ��ʼ���ӵ�����
	 * @param _bid bullet���ݱ�id
	 * @return
	 *	
	 */
	void initObj(int _bid,int sk_id );



	//
	bool changeState( unsigned int mask, const Telegram& telegram );


	// 
	//virtual Rect getBoundingBox() const override;

	// ˭�����ӵ�
	int getOwnerId()	{ return m_onwer_id;}


	//
	void run_tick(float dt);




	// ��ʧ����
	void deadCallback();


	// 
	virtual void runTo(const Vec2& _dest);

	// ����ӵ����id
	void setOwnerInfo(GameEntity* _owner)
	{
		if (_owner)
		{
			m_onwer_id = _owner->getID();
			m_type |= _owner->getMainType();
		}

		// ����ǽ�����������
		if (_owner->getMainType() & GameEntity::OT_OFFENSIVE)
		{
			this->setScaleX(-1 * this->getScaleX());
		}
	}


	//
	CREATE_FUNC(Bullet);

protected:


	/*
	 * @desc �����ӵ������ļ��й���path��Ϣ
	 * @param _cfgNames path�����ֶ�
	 * @return *.png -> Sprite, * -> Armature
	 *	
	 */
	Node* parseBody(const std::string& _cfgNames);



	// ����Born״̬��Summer����
	void filterBorningStatus(std::vector<GameEntity*>& _out);


private:
	int m_from_skill_id;				// ���ӵ�Ч�����Ǹ����ܳ����ģ��˺�����ʱʹ��
	int m_onwer_id;						// ˭����ĸ��ӵ�
	BBT_TYPE m_body_type;				// ��������
};



