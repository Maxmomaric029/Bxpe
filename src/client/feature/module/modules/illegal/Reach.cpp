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

void Reach::setReach(JNIEnv* env, double entityReach, double blockReach) {
    // Original logic from Project B
    // ... (This involves attribute modification via JNI)
}
