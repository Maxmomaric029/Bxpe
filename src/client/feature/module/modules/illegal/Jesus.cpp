#include "pch.h"
#include "Jesus.h"
#include "core/jvm_wrapper.h"
#include "sdk/minecraft.h"
#include "sdk/entity.h"

Jesus::Jesus() : Module("Jesus", L"Jesus", L"Walk on water", ILLEGAL) {
    listen<UpdateEvent>(&Jesus::onUpdate);
}

void Jesus::onUpdate(Event& ev) {
    JNIEnv* env = JvmWrapper::getEnv();
    if (!env) return;

    jobject playerObj = CMinecraft::getPlayer();
    if (!playerObj) return;

    CEntity player(playerObj);
    if (player.isInWater()) {
        player.setMotionY(0.1);
        player.setOnGround(true);
    }

    env->DeleteLocalRef(playerObj);
}
