#pragma once
#include "pch.h"
#include "sdk/entity.h"
#include "util/DrawContext.h"

class EspRenderer {
public:
    static void updateCamera(double camX, double camY, double camZ,
                             float yaw, float pitch,
                             int screenW, int screenH);

    static void setFOV(float fov) { s_fov = fov; }
    static void setMatrices(bool hasMatrices, const float* view, const float* proj);

    static bool worldToScreen(double x, double y, double z, Vec2& out);

    struct EspColors {
        d2d::Color boxVisible;
        d2d::Color boxHidden;
        d2d::Color text;
    };
    static void drawEntity(DrawUtil* draw, const CEntity& entity, bool drawBox, bool drawName, bool drawHealth, bool drawDistance, const EspColors& colors);

private:
    static inline double s_camX = 0, s_camY = 0, s_camZ = 0;
    static inline float  s_yaw  = 0, s_pitch = 0;
    static inline int    s_screenW = 1920, s_screenH = 1080;
    static inline float  s_fov  = 70.0f;
    static inline bool   s_hasMatrices = false;
    static inline float  s_viewMatrix[16] = {0};
    static inline float  s_projMatrix[16] = {0};
};
