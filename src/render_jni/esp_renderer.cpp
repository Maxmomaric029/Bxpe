#include "pch.h"
#include "render_jni/esp_renderer.h"
#include "sdk/minecraft.h"
#include <cmath>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void EspRenderer::updateCamera(double camX, double camY, double camZ,
                                float yaw, float pitch,
                                int screenW, int screenH) {
    s_camX = camX;
    s_camY = camY;
    s_camZ = camZ;
    s_yaw  = yaw;
    s_pitch = pitch;
    s_screenW = screenW;
    s_screenH = screenH;
}

void EspRenderer::setMatrices(bool hasMatrices, const float* view, const float* proj) {
    s_hasMatrices = hasMatrices;
    if (hasMatrices) {
        for (int i = 0; i < 16; i++) {
            s_viewMatrix[i] = view[i];
            s_projMatrix[i] = proj[i];
        }
    }
}

bool EspRenderer::worldToScreen(double x, double y, double z, Vec2& out) {
    double dx = x - s_camX;
    double dy = y - s_camY;
    double dz = z - s_camZ;

    if (s_hasMatrices) {
        double clipX = dx * s_viewMatrix[0] + dy * s_viewMatrix[4] + dz * s_viewMatrix[8]  + 1.0 * s_viewMatrix[12];
        double clipY = dx * s_viewMatrix[1] + dy * s_viewMatrix[5] + dz * s_viewMatrix[9]  + 1.0 * s_viewMatrix[13];
        double clipZ = dx * s_viewMatrix[2] + dy * s_viewMatrix[6] + dz * s_viewMatrix[10] + 1.0 * s_viewMatrix[14];
        double clipW = dx * s_viewMatrix[3] + dy * s_viewMatrix[7] + dz * s_viewMatrix[11] + 1.0 * s_viewMatrix[15];

        if (clipW < 0.1f) return false;

        double ndcX = clipX * s_projMatrix[0] + clipY * s_projMatrix[4] + clipZ * s_projMatrix[8]  + clipW * s_projMatrix[12];
        double ndcY = clipX * s_projMatrix[1] + clipY * s_projMatrix[5] + clipZ * s_projMatrix[9]  + clipW * s_projMatrix[13];
        double ndcW = clipX * s_projMatrix[3] + clipY * s_projMatrix[7] + clipZ * s_projMatrix[11] + clipW * s_projMatrix[15];

        ndcX /= ndcW;
        ndcY /= ndcW;

        out.x = (float)((ndcX * 0.5 + 0.5) * s_screenW);
        out.y = (float)((1.0 - (ndcY * 0.5 + 0.5)) * s_screenH);
        return true;
    }

    double yawRad   = s_yaw   * (M_PI / 180.0);
    double pitchRad = s_pitch * (M_PI / 180.0);

    double cosYaw   = cos(yawRad);
    double sinYaw   = sin(yawRad);
    double cosPitch = cos(pitchRad);
    double sinPitch = sin(pitchRad);

    double viewX = -(dx * cosYaw + dz * sinYaw);
    double viewY = dy;
    double viewZ = -dx * sinYaw + dz * cosYaw;

    double finalX = viewX;
    double finalY = viewY * cosPitch + viewZ * sinPitch;
    double finalZ = -viewY * sinPitch + viewZ * cosPitch;

    if (finalZ <= 0.05) return false;

    double fovRad = s_fov * (M_PI / 180.0);
    double halfTanFov = tan(fovRad / 2.0);
    double aspect = (double)s_screenW / (double)s_screenH;
    double ndcX =  (finalX / (finalZ * halfTanFov * aspect));
    double ndcY = -(finalY / (finalZ * halfTanFov));

    out.x = (float)((ndcX * 0.5 + 0.5) * s_screenW);
    out.y = (float)((ndcY * 0.5 + 0.5) * s_screenH);

    return true;
}

void EspRenderer::drawEntity(DrawUtil* draw, const CEntity& entity, bool drawBox, bool drawName, bool drawHealth, bool drawDistance, const EspColors& colors) {
    if (!entity.isValid()) return;

    double ex = entity.getX();
    double ey = entity.getY();
    double ez = entity.getZ();

    auto bbox = entity.getBoundingBox();

    Vec2 corners[8];
    bool visible[8];
    double pts[8][3] = {
        {bbox.minX, bbox.minY, bbox.minZ},
        {bbox.maxX, bbox.minY, bbox.minZ},
        {bbox.minX, bbox.maxY, bbox.minZ},
        {bbox.maxX, bbox.maxY, bbox.minZ},
        {bbox.minX, bbox.minY, bbox.maxZ},
        {bbox.maxX, bbox.minY, bbox.maxZ},
        {bbox.minX, bbox.maxY, bbox.maxZ},
        {bbox.maxX, bbox.maxY, bbox.maxZ},
    };

    bool anyVisible = false;
    for (int i = 0; i < 8; i++) {
        visible[i] = worldToScreen(pts[i][0], pts[i][1], pts[i][2], corners[i]);
        if (visible[i]) anyVisible = true;
    }

    if (!anyVisible) return;

    float minSX = 99999.f, minSY = 99999.f;
    float maxSX = -99999.f, maxSY = -99999.f;
    for (int i = 0; i < 8; i++) {
        if (!visible[i]) continue;
        minSX = std::min(minSX, corners[i].x);
        minSY = std::min(minSY, corners[i].y);
        maxSX = std::max(maxSX, corners[i].x);
        maxSY = std::max(maxSY, corners[i].y);
    }

    if (drawBox) {
        draw->drawRectangle({minSX - 1, minSY - 1, maxSX + 1, maxSY + 1}, d2d::Color(0, 0, 0, 0.5f), 1.0f);
        draw->drawRectangle({minSX, minSY, maxSX, maxSY}, colors.boxVisible, 1.5f);
    }

    if (drawName) {
        std::string name = entity.getName();
        if (name.empty()) name = "Player";
        std::wstring wname(name.begin(), name.end());
        Vec2 textSize = draw->getTextSize(wname, Renderer::FontSelection::PrimaryRegular, 15.0f);
        float textX = (minSX + maxSX) / 2.0f - textSize.x / 2.0f;
        float textY = minSY - textSize.y - 4.0f;

        draw->fillRectangle({textX - 2, textY - 1, textX + textSize.x + 2, textY + textSize.y + 1}, d2d::Color(0, 0, 0, 0.6f));
        draw->drawText({textX, textY, textX + textSize.x, textY + textSize.y}, wname, colors.text, Renderer::FontSelection::PrimaryRegular, 15.0f);
    }

    if (drawDistance) {
        double dx = ex - s_camX;
        double dy = ey - s_camY;
        double dz = ez - s_camZ;
        double dist = std::sqrt(dx*dx + dy*dy + dz*dz);
        
        wchar_t distStr[32];
        swprintf(distStr, 32, L"[%.1fm]", (float)dist);
        
        Vec2 textSize = draw->getTextSize(distStr, Renderer::FontSelection::PrimaryRegular, 12.0f);
        float textX = (minSX + maxSX) / 2.0f - textSize.x / 2.0f;
        float textY = maxSY + 2.0f;

        draw->fillRectangle({textX - 2, textY - 1, textX + textSize.x + 2, textY + textSize.y + 1}, d2d::Color(0, 0, 0, 0.6f));
        draw->drawText({textX, textY, textX + textSize.x, textY + textSize.y}, distStr, colors.text, Renderer::FontSelection::PrimaryRegular, 12.0f);
    }

    if (drawHealth) {
        float health = entity.getHealth();
        float maxHP  = entity.getMaxHealth();
        if (maxHP > 0.0f) {
            float ratio = std::max(0.0f, std::min(1.0f, health / maxHP));
            float barWidth = 3.0f;
            float barX = maxSX + 3.0f;
            float barHeight = maxSY - minSY;

            draw->fillRectangle({barX, minSY, barX + barWidth, maxSY}, d2d::Color(0, 0, 0, 0.6f));
            d2d::Color healthCol = (ratio > 0.5f) ? d2d::Color(0, 1, 0) : d2d::Color(1, 0, 0);
            draw->fillRectangle({barX, minSY + barHeight * (1.0f - ratio), barX + barWidth, maxSY}, healthCol);
        }
    }
}
