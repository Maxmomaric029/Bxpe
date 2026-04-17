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

    // Minecraft
    inline const char* MC_getInstance      = "getInstance";
    inline const char* MC_getInstance_Sig  = "()Lnet/minecraft/client/Minecraft;";
    inline const char* MC_player           = "player";
    inline const char* MC_player_Sig       = "Lnet/minecraft/client/player/LocalPlayer;";
    inline const char* MC_level            = "level";
    inline const char* MC_level_Sig         = "Lnet/minecraft/client/multiplayer/ClientLevel;";

    // Level/World
    inline const char* Level_players       = "players"; // Field
    inline const char* Level_players_Sig   = "Ljava/util/List;";
    
    // List
    inline const char* List_size           = "size";
    inline const char* List_size_Sig       = "()I";
    inline const char* List_get            = "get";
    inline const char* List_get_Sig        = "(I)Ljava/lang/Object;";

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
    inline const char* Entity_getYaw_Sig   = "()F";
    inline const char* Entity_getXRot       = "getXRot";
    inline const char* Entity_getPitch_Sig = "()F";
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
