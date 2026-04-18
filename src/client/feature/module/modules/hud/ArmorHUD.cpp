#include "pch.h"
#include "ArmorHUD.h"

ArmorHUD::ArmorHUD() : HUDModule("ArmorHUD", LocalizeString::get("client.hudmodule.armorHud.name"),
                                 LocalizeString::get("client.hudmodule.armorHud.desc"), HUD) {
	mode.addEntry(EnumEntry{ mode_vetical, LocalizeString::get("client.hudmodule.armorHud.modeVertical.name") });
	mode.addEntry(EnumEntry{ mode_horizontal, LocalizeString::get("client.hudmodule.armorHud.modeHorizontal.name") });
	addEnumSetting("mode", LocalizeString::get("client.hudmodule.armorHud.mode.name"),
                   LocalizeString::get("client.hudmodule.armorHud.mode.desc"), mode);
	addSetting("durability", LocalizeString::get("client.hudmodule.armorHud.durability.name"),
               LocalizeString::get("client.hudmodule.armorHud.durability.desc"), showDamage);
	addSetting("percent", LocalizeString::get("client.hudmodule.armorHud.percent.name"),
               LocalizeString::get("client.hudmodule.armorHud.percent.desc"), this->percentage, "durability"_istrue);

	std::get<ColorValue>(txtColor).getMainColor() = { 1.f, 1.f, 1.f, 1.f };
	addSetting("textColor", LocalizeString::get("client.hudmodule.armorHud.textColor.name"),
               LocalizeString::get("client.hudmodule.armorHud.textColor.desc"), txtColor);
}

void ArmorHUD::render(DrawUtil& ctxGeneric, bool isDefault, bool inEditor) {
}

d2d::Rect ArmorHUD::drawItem(DrawUtil& dc, Vec2 pos, SDK::ItemStack* stack, float size){
    return d2d::Rect(pos.x, pos.y, pos.x + size, pos.y + size);
}
