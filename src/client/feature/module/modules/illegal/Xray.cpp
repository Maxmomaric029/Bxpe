#include "pch.h"
#include "Xray.h"
#include "core/jvm_wrapper.h"
#include "sdk/minecraft.h"

Xray::Xray() : Module("Xray", L"Xray", L"See through blocks", ILLEGAL) {
}

void Xray::onEnable() {
    JNIEnv* env = JvmWrapper::getEnv();
    if (!env) return;

    jobject mc = CMinecraft::getInstance();
    if (mc) {
        // Logic to trigger world re-render or change block transparency
        // For now, keeping it consistent with Project B's stub/intent
        env->DeleteLocalRef(mc);
    }
}

void Xray::onDisable() {
}
