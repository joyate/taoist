#pragma once
#include "ITargetSelect.h"
#include "SkillDamage.h"
#include "IBuffBase.h"
#include "ISkillExecBase.h"
#include "../utility/ObjectInstanceMgr.h"







typedef ObjectInstanceMgr<ITargetSelect> tSkillTargetMgr;
typedef ObjectInstanceMgr<ISkillDamage> tSkillDamageMgr;


typedef ObjectInstanceMgr<IBuffBase> tBufferMgr;
typedef ObjectInstanceMgr<ISkillExecBase> tSkillExecBaseMgr;

