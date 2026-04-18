#pragma once

namespace Mappings {
    // --- Minecraft (MinecraftClient) ---
    inline const char* Minecraft_Class = "net/minecraft/class_310"; 
    inline const char* MC_getInstance = "method_1551";
    inline const char* MC_getInstance_Sig = "()Lnet/minecraft/class_310;";
    inline const char* MC_player = "field_1724";
    inline const char* MC_player_Sig = "Lnet/minecraft/class_746;";
    inline const char* MC_level = "field_1687";
    inline const char* MC_level_Sig = "Lnet/minecraft/class_638;";
    inline const char* MC_gameRenderer = "field_1773";
    inline const char* MC_gameRenderer_Sig = "Lnet/minecraft/class_757;";
    inline const char* MC_options = "field_1690";
    inline const char* MC_options_Sig = "Lnet/minecraft/class_315;";

    // --- Entity ---
    inline const char* Entity_Class = "net/minecraft/class_1297";
    inline const char* Entity_getX = "method_23317";
    inline const char* Entity_getY = "method_23318";
    inline const char* Entity_getZ = "method_23321";
    inline const char* Entity_getBoundingBox = "method_5829";
    inline const char* Entity_getBoundingBox_Sig = "()Lnet/minecraft/class_238;";

    // --- GameRenderer ---
    inline const char* GameRenderer_Class = "net/minecraft/class_757";
    inline const char* GR_getMainCamera = "method_19351";
    inline const char* GR_getMainCamera_Sig = "()Lnet/minecraft/class_4184;";
    inline const char* GR_getProjectionMatrix = "method_56157"; // 1.21.1 basic proj
    inline const char* GR_getProjectionMatrix_Sig = "()Lorg/joml/Matrix4f;";
    inline const char* GR_getFov = "method_3192";
    inline const char* GR_getFov_Sig = "(Lnet/minecraft/class_4184;FZ)F";

    // --- Camera ---
    inline const char* Camera_Class = "net/minecraft/class_4184";
    
    // --- RenderSystem ---
    inline const char* RenderSystem_Class = "com/mojang/blaze3d/systems/RenderSystem";
    inline const char* RS_getProjectionMatrix = "getProjectionMatrix";
    inline const char* RS_getProjectionMatrix_Sig = "()Lorg/joml/Matrix4f;";
    inline const char* RS_getModelViewMatrix = "getModelViewMatrix";
    inline const char* RS_getModelViewMatrix_Sig = "()Lorg/joml/Matrix4f;";

    // --- Matrix4f ---
    inline const char* Matrix4f_Class = "org/joml/Matrix4f";
    inline const char* Matrix4f_m00 = "m00";
    inline const char* Matrix4f_m01 = "m01";
    inline const char* Matrix4f_m02 = "m02";
    inline const char* Matrix4f_m03 = "m03";
    inline const char* Matrix4f_m10 = "m10";
    inline const char* Matrix4f_m11 = "m11";
    inline const char* Matrix4f_m12 = "m12";
    inline const char* Matrix4f_m13 = "m13";
    inline const char* Matrix4f_m20 = "m20";
    inline const char* Matrix4f_m21 = "m21";
    inline const char* Matrix4f_m22 = "m22";
    inline const char* Matrix4f_m23 = "m23";
    inline const char* Matrix4f_m30 = "m30";
    inline const char* Matrix4f_m31 = "m31";
    inline const char* Matrix4f_m32 = "m32";
    inline const char* Matrix4f_m33 = "m33";
}
