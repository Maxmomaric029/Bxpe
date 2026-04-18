#include "pch.h"
#include "Reach.h"
#include "core/jvm_wrapper.h"
#include "sdk/minecraft.h"
#include "sdk/entity.h"

Reach::Reach() : Module("Reach", L"Reach", L"Increase your reach distance", ILLEGAL) {
    addSliderSetting("reach_distance", L"Reach Distance", L"Reach distance in blocks", reach_distance, FloatValue(3.f), FloatValue(6.f), FloatValue(0.1f));
    listen<UpdateEvent>(&Reach::onUpdate);
}

void Reach::onDisable() {
    JNIEnv* env = JvmWrapper::getEnv();
    if (env) {
        setReach(env, 3.0, 4.5);
    }
}

void Reach::onUpdate(Event& ev) {
    JNIEnv* env = JvmWrapper::getEnv();
    if (!env) return;

    float fReachDist = std::get<FloatValue>(reach_distance);
    setReach(env, fReachDist, fReachDist + 1.5);
}

static jclass s_attributesClass = nullptr;
static jfieldID s_entityInteractionRange = nullptr;
static jfieldID s_blockInteractionRange = nullptr;
static jclass s_livingEntityClass = nullptr;
static jmethodID s_getAttribute = nullptr;
static jclass s_attributeInstanceClass = nullptr;
static jmethodID s_setBaseValue = nullptr;

void Reach::setReach(JNIEnv* env, double entityReach, double blockReach) {
    static bool init = false;
    if (!init) {
        s_attributesClass = JvmWrapper::findClass("net/minecraft/world/entity/ai/attributes/Attributes");
        if (s_attributesClass) {
            s_entityInteractionRange = env->GetStaticFieldID(s_attributesClass, "ENTITY_INTERACTION_RANGE", "Lnet/minecraft/core/Holder;");
            s_blockInteractionRange = env->GetStaticFieldID(s_attributesClass, "BLOCK_INTERACTION_RANGE", "Lnet/minecraft/core/Holder;");
        }

        s_livingEntityClass = JvmWrapper::findClass("net/minecraft/world/entity/LivingEntity");
        if (s_livingEntityClass) {
            s_getAttribute = env->GetMethodID(s_livingEntityClass, "getAttribute", "(Lnet/minecraft/core/Holder;)Lnet/minecraft/world/entity/ai/attributes/AttributeInstance;");
        }

        s_attributeInstanceClass = JvmWrapper::findClass("net/minecraft/world/entity/ai/attributes/AttributeInstance");
        if (s_attributeInstanceClass) {
            s_setBaseValue = env->GetMethodID(s_attributeInstanceClass, "setBaseValue", "(D)V");
        }
        init = true;
    }

    if (!s_attributesClass || !s_livingEntityClass || !s_attributeInstanceClass) return;
    if (!s_entityInteractionRange || !s_blockInteractionRange || !s_getAttribute || !s_setBaseValue) return;

    jobject playerObj = CMinecraft::getPlayer();
    if (!playerObj) return;

    // Set Entity Reach
    jobject entityHolder = env->GetStaticObjectField(s_attributesClass, s_entityInteractionRange);
    if (entityHolder) {
        jobject attrInst = env->CallObjectMethod(playerObj, s_getAttribute, entityHolder);
        if (attrInst) {
            env->CallVoidMethod(attrInst, s_setBaseValue, entityReach);
            env->DeleteLocalRef(attrInst);
        }
        env->DeleteLocalRef(entityHolder);
        JvmWrapper::checkException();
    }

    // Set Block Reach
    jobject blockHolder = env->GetStaticObjectField(s_attributesClass, s_blockInteractionRange);
    if (blockHolder) {
        jobject attrInst = env->CallObjectMethod(playerObj, s_getAttribute, blockHolder);
        if (attrInst) {
            env->CallVoidMethod(attrInst, s_setBaseValue, blockReach);
            env->DeleteLocalRef(attrInst);
        }
        env->DeleteLocalRef(blockHolder);
        JvmWrapper::checkException();
    }
}
