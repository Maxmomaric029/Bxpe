#include "pch.h"
#include "Jesus.h"
#include "sdk/minecraft.h"
#include "client/Latite.h"

Jesus::Jesus() : Module("Jesus", "Walk on water", Category::ILLEGAL) {
    listen<UpdateEvent>(&Jesus::onUpdate);
}

void Jesus::onUpdate(Event& ev) {
    if (!isEnabled()) return;
    if (ev.getHash() != UpdateEvent::hash) return;

    JNIEnv* env = JvmWrapper::getEnv();
    if (!env) return;

    CMinecraft mc;
    CLocalPlayer lp(mc.getPlayer());
    if (!lp.isValid()) return;

    if (lp.isInWater()) {
        CEntity::Vec3 vel = lp.getDeltaMovement();
        if (vel.y < 0) {
            lp.setDeltaMovement(vel.x, 0.1, vel.z);
        }
    }
}
