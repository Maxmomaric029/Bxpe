#include "pch.h"
#include "modules/render/esp.h"
#include "sdk/minecraft.h"
#include "sdk/entity.h"
#include "sdk/world.h"
#include "render/esp_renderer.h"

ESP::ESP() : Module("ESP", 0) {
    m_boolSettings["boxes"]    = true;
    m_boolSettings["corners"]  = true;
    m_boolSettings["names"]    = true;
    m_boolSettings["health"]   = true;
    m_floatSettings["range"]   = 128.0f;
}

void ESP::onRender(ImDrawList* drawList) {
    if (!m_enabled) return;

    jobject mcObj = CMinecraft::getInstance();
    if (!mcObj) return;

    jobject worldObj = CMinecraft::getWorld();
    if (!worldObj) {
        JvmWrapper::getEnv()->DeleteLocalRef(mcObj);
        return;
    }

    jobject playerObj = CMinecraft::getPlayer();
    if (!playerObj) {
        JvmWrapper::getEnv()->DeleteLocalRef(worldObj);
        JvmWrapper::getEnv()->DeleteLocalRef(mcObj);
        return;
    }

    CEntity player(playerObj);
    std::vector<CEntity> entities = CWorld::getAllEntities(worldObj);

    for (auto& entity : entities) {
        if (entity.getId() == player.getId() || !entity.isAlive() || !entity.isLiving()) continue;

        CEntity::AABB box = entity.getBoundingBox();
        
        // Convertir AABB 3D a Rect 2D en pantalla
        ImVec4 rect;
        if (!EspRenderer::getScreenRect(box, rect)) continue;

        float x = rect.x;
        float y = rect.y;
        float w = rect.z - rect.x;
        float h = rect.w - rect.y;

        // Dibujar Box
        if (m_boolSettings["boxes"]) {
            ImU32 color = IM_COL32(255, 255, 255, 180);
            if (m_boolSettings["corners"]) {
                EspRenderer::drawCornerBox(drawList, x, y, w, h, 2.0f, color);
            } else {
                drawList->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color);
            }
        }

        // Dibujar Vida
        if (m_boolSettings["health"]) {
            float health = entity.getHealth();
            float maxHealth = entity.getMaxHealth();
            float healthPercentage = health / maxHealth;
            ImU32 healthColor = EspRenderer::getHealthColor(healthPercentage);
            
            float barHeight = h * healthPercentage;
            drawList->AddRectFilled(ImVec2(x - 5, y), ImVec2(x - 2, y + h), IM_COL32(0, 0, 0, 150));
            drawList->AddRectFilled(ImVec2(x - 5, y + (h - barHeight)), ImVec2(x - 2, y + h), healthColor);
        }

        // Dibujar Nombre
        if (m_boolSettings["names"]) {
            std::string name = entity.getName();
            ImVec2 textSize = ImGui::CalcTextSize(name.c_str());
            drawList->AddText(ImVec2(x + (w / 2) - (textSize.x / 2), y - textSize.y - 2), IM_COL32(255, 255, 255, 255), name.c_str());
        }
    }

    JNIEnv* env = JvmWrapper::getEnv();
    env->DeleteLocalRef(playerObj);
    env->DeleteLocalRef(worldObj);
    env->DeleteLocalRef(mcObj);
}
