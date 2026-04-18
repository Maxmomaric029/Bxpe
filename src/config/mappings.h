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
    inline const char* Entity_getX_Sig = "()D";
    inline const char* Entity_getY = "method_23318";
    inline const char* Entity_getY_Sig = "()D";
    inline const char* Entity_getZ = "method_23321";
    inline const char* Entity_getZ_Sig = "()D";
    inline const char* Entity_prevX = "field_6014";
    inline const char* Entity_prevY = "field_6036";
    inline const char* Entity_prevZ = "field_6004";
    inline const char* Entity_prev_Sig = "D";
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
    // --- Player ---
    inline const char* Player_Class = "net/minecraft/class_1657";
    inline const char* ClientPlayer_Class = "net/minecraft/class_746";
    inline const char* ClientPlayer_networkHandler = "field_3944";
    inline const char* ClientPlayer_networkHandler_Sig = "Lnet/minecraft/class_634;";
    
    // --- LivingEntity ---
    inline const char* LivingEntity_Class = "net/minecraft/class_1309";
    inline const char* LivingEntity_getHealth = "method_6032";
    inline const char* LivingEntity_getHealth_Sig = "()F";
    inline const char* LivingEntity_getMaxHealth = "method_6063";
    inline const char* LivingEntity_getMaxHealth_Sig = "()F";
    inline const char* LivingEntity_jumping = "field_6213";
    inline const char* LivingEntity_jumping_Sig = "Z";
    inline const char* LivingEntity_discardFriction = "field_6233";
    inline const char* LivingEntity_discardFriction_Sig = "Z";

    inline const char* Player_getInventory = "method_31548";
    inline const char* Player_getInventory_Sig = "()Lnet/minecraft/class_1661;";

    // --- PlayerInventory ---
    inline const char* PlayerInventory_Class = "net/minecraft/class_1661";
    inline const char* PlayerInventory_getArmorStack = "method_7372";
    inline const char* PlayerInventory_getArmorStack_Sig = "(I)Lnet/minecraft/class_1799;";

    // --- ItemStack ---
    inline const char* ItemStack_Class = "net/minecraft/class_1799";
    inline const char* ItemStack_isEmpty = "method_7960";
    inline const char* ItemStack_isEmpty_Sig = "()Z";

    // --- Options ---
    inline const char* Options_Class = "net/minecraft/class_315";
    inline const char* Options_keyForward = "field_1894";
    inline const char* Options_keyBack = "field_1881";
    inline const char* Options_keyLeft = "field_1913";
    inline const char* Options_keyRight = "field_1849";
    inline const char* Options_keyJump = "field_1903";
    inline const char* Options_keySneak = "field_1832";
    inline const char* Options_KeySig = "Lnet/minecraft/class_304;";

    // --- KeyBinding ---
    inline const char* KeyBinding_Class = "net/minecraft/class_304";
    inline const char* KB_isPressed = "method_1434";
    inline const char* KB_isPressed_Sig = "()Z";

    // --- NetworkHandler ---
    inline const char* NetworkHandler_Class = "net/minecraft/class_634";
    inline const char* NH_sendChatMessage = "method_44099";
    inline const char* NH_sendChatMessage_Sig = "(Ljava/lang/String;)V";
}
