#include "pch.h"
#include "ItemCounter.h"


namespace {
	class ItemCount {
	public:
		std::string texture;
		bool isHash = false;
		ValueType& setting;
		int64_t hash = 0;
		std::string inString = "";

		ItemCount(std::string texture, ValueType& setting, bool hashed, int64_t hash = 0, std::string include = "") : texture(texture), isHash(hashed), inString(include), setting(setting), hash(hash) {
		}
	};

	std::vector<ItemCount> counterList;

	int getCountStr(void* inv, std::string incl) {
		return 0;
	}

	int getCountHashed(void* inv, int64_t hash) {
		return 0;
	}
}


ItemCounter::ItemCounter() : HUDModule("ItemCounter", LocalizeString::get("client.hudmodule.itemCounter.name"),
                                       LocalizeString::get("client.hudmodule.itemCounter.desc"), HUD) {
	std::string arrowT = "textures/items/arrow";
	std::string potionT = "textures/items/potion_bottle_splash_heal";
	std::string xpT = "textures/items/experience_bottle";
	std::string totemT = "textures/items/totem";
	std::string crystalT = "textures/items/end_crystal";

	addSetting("alwaysShow", LocalizeString::get("client.hudmodule.itemCounter.alwaysShow.name"), L"", alwaysShow);
	addSetting("potions", LocalizeString::get("client.hudmodule.itemCounter.potions.name"), L"", potions);
	addSetting("arrows", LocalizeString::get("client.hudmodule.itemCounter.arrows.name"), L"", arrow);
	addSetting("crystals", LocalizeString::get("client.hudmodule.itemCounter.crystals.name"), L"", crystals);
	addSetting("totems", LocalizeString::get("client.hudmodule.itemCounter.totems.name"), L"", totems);
	addSetting("bottles", LocalizeString::get("client.hudmodule.itemCounter.xpBottles.name"), L"", xpBottles);

	counterList.emplace_back(potionT, potions, false, 0, "potion");
	counterList.emplace_back(arrowT, arrow, false, 0, "arrow");
	counterList.emplace_back(totemT, totems, false, 0, "totem");
	counterList.emplace_back(xpT, xpBottles, false, 0, "experience_bottle");
	counterList.emplace_back(crystalT, crystals, false, 0, "end_crystal");
}

void ItemCounter::render(DrawUtil& ct, bool isDefault, bool inEditor) {
}
