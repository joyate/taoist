#include "ISkillExecBase.h"
#include "../data/GameData.h"
#include "SkillInstance.h"
#include "../obj/Bullet.h"
#include "../frame/BattleScene.h"
#include "../frame/MapManager.h"
#include "../ai/MessageDispatcher.h"
#include "../obj/Defender.h"
#include "../obj/Zombie.h"
#include "../obj/Summoner.h"
#include "../component/Effect.h"






ISkillExecBase::~ISkillExecBase()
{

}




void NormalSkillExec::onExec(GameEntity* _ge,Skill* _skill)
{
	
	auto skill_info = g_SkillInfoMgr.getObject(_skill->getID());
	if (!skill_info)
	{
		CCLOG("skill %d has no data",_skill->getID());
		return;
	}

	std::vector<GameEntity*> out;

	auto scene = (BattleScene*)Director::getInstance()->getRunningScene();
	auto& vec_targets = _skill->getTargetIds();	
	for (auto _tar_id : vec_targets)
	{
		auto target = scene->getCurMapMgr().GetGameObject(_tar_id);

		if (!target)
		{
			CCLOG("game entity id %d nullptr",_tar_id);
			continue;
		}

		out.push_back(target);
	}


	if (!out.empty())
	{
		auto dmg = ObjectInstanceMgr<ISkillDamage>::getInstance()->getHandler(skill_info->damage_type);
		if (!dmg)
		{
			CCLOG("skill %d has no damage type",skill_info->id);
			return;
		}

		dmg->init(*skill_info); // 这只有在单线程下有效
		dmg->handleDamage(_ge,out);
	}

}



void ShootSkillExec::onExec( GameEntity* _ge,Skill* _skill)
{
	auto skill_info = g_SkillInfoMgr.getObject(_skill->getID());
	if (!skill_info)
	{
		CCLOG("skill %d has no data",_skill->getID());
		return;
	}


	auto _bullet_info = g_BulletInfoMgr.getObject(skill_info->emit_id);
	if (!_bullet_info)
	{
		CCLOG("skill %d has no bullet info %d",skill_info->id,skill_info->sk_exec_type);
		return;
	}

	Vec2 pos = getEmitPos(_ge);

	auto bullet = Bullet::create();
	bullet->initObj(_bullet_info->id,skill_info->id);
	bullet->setPosition(pos);
	bullet->setOwnerInfo(_ge);


	auto scene = (BattleScene*)Director::getInstance()->getRunningScene();
	scene->getCurMapMgr().enterMap(bullet);


	GameDefine::state_attr sa;
	sa.mask = GameDefine::state_attr::SA_DEST_MASK;
	float dir = _ge->getMainType() == GameEntity::OT_DEFENDER ? 1.0f:-1.0f;
	sa.dest = Vec2(pos.x + dir*_bullet_info->distance,pos.y);


	MessageDispatcher::Instance()->DispatchMsg(-1,bullet,bullet,M_RUN,(void*)&sa);

}



Vec2 ShootSkillExec::getEmitPos( GameEntity* _ge )
{
	if (!_ge)
	{
		return Vec2::ZERO;
	}

	Rect rect = _ge->getBoundingBox();

	Vec2 _pos = Vec2(rect.origin.x,rect.origin.y + MIN(rect.size.height/2,MapManager::GRID_HEIGHT_LEN));
	
	// 根据释放者的大类别，也就是方向问题，初始化子弹的起点
	if(_ge->getMainType() & GameEntity::OT_DEFENDER)
	{
		_pos.x += rect.size.width;
	}

	return _pos;
}




//////////////////////////////////////////////////////////////////////////
// 选择目标点技能
//////////////////////////////////////////////////////////////////////////


void TargetPosSkillExec::onExec( GameEntity* _ge,Skill* _skill )
{
	auto skill_info = g_SkillInfoMgr.getObject(_skill->getID());
	if (!skill_info)
	{
		CCLOG("skill %d has no data",_skill->getID());
		return;
	}


	if (_skill->getTargetPos().isZero())
	{
		CCLOG("target pos is invalid");
		return;
	}


	auto ts = ObjectInstanceMgr<ITargetSelect>::getInstance()->getHandler(skill_info->tar_sel_type);
	if (!ts)
	{
		CCLOG("target select type %d no data",skill_info->tar_sel_type);
		return;
	}

	int nCount = ts->handleSelect(_ge,_skill);
	if (nCount > 0)
	{

		std::vector<GameEntity*> out;

		auto scene = (BattleScene*)Director::getInstance()->getRunningScene();
		auto& vec_targets = _skill->getTargetIds();	
		for (auto _tar_id : vec_targets)
		{
			auto target = scene->getCurMapMgr().GetGameObject(_tar_id);

			if (!target)
			{
				CCLOG("game entity id %d nullptr",_tar_id);
				continue;
			}

			out.push_back(target);
		}

		
		auto dmg = ObjectInstanceMgr<ISkillDamage>::getInstance()->getHandler(skill_info->damage_type);
		if (!dmg)
		{
			CCLOG("skill %d has no damage type",skill_info->id);
			return;
		}

		dmg->init(*skill_info); // 这只有在单线程下有效
		dmg->handleDamage(_ge,out);
	}

}


void EnergyDouSkillExec::onExec( GameEntity* _ge,Skill* _skill )
{
	auto scene = (BattleScene*)Director::getInstance()->getRunningScene();

	auto& vec_targets = _skill->getTargetIds();	
	for (auto _tar_id : vec_targets)
	{
		auto target = scene->getCurMapMgr().GetGameObject(_tar_id);

		if (!target)
		{
			CCLOG("game entity id %d nullptr",_tar_id);
			return;
		}

		auto defender = static_cast<Defender*>(target);
		defender->usePrivateSkill();
	}
}



void SummonSkillExec::onExec( GameEntity* _ge,Skill* _skill )
{
	auto skill_info = g_SkillInfoMgr.getObject(_skill->getID());
	if (!skill_info)
	{
		CCLOG("skill %d has no data",_skill->getID());
		return;
	}


	if (_skill->getTargetPos().isZero())
	{
		CCLOG("target pos is invalid");
		return;
	}

	//
	auto scene = (BattleScene*)Director::getInstance()->getRunningScene();
	
	GameEntity* sum_obj = nullptr;
	if (_ge->getMainType() & GameEntity::OT_DEFENDER)
	{
		// 
		auto def = createSummoner((Defender*)_ge);

		CC_ASSERT(skill_info->sk_vals[SK_VAR_LIVE_TIME_INDEX] > 1.0f);
		def->setLifeTime(skill_info->sk_vals[SK_VAR_LIVE_TIME_INDEX]);

		sum_obj = def;
	}
	else if(_ge->getMainType() & GameEntity::OT_OFFENSIVE)
	{
		auto off = createSummoner((Zombie*)_ge);

		CC_ASSERT(skill_info->sk_vals[SK_VAR_LIVE_TIME_INDEX] > 1.0f);
		off->setLifeTime(skill_info->sk_vals[SK_VAR_LIVE_TIME_INDEX]);

		sum_obj = off;
	}


	if (!sum_obj)
	{
		CCLOG("not compatable owner type");
		return;
	}
	
	// 这里共用了buff_id,这里作为召唤对象id
	sum_obj->initCardId(skill_info->sk_vals[SK_VAR_SUMMONER_ID_INDEX]);

	auto rect_idx = scene->getCurMapMgr().getVec2Rect(_skill->getTargetPos());
	scene->getCurMapMgr().putObjectInGrid(rect_idx,sum_obj);

	// 召唤物出现了
	MessageDispatcher::Instance()->DispatchMsg(-1,(GameEntity*)sum_obj,(GameEntity*)sum_obj,M_BORN,nullptr);

}




void BuffSkillExec::onExec( GameEntity* _ge,Skill* _skill )
{
	auto skill_info = g_SkillInfoMgr.getObject(_skill->getID());
	if (!skill_info)
	{
		CCLOG("skill %d has no data",_skill->getID());
		return;
	}


	//CC_ASSERT(skill_info->buff_id > 0 && "buff id is invalid");
	if (skill_info->buff_id < 0)
	{
		CCLOG("summon obj id %d is invalid",skill_info->buff_id);
		return;
	}



	auto scene = (BattleScene*)Director::getInstance()->getRunningScene();
	auto& vec_targets = _skill->getTargetIds();	
	for (auto _tar_id : vec_targets)
	{
		auto target = scene->getCurMapMgr().GetGameObject(_tar_id);

		if (!target)
		{
			CCLOG("game entity id %d nullptr",_tar_id);
			continue;
		}

		bool bRet = target->handleGotBuff(skill_info->buff_id);
		if (!bRet)
		{
			CCLOG("obj id %d use skill id %d active buff id %d failed",
				_ge->getID(), skill_info->id,skill_info->buff_id);
		}

	}
}



void PosSummonSkillExec::onExec( GameEntity* _ge,Skill* _skill )
{
	auto skill_info = g_SkillInfoMgr.getObject(_skill->getID());
	if (!skill_info)
	{
		CCLOG("skill %d has no data",_skill->getID());
		return;
	}

	//
	auto scene = (BattleScene*)Director::getInstance()->getRunningScene();


	GameEntity* sum_obj = nullptr;
	if (_ge->getMainType() & GameEntity::OT_DEFENDER)
	{
		// 
		auto def = createSummoner((Defender*)_ge);

		CC_ASSERT(skill_info->sk_vals[SK_VAR_LIVE_TIME_INDEX] > 1.0f);
		def->setLifeTime(skill_info->sk_vals[SK_VAR_LIVE_TIME_INDEX]);

		sum_obj = def;
	}
	else if(_ge->getMainType() & GameEntity::OT_OFFENSIVE)
	{
		auto off = createSummoner((Zombie*)_ge);

		CC_ASSERT(skill_info->sk_vals[SK_VAR_LIVE_TIME_INDEX] > 1.0f);
		off->setLifeTime(skill_info->sk_vals[SK_VAR_LIVE_TIME_INDEX]);

		sum_obj = off;
	}


	if (!sum_obj)
	{
		CCLOG("not compatable owner type");
		return;
	}

	// 这里共用了buff_id,这里作为召唤对象id
	sum_obj->initCardId((int)skill_info->sk_vals[SK_VAR_SUMMONER_ID_INDEX]);

	Vec2 pos = _ge->getPosition() + Vec2(skill_info->ts_vals[TS_VAR_TARGET_DISTANCE_INDEX],0);
	auto rect_idx = scene->getCurMapMgr().getVec2Rect(pos);
	scene->getCurMapMgr().putObjectInGrid(rect_idx,sum_obj);

	// 召唤物出现了
	MessageDispatcher::Instance()->DispatchMsg(-1,(GameEntity*)sum_obj,(GameEntity*)sum_obj,M_BORN,nullptr);

}



void SelfExplodeSkillExec::onExec( GameEntity* _ge,Skill* _skill )
{
	auto skill_info = g_SkillInfoMgr.getObject(_skill->getID());
	if (!skill_info)
	{
		CCLOG("skill %d has no data",_skill->getID());
		return;
	}

	std::vector<GameEntity*> out;

	auto scene = (BattleScene*)Director::getInstance()->getRunningScene();
	auto& vec_targets = _skill->getTargetIds();	
	for (auto _tar_id : vec_targets)
	{
		auto target = scene->getCurMapMgr().GetGameObject(_tar_id);

		if (!target)
		{
			CCLOG("game entity id %d nullptr",_tar_id);
			continue;
		}

		out.push_back(target);
	}


	if (!out.empty())
	{
		auto dmg = ObjectInstanceMgr<ISkillDamage>::getInstance()->getHandler(skill_info->damage_type);
		if (!dmg)
		{
			CCLOG("skill %d has no damage type",skill_info->id);
			return;
		}

		dmg->init(*skill_info); // 这只有在单线程下有效
		dmg->handleDamage(_ge,out);
	}

	//
	_ge->decreaseHp(_ge->getHp());
}
