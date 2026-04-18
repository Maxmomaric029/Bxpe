#include "pch.h"
#include "ESP.h"
#include "client/event/events/RenderOverlayEvent.h"
#include "render_jni/esp_renderer.h"
#include "sdk/minecraft.h"
#include "sdk/world.h"
#include "client/Latite.h"

ESP::ESP() : Module("ESP", "Extra Sensory Perception", Category::ILLEGAL) {
    addSetting("Draw Boxes", &draw_boxes);
    addSetting("Draw Names", &draw_names);
    addSetting("Draw Health", &draw_health);
    addSetting("Draw Distance", &draw_distance);
    addSetting("Draw Animals", &draw_animals);
    addSetting("Max Distance", &max_distance);
    
    listen<RenderOverlayEvent>(&ESP::onRender);
}

void ESP::onRender(Event& ev) {
    if (!isEnabled()) return;
    if (ev.getHash() != RenderOverlayEvent::hash) return;

    JNIEnv* env = JvmWrapper::getEnv();
    if (!env) return;

    jobject mcObj = CMinecraft::getInstance();
    if (!mcObj) return;

    CMinecraft mc;
    CMinecraft::CameraData cam = mc.getCameraData();
    if (!cam.valid) {
        env->DeleteLocalRef(mcObj);
        return;
    }

    EspRenderer::updateCamera(cam.x, cam.y, cam.z, cam.yaw, cam.pitch, cam.screenW, cam.screenH);
    EspRenderer::setFOV(cam.fov);
    EspRenderer::setMatrices(cam.hasMatrices, cam.viewMatrix, cam.projMatrix);

    bool bBoxes = std::get<BoolValue>(draw_boxes);
    bool bNames = std::get<BoolValue>(draw_names);
    bool bHealth = std::get<BoolValue>(draw_health);
    bool bDistance = std::get<BoolValue>(draw_distance);
    bool bDrawAnimals = std::get<BoolValue>(draw_animals);
    float fMaxDist = std::get<FloatValue>(max_distance);

    D2DUtil draw;
    draw.ctx = static_cast<RenderOverlayEvent&>(ev).getDeviceContext();

    CWorld world(mc.getWorld());
    if (world.isValid()) {
        std::vector<CEntity> entities = world.getEntities();
        
        EspRenderer::EspColors colors = {
            d2d::Color(0.55f, 0.39f, 1.0f, 0.8f),
            d2d::Color(0, 0, 0, 0),
            d2d::Color(1.0f, 1.0f, 1.0f, 1.0f)
        };

        for (auto& entity : entities) {
            if (entity.getId() == CLocalPlayer(mc.getPlayer()).getId()) continue;
            
            bool isPlayer = entity.isPlayer();
            if (!isPlayer && !bDrawAnimals) continue;

            double dist = std::sqrt(std::pow(entity.getX() - cam.x, 2) + 
                                   std::pow(entity.getY() - cam.y, 2) + 
                                   std::pow(entity.getZ() - cam.z, 2));

            if (dist > fMaxDist) continue;

            EspRenderer::drawEntity(&draw, entity, bBoxes, bNames, bHealth, bDistance, colors);
        }
    }

    env->DeleteLocalRef(mcObj);
}
