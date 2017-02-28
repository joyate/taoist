#pragma once
#include "../ai/GameEntity.h"


/*
 * 子弹类
 * 
 * 有限生命的游戏单位
 * 支持sprite,armature
 *	
 */




class Bullet : public GameEntity
{
public:

	Bullet(void);
	virtual ~Bullet(void);


	// 主体类型
	enum BBT_TYPE
	{
		BODY_TYPE_SPRITE,
		BODY_TYPE_ARMATURE,
	};



	/*
	 * @desc 初始化子弹类型
	 * @param _bid bullet数据表id
	 * @return
	 *	
	 */
	void initObj(int _bid,int sk_id );



	//
	bool changeState( unsigned int mask, const Telegram& telegram );


	// 
	//virtual Rect getBoundingBox() const override;

	// 谁发的子弹
	int getOwnerId()	{ return m_onwer_id;}


	//
	void run_tick(float dt);




	// 消失处理
	void deadCallback();


	// 
	virtual void runTo(const Vec2& _dest);

	// 设置拥有者id
	void setOwnerInfo(GameEntity* _owner)
	{
		if (_owner)
		{
			m_onwer_id = _owner->getID();
			m_type |= _owner->getMainType();
		}

		// 如果是进攻方，反向
		if (_owner->getMainType() & GameEntity::OT_OFFENSIVE)
		{
			this->setScaleX(-1 * this->getScaleX());
		}
	}


	//
	CREATE_FUNC(Bullet);

protected:


	/*
	 * @desc 解析子弹配置文件中关于path信息
	 * @param _cfgNames path配置字段
	 * @return *.png -> Sprite, * -> Armature
	 *	
	 */
	Node* parseBody(const std::string& _cfgNames);



	// 过滤Born状态的Summer对象
	void filterBorningStatus(std::vector<GameEntity*>& _out);


private:
	int m_from_skill_id;				// 该子弹效果从那个技能出来的，伤害结算时使用
	int m_onwer_id;						// 谁发射的该子弹
	BBT_TYPE m_body_type;				// 主体类型
};



