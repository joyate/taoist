LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/extensions)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
				   ../../Classes/TestPhysicScene.cpp \
				   ../../Classes/MyBodyParser.cpp \
				   ../../Classes/VisibleRect.cpp \
				   ../../Classes/GameDefine.cpp \
				   ../../Classes/obj/Hero.cpp \
				   ../../Classes/obj/Defender.cpp \
				   ../../Classes/obj/Zombie.cpp \
				   ../../Classes/obj/Bullet.cpp \
				   ../../Classes/obj/Summoner.cpp \
				   ../../Classes/frame/GameMain.cpp \
				   ../../Classes/frame/GameScene.cpp \
				   ../../Classes/frame/BattleScene.cpp \
				   ../../Classes/frame/ITriggerBase.cpp \
				   ../../Classes/frame/LoadingScene.cpp \
				   ../../Classes/frame/MapManager.cpp \
				   ../../Classes/frame/TriggerInstance.cpp \
				   ../../Classes/frame/LootMgr.cpp \
				   ../../Classes/data/RoleData.cpp \
				   ../../Classes/data/GameData.cpp \
				   ../../Classes/data/AttrChange.cpp \
				   ../../Classes/data/LocalPlayer.cpp \
				   ../../Classes/data/MsgManager.cpp \
				   ../../Classes/ai/AIState.cpp \
				   ../../Classes/ai/MessageDispatcher.cpp \
				   ../../Classes/ai/GameEntity.cpp \
				   ../../Classes/skill/DamageCalc.cpp \
				   ../../Classes/skill/ITargetSelect.cpp \
				   ../../Classes/skill/ObjectAction.cpp \
				   ../../Classes/skill/Skill.cpp \
				   ../../Classes/skill/SkillDamage.cpp \
				   ../../Classes/skill/SkillInstance.cpp \
				   ../../Classes/skill/SkillMgr.cpp \
				   ../../Classes/skill/BuffMgr.cpp \
				   ../../Classes/skill/IBuffBase.cpp \
				   ../../Classes/skill/ISkillExecBase.cpp \
				   ../../Classes/utility/Utility.cpp \
				   ../../Classes/utility/StackLayerMgr.cpp \
				   ../../Classes/game_ui/Card.cpp \
				   ../../Classes/game_ui/GameWorldMap.cpp \
				   ../../Classes/game_ui/Loading.cpp \
				   ../../Classes/game_ui/MainUI.cpp \
				   ../../Classes/game_ui/NoticeBoard.cpp \
				   ../../Classes/game_ui/StageItem.cpp \
				   ../../Classes/game_ui/UICopySelect.cpp \
				   ../../Classes/game_ui/CopyShopItem.cpp \
				   ../../Classes/game_ui/BagPanel.cpp \
				   ../../Classes/game_ui/FightUI.cpp \
				   ../../Classes/game_ui/HeroInfoPanel.cpp \
				   ../../Classes/game_ui/HeroInfoMain.cpp \
				   ../../Classes/game_ui/HeroPanel.cpp \
				   ../../Classes/game_ui/Item.cpp \
				   ../../Classes/game_ui/SideItem.cpp \
				   ../../Classes/game_ui/SkillIcon.cpp \
				   ../../Classes/game_ui/CardTip.cpp \
				   ../../Classes/game_ui/HeadUpInfo.cpp \
				   ../../Classes/game_ui/HeroItem.cpp \
				   ../../Classes/game_ui/NewStageDesc.cpp \
				   ../../Classes/game_ui/StageArmySel.cpp \
				   ../../Classes/game_ui/StageDescLayer.cpp \
				   ../../Classes/game_ui/ReinforcePanel.cpp \
				   ../../Classes/game_ui/ItemDescPanel.cpp \
				   ../../Classes/game_ui/LosePanel.cpp \
				   ../../Classes/game_ui/ObjInfoDetailPanel.cpp \
				   ../../Classes/game_ui/RewardLayer.cpp \
				   ../../Classes/game_ui/TaskItem.cpp \
				   ../../Classes/game_ui/TaskPanel.cpp \
				   ../../Classes/game_ui/SkillUpItem.cpp \
				   ../../Classes/game_ui/UISkillDesc.cpp \
				   ../../Classes/ui_ext/PokerMenu.cpp \
				   ../../Classes/ui_ext/StateMenuItemSprite.cpp \
				   ../../Classes/ui_ext/TipUI.cpp \
				   ../../Classes/ui_ext/SideItemListView.cpp \
				   ../../Classes/component/Bag.cpp \
				   ../../Classes/component/ObjFactory.cpp \
				   ../../Classes/component/TimeManager.cpp \
				   ../../Classes/component/GuideFilterMgr.cpp \
				   ../../Classes/component/GuideLayer.cpp \
				   ../../Classes/component/GuideOpInstance.cpp \
				   ../../Classes/component/IGuideOp.cpp \
				   ../../Classes/component/MsgBox.cpp \
				   ../../Classes/component/RewardShow.cpp \
				   ../../Classes/component/Effect.cpp \
				   ../../Classes/component/TaskManager.cpp \
				   ../../Classes/component/TaoResManager.cpp \
				   ../../Classes/component/AttrCalc.cpp \
				   ../../Classes/component/TaskTrigger.cpp \
				   ../../Classes/component/PopTipManager.cpp \
				   ../../Classes/ext_action/CCShake.cpp \
				   ../../Classes/ext_action/ScreenTint.cpp \
				   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
$(call import-module,editor-support/cocostudio)
# $(call import-module,network)
$(call import-module,extensions)
