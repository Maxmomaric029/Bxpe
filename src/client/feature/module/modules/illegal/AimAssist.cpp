#include "pch.h"
#include "AimAssist.h"
#include "sdk/minecraft.h"
#include "sdk/world.h"
#include "client/Latite.h"

AimAssist::AimAssist() : Module("AimAssist", "Smoothly aims at players", Category::ILLEGAL) {
    addSetting("Aim Assist", &aim_assist);
    addSetting("Target Range", &target_range);
    addSetting("Aim FOV", &aim_fov);
    addSetting("Aim Speed", &aim_speed);
    
    listen<UpdateEvent>(&AimAssist::onUpdate);
    listen<RenderOverlayEvent>(&AimAssist::onRender);
}

float AimAssist::wrapAngleTo180(float angle) {
    while (angle > 180.0f) angle -= 360.0f;
    while (angle < -180.0f) angle += 360.0f;
    return angle;
}

float AimAssist::getAngleDifference(float a, float b) {
    return wrapAngleTo180(b - a);
}

void AimAssist::onUpdate(Event& ev) {
    if (!isEnabled()) return;
    if (ev.getHash() != UpdateEvent::hash) return;

    JNIEnv* env = JvmWrapper::getEnv();
    if (!env) return;

    jobject mcObj = CMinecraft::getInstance();
    if (!mcObj) return;

    CMinecraft mc;
    CLocalPlayer lp(mc.getPlayer());
    if (!lp.isValid()) {
        env->DeleteLocalRef(mcObj);
        return;
    }

    if (!std::get<BoolValue>(aim_assist)) {
        env->DeleteLocalRef(mcObj);
        return;
    }

    float maxDist = std::get<FloatValue>(target_range);
    float maxFov = std::get<FloatValue>(aim_fov);
    float speed = std::get<FloatValue>(aim_speed);

    CEntity bestTarget;
    float bestFov = maxFov;

    CWorld world(mc.getWorld());
    if (world.isValid()) {
        std::vector<CEntity> entities = world.getEntities();
        for (auto& entity : entities) {
            if (entity.getId() == lp.getId()) continue;
            if (!entity.isPlayer() || !entity.isAlive()) continue;

            double dx = entity.getX() - lp.getX();
            double dy = entity.getY() + 1.6 - (lp.getY() + 1.6);
            double dz = entity.getZ() - lp.getZ();
            double dist = std::sqrt(dx*dx + dy*dy + dz*dz);

            if (dist > maxDist) continue;

            float yaw = (float)(std::atan2(dz, dx) * 180.0 / M_PI) - 90.0f;
            float pitch = (float)(-std::atan2(dy, std::sqrt(dx*dx + dz*dz)) * 180.0 / M_PI);

            float yawDiff = std::abs(getAngleDifference(lp.getYaw(), yaw));
            float pitchDiff = std::abs(getAngleDifference(lp.getPitch(), pitch));
            float fov = std::sqrt(yawDiff*yawDiff + pitchDiff*pitchDiff);

            if (fov < bestFov) {
                bestFov = fov;
                bestTarget = entity;
            }
        }
    }

    if (bestTarget.isValid()) {
        double dx = bestTarget.getX() - lp.getX();
        double dy = bestTarget.getY() + 1.6 - (lp.getY() + 1.6);
        double dz = bestTarget.getZ() - lp.getZ();

        float targetYaw = (float)(std::atan2(dz, dx) * 180.0 / M_PI) - 90.0f;
        float targetPitch = (float)(-std::atan2(dy, std::sqrt(dx*dx + dz*dz)) * 180.0 / M_PI);

        float yawDelta = getAngleDifference(lp.getYaw(), targetYaw);
        float pitchDelta = getAngleDifference(lp.getPitch(), targetPitch);

        lp.setYaw(lp.getYaw() + yawDelta / (10.0f / speed));
        lp.setPitch(lp.getPitch() + pitchDelta / (10.0f / speed));
    }

    env->DeleteLocalRef(mcObj);
}

void AimAssist::onRender(Event& ev) {
    if (!isEnabled()) return;
    if (ev.getHash() != RenderOverlayEvent::hash) return;

    float maxFov = std::get<FloatValue>(aim_fov);
    if (maxFov <= 0) return;

    D2D1_SIZE_F ss = Latite::getRenderer().getScreenSize();
    Vec2 center = { ss.width / 2.0f, ss.height / 2.0f };
    float radius = maxFov * 10.0f; 

    D2DUtil draw;
    draw.ctx = static_cast<RenderOverlayEvent&>(ev).getDeviceContext();
    draw.drawPolygon(center, radius, 36, d2d::Color(1.0f, 1.0f, 1.0f, 0.3f), 1.0f);
}

void AimAssist::onEnable() {}
void AimAssist::onDisable() {}
