#pragma once

namespace Mappings {
    // Classes
    inline const char* Minecraft_Class     = "net/minecraft/client/Minecraft";
    inline const char* Entity_Class        = "net/minecraft/world/entity/Entity";
    inline const char* LivingEntity_Class  = "net/minecraft/world/entity/LivingEntity";
    inline const char* Player_Class        = "net/minecraft/client/player/LocalPlayer";
    inline const char* ClientLevel_Class   = "net/minecraft/client/multiplayer/ClientLevel";
    inline const char* Vec3_Class          = "net/minecraft/world/phys/Vec3";
    inline const char* AABB_Class          = "net/minecraft/world/phys/AABB";
    inline const char* List_Class          = "java/util/List";
    inline const char* Component_Class     = "net/minecraft/network/chat/Component";
    inline const char* GameProfile_Class   = "com/mojang/authlib/GameProfile";
    inline const char* ItemEntity_Class    = "net/minecraft/world/entity/item/ItemEntity";
    inline const char* ArmorStand_Class    = "net/minecraft/world/entity/decoration/ArmorStand";
    inline const char* MinecartChest_Class = "net/minecraft/world/entity/vehicle/MinecartChest";
    inline const char* GameRenderer_Class  = "net/minecraft/client/renderer/GameRenderer";
    inline const char* Camera_Class        = "net/minecraft/client/Camera";
    inline const char* Options_Class       = "net/minecraft/client/Options";
    inline const char* RenderSystem_Class  = "com/mojang/blaze3d/systems/RenderSystem";
    inline const char* Matrix4f_Class      = "org/joml/Matrix4f";

    // Minecraft
    inline const char* MC_getInstance      = "getInstance";
    inline const char* MC_getInstance_Sig  = "()Lnet/minecraft/client/Minecraft;";
    inline const char* MC_player           = "player";
    inline const char* MC_player_Sig       = "Lnet/minecraft/client/player/LocalPlayer;";
    inline const char* MC_level            = "level";
    inline const char* MC_level_Sig         = "Lnet/minecraft/client/multiplayer/ClientLevel;";
    inline const char* MC_gameRenderer     = "gameRenderer";
    inline const char* MC_gameRenderer_Sig = "Lnet/minecraft/client/renderer/GameRenderer;";
    inline const char* MC_options          = "options";
    inline const char* MC_options_Sig      = "Lnet/minecraft/client/Options;";

    // GameRenderer
    inline const char* GR_getMainCamera    = "getMainCamera";
    inline const char* GR_getMainCamera_Sig = "()Lnet/minecraft/client/Camera;";
    inline const char* GR_getProjectionMatrix = "getProjectionMatrix";
    inline const char* GR_getProjectionMatrix_Sig = "()Lorg/joml/Matrix4f;";
    inline const char* GR_getFov           = "getFov";
    inline const char* GR_getFov_Sig       = "(DZ)D";

    // RenderSystem
    inline const char* RS_getProjectionMatrix = "getProjectionMatrix";
    inline const char* RS_getProjectionMatrix_Sig = "()Lorg/joml/Matrix4f;";
    inline const char* RS_getModelViewMatrix = "getModelViewMatrix";
    inline const char* RS_getModelViewMatrix_Sig = "()Lorg/joml/Matrix4f;";

    // Level/World
    inline const char* Level_players       = "players";
    inline const char* Level_players_Sig   = "Ljava/util/List;";
    
    // List
    inline const char* List_size           = "size";
    inline const char* List_size_Sig       = "()I";
    inline const char* List_get            = "get";
    inline const char* List_get_Sig        = "(I)Ljava/lang/Object;";

    // Matrix4f
    inline const char* Matrix4f_m00 = "m00"; // En 1.21.1 / JOML suelen ser m00, m01...
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
    inline const char* Matrix4f_Sig = "F";

    // Entity
    inline const char* Entity_getX         = "getX";
    inline const char* Entity_getX_Sig     = "()D";
    inline const char* Entity_getY         = "getY";
    inline const char* Entity_getY_Sig     = "()D";
    inline const char* Entity_getZ         = "getZ";
    inline const char* Entity_getZ_Sig     = "()D";
    inline const char* Entity_prevX        = "xo";
    inline const char* Entity_prevX_Sig    = "D";
    inline const char* Entity_prevY        = "yo";
    inline const char* Entity_prevY_Sig    = "D";
    inline const char* Entity_prevZ        = "zo";
    inline const char* Entity_prevZ_Sig    = "D";
    inline const char* Entity_getYRot       = "getYRot";
    inline const char* Entity_getYRot_Sig   = "()F";
    inline const char* Entity_getXRot       = "getXRot";
    inline const char* Entity_getXRot_Sig   = "()F";
    inline const char* Entity_setYRot       = "setYRot";
    inline const char* Entity_setYRot_Sig   = "(F)V";
    inline const char* Entity_setXRot       = "setXRot";
    inline const char* Entity_setXRot_Sig   = "(F)V";
    inline const char* Entity_isAlive      = "isAlive";
    inline const char* Entity_isAlive_Sig  = "()Z";
    inline const char* Entity_getId        = "getId";
    inline const char* Entity_getId_Sig    = "()I";
    inline const char* Entity_getEyeHeight = "getEyeHeight";
    inline const char* Entity_getEyeHeight_Sig = "()F";
    inline const char* Entity_getBoundingBox = "getBoundingBox";
    inline const char* Entity_getBoundingBox_Sig = "()Lnet/minecraft/world/phys/AABB;";
    inline const char* Entity_getScoreboardName = "getScoreboardName";
    inline const char* Entity_getScoreboardName_Sig = "()Ljava/lang/String;";
    inline const char* Entity_getName      = "getName";
    inline const char* Entity_getName_Sig  = "()Lnet/minecraft/network/chat/Component;";
    inline const char* Entity_getDeltaMovement = "getDeltaMovement";
    inline const char* Entity_getDeltaMovement_Sig = "()Lnet/minecraft/world/phys/Vec3;";
    inline const char* Entity_setDeltaMovement = "setDeltaMovement";
    inline const char* Entity_setDeltaMovement_Sig = "(Lnet/minecraft/world/phys/Vec3;)V";
    inline const char* Entity_onGround     = "onGround";
    inline const char* Entity_onGround_Sig = "Z";
    inline const char* Entity_horizontalCollision = "horizontalCollision";
    inline const char* Entity_horizontalCollision_Sig = "Z";
    inline const char* Entity_isShiftKeyDown = "isShiftKeyDown";
    inline const char* Entity_isShiftKeyDown_Sig = "()Z";
    inline const char* Entity_setSharedFlag = "setSharedFlag";
    inline const char* Entity_setSharedFlag_Sig = "(IZ)V";
    inline const char* Entity_getSharedFlag = "getSharedFlag";
    inline const char* Entity_getSharedFlag_Sig = "(I)Z";
    inline const char* Entity_isInWater    = "isInWater";
    inline const char* Entity_isInWater_Sig = "()Z";

    // LivingEntity
    inline const char* LivingEntity_getHealth = "getHealth";
    inline const char* LivingEntity_getHealth_Sig = "()F";
    inline const char* LivingEntity_getMaxHealth = "getMaxHealth";
    inline const char* LivingEntity_getMaxHealth_Sig = "()F";
    inline const char* LivingEntity_jumping = "jumping";
    inline const char* LivingEntity_jumping_Sig = "Z";
    inline const char* LivingEntity_discardFriction = "discardFriction";
    inline const char* LivingEntity_discardFriction_Sig = "Z";

    // Vec3 fields
    inline const char* Vec3_x              = "x";
    inline const char* Vec3_y              = "y";
    inline const char* Vec3_z              = "z";
    inline const char* Vec3_D_Sig          = "D";

    // AABB fields
    inline const char* AABB_minX           = "minX";
    inline const char* AABB_minY           = "minY";
    inline const char* AABB_minZ           = "minZ";
    inline const char* AABB_maxX           = "maxX";
    inline const char* AABB_maxY           = "maxY";
    inline const char* AABB_maxZ           = "maxZ";
    inline const char* AABB_D_Sig          = "D";
}
