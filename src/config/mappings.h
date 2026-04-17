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

    // Minecraft
    inline const char* MC_getInstance      = "getInstance";
    inline const char* MC_getInstance_Sig  = "()Lnet/minecraft/client/Minecraft;";
    inline const char* MC_player           = "player";
    inline const char* MC_player_Sig       = "Lnet/minecraft/client/player/LocalPlayer;";
    inline const char* MC_level            = "level";
    inline const char* MC_level_Sig         = "Lnet/minecraft/client/multiplayer/ClientLevel;";

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
    inline const char* Entity_getYaw       = "getYRot";
    inline const char* Entity_getYaw_Sig   = "()F";
    inline const char* Entity_getPitch     = "getXRot";
    inline const char* Entity_getPitch_Sig = "()F";
    inline const char* Entity_isAlive      = "isAlive";
    inline const char* Entity_isAlive_Sig  = "()Z";
    inline const char* Entity_getId        = "getId";
    inline const char* Entity_getId_Sig    = "()I";
    inline const char* Entity_getEyeHeight = "getEyeHeight";
    inline const char* Entity_getEyeHeight_Sig = "()F";
    
    // LivingEntity
    inline const char* Living_getHealth    = "getHealth";
    inline const char* Living_getHealth_Sig = "()F";
}
