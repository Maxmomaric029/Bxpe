#include "pch.h"
#include "modules/combat/aimassist.h"
#include "sdk/minecraft.h"
#include "sdk/entity.h"
#include "sdk/world.h"
#include <cmath>
#include <chrono>
#include <random>

AimAssist::AimAssist() : Module("Aim Assist", 0) {
    m_boolSettings["aim_assist"]   = true;
    m_boolSettings["prediction"]   = true;
    m_boolSettings["gcd_fix"]      = true;
    
    m_floatSettings["range"]       = 4.5f;
    m_floatSettings["fov"]         = 60.0f;
    m_floatSettings["smoothness"]  = 3.5f; // Higher = slower/more legit
}

float AimAssist::wrapAngleTo180(float angle) {
    angle = std::fmod(angle, 360.0f);
    if (angle >= 180.0f) angle -= 360.0f;
    if (angle < -180.0f) angle += 360.0f;
    return angle;
}

void AimAssist::onUpdate(JNIEnv* env) {
    if (!m_enabled) return;

    jobject mcObj = CMinecraft::getInstance();
    if (!mcObj) return;

    jobject playerObj = CMinecraft::getPlayer();
    if (!playerObj) {
        env->DeleteLocalRef(mcObj);
        return;
    }

    CEntity player(playerObj);
    
    // Solo actuar si el jugador está atacando (LMB) para máxima discreción
    if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
        env->DeleteLocalRef(playerObj);
        env->DeleteLocalRef(mcObj);
        return;
    }

    jobject worldObj = CMinecraft::getWorld();
    if (!worldObj) {
        env->DeleteLocalRef(playerObj);
        env->DeleteLocalRef(mcObj);
        return;
    }

    std::vector<CEntity> entities = CWorld::getAllEntities(worldObj);
    CEntity* bestTarget = nullptr;
    float bestFov = m_floatSettings["fov"];

    CEntity::Vec3 pPos = player.getEyePos();
    float pYaw = player.getYaw();
    float pPitch = player.getPitch();

    for (auto& entity : entities) {
        if (entity.getId() == player.getId() || !entity.isAlive() || !entity.isLiving()) continue;

        CEntity::Vec3 tPos = entity.getEyePos();
        
        // Predicción Meteor-Style
        if (m_boolSettings["prediction"]) {
            double vx = (entity.getX() - entity.getPrevX());
            double vy = (entity.getY() - entity.getPrevY());
            double vz = (entity.getZ() - entity.getPrevZ());
            tPos.x += vx * 2.5; // Factor de predicción ajustable
            tPos.y += vy * 2.5;
            tPos.z += vz * 2.5;
        }

        double dx = tPos.x - pPos.x;
        double dy = tPos.y - pPos.y;
        double dz = tPos.z - pPos.z;
        double dist = std::sqrt(dx*dx + dy*dy + dz*dz);

        if (dist > m_floatSettings["range"]) continue;

        float yawToTarget = (float)(std::atan2(dz, dx) * 180.0 / 3.1415926535) - 90.0f;
        float pitchToTarget = (float)-(std::atan2(dy, std::sqrt(dx*dx + dz*dz)) * 180.0 / 3.1415926535);

        float yawDiff = std::abs(wrapAngleTo180(yawToTarget - pYaw));
        if (yawDiff < bestFov) {
            bestFov = yawDiff;
            bestTarget = &entity;
        }
    }

    if (bestTarget) {
        CEntity::Vec3 tPos = bestTarget->getEyePos();
        if (m_boolSettings["prediction"]) {
            tPos.x += (bestTarget->getX() - bestTarget->getPrevX()) * 2.5;
            tPos.y += (bestTarget->getY() - bestTarget->getPrevY()) * 2.5;
            tPos.z += (bestTarget->getZ() - bestTarget->getPrevZ()) * 2.5;
        }

        double dx = tPos.x - pPos.x;
        double dy = tPos.y - pPos.y;
        double dz = tPos.z - pPos.z;

        float targetYaw = (float)(std::atan2(dz, dx) * 180.0 / 3.1415926535) - 90.0f;
        float targetPitch = (float)-(std::atan2(dy, std::sqrt(dx*dx + dz*dz)) * 180.0 / 3.1415926535);

        float yawDiff = wrapAngleTo180(targetYaw - pYaw);
        float pitchDiff = targetPitch - pPitch;

        // Suavizado exponencial (Meteor Style)
        float smooth = m_floatSettings["smoothness"] * 10.0f;
        float nextYaw = pYaw + (yawDiff / smooth);
        float nextPitch = pPitch + (pitchDiff / smooth);

        // GCD Fix (Indetectabilidad de ratón)
        if (m_boolSettings["gcd_fix"]) {
            float sensitivity = 0.5f; // TODO: Leer de mc.options.sensitivity
            float f = sensitivity * 0.6f + 0.2f;
            float gcd = f * f * f * 1.2f; // Simplificado
            nextYaw = std::round(nextYaw / gcd) * gcd;
            nextPitch = std::round(nextPitch / gcd) * gcd;
        }

        player.setYaw(nextYaw);
        player.setPitch(nextPitch);
    }

    env->DeleteLocalRef(worldObj);
    env->DeleteLocalRef(playerObj);
    env->DeleteLocalRef(mcObj);
}
