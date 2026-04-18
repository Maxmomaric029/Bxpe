#include "pch.h"
#include "ESP.h"
#include "core/jvm_wrapper.h"
#include "sdk/minecraft.h"
#include "sdk/world.h"
#include "render_jni/esp_renderer.h"

ESP::ESP() : Module("ESP", L"ESP", L"See entities through walls", ILLEGAL) {
    addSetting("draw_boxes", L"Draw Boxes", L"Draw bounding boxes around entities", draw_boxes);
    addSetting("draw_names", L"Draw Names", L"Draw names above entities", draw_names);
    addSetting("draw_health", L"Draw Health", L"Draw health bars", draw_health);
    addSetting("draw_distance", L"Draw Distance", L"Draw distance to entities", draw_distance);
    addSetting("draw_animals", L"Draw Animals", L"Show animals/mobs", draw_animals);
    addSetting("draw_chests", L"Draw Chests", L"Show chests", draw_chests);
    addSetting("chams", L"Chams", L"Make entities glow", chams);
    addSliderSetting("max_distance", L"Max Distance", L"Maximum distance for ESP", max_distance, FloatValue(10.f), FloatValue(1000.f), FloatValue(10.f));

    listen<RenderOverlayEvent>(&ESP::onRender);
}

void ESP::onRender(Event& ev) {
    JNIEnv* env = JvmWrapper::getEnv();
    if (!env) return;

    env->PushLocalFrame(256);

    jobject localPlayer = CMinecraft::getPlayer();
    if (!localPlayer) {
        env->PopLocalFrame(nullptr);
        return;
    }

    auto camData = CMinecraft::getCameraData();
    double camX, camY, camZ;
    float yaw, pitch;
    
    if (camData.valid) {
        camX = camData.x;
        camY = camData.y;
        camZ = camData.z;
        yaw = camData.yaw;
        pitch = camData.pitch;
        EspRenderer::setFOV(camData.fov);
        EspRenderer::setMatrices(camData.hasMatrices, camData.viewMatrix, camData.projMatrix);
    } else {
        CEntity cam(localPlayer);
        camX = cam.getX();
        camY = cam.getY() + 1.62;
        camZ = cam.getZ();
        yaw = cam.getYaw();
        pitch = cam.getPitch();
    }

    // Use hardcoded or dynamic screen size if possible
    // For now, let's assume we can get it from the event or renderer
    int screenW = 1920, screenH = 1080; // Default fallback

    EspRenderer::updateCamera(camX, camY, camZ, yaw, pitch, screenW, screenH);

    jobject worldObj = CMinecraft::getWorld();
    if (!worldObj) {
        env->PopLocalFrame(nullptr);
        return;
    }

    CEntity localEntity(localPlayer);
    int localId = localEntity.getId();
    auto players = CWorld::getAllEntities(worldObj);

    bool bBoxes = std::get<BoolValue>(draw_boxes);
    bool bNames = std::get<BoolValue>(draw_names);
    bool bHealth = std::get<BoolValue>(draw_health);
    bool bDistance = std::get<BoolValue>(draw_distance);
    bool bDrawAnimals = std::get<BoolValue>(draw_animals);
    bool bDrawChests = std::get<BoolValue>(draw_chests);
    bool bChams = std::get<BoolValue>(chams);
    float fMaxDist = std::get<FloatValue>(max_distance);

    for (auto& entity : players) {
        if (entity.getId() == localId) continue;
        if (!entity.isAlive()) continue;

        bool isPlayer = entity.isPlayer();
        bool isLiving = entity.isLiving() && !entity.isArmorStand();

        if (!isPlayer && !bDrawAnimals && isLiving) continue;

        double dx = entity.getX() - camX;
        double dy = entity.getY() - camY;
        double dz = entity.getZ() - camZ;
        double distToEntity = std::sqrt(dx*dx + dy*dy + dz*dz);
        
        if (distToEntity > fMaxDist) continue;

        if (bChams) entity.setGlowingTag(true);
        else if (entity.hasGlowingTag()) entity.setGlowingTag(false);

        EspRenderer::EspColors colors = {
            IM_COL32(140, 100, 255, 200),
            IM_COL32(0, 0, 0, 0),
            IM_COL32(255, 255, 255, 255)
        };

        EspRenderer::drawEntity(entity, bBoxes, bNames, bHealth, bDistance, colors);
    }

    env->PopLocalFrame(nullptr);
}
