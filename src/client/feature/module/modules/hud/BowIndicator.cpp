#include "pch.h"
#include "BowIndicator.h"

BowIndicator::BowIndicator() : TextModule("BowIndicator", LocalizeString::get("client.textmodule.bowIndicator.name"),
                                          LocalizeString::get("client.textmodule.bowIndicator.desc"), HUD, 400.f, 0,
                                          true) {
    addSetting("visual", LocalizeString::get("client.textmodule.bowIndicator.visual.name"),
               LocalizeString::get("client.textmodule.bowIndicator.visual.desc"), this->visual);
    addSetting("fgCol", LocalizeString::get("client.textmodule.bowIndicator.fgCol.name"),
               LocalizeString::get("client.textmodule.bowIndicator.fgCol.desc"), this->indicatorCol2);
    addSetting("bgCol", LocalizeString::get("client.textmodule.bowIndicator.bgCol.name"),
               LocalizeString::get("client.textmodule.bowIndicator.bgCol.desc"), this->indicatorCol);
    addSetting("horizontal", LocalizeString::get("client.textmodule.bowIndicator.horizontal.name"),
               LocalizeString::get("client.textmodule.bowIndicator.horizontal.desc"), this->horizontal,
               "visual"_istrue);
    addSetting("hideWhenCharged", LocalizeString::get("client.textmodule.bowIndicator.hideWhenCharged.name"),
               LocalizeString::get("client.textmodule.bowIndicator.hideWhenCharged.desc"), this->hideWhenCharged,
               "visual"_istrue);

    addSliderSetting("size", LocalizeString::get("client.textmodule.bowIndicator.size.name"),
                     LocalizeString::get("client.textmodule.bowIndicator.size.desc"), indicatorSize, FloatValue(0.f),
                     FloatValue(200.f), FloatValue(2.5f), "visual"_istrue);
    addSliderSetting("width", LocalizeString::get("client.textmodule.bowIndicator.width.name"),
                     LocalizeString::get("client.textmodule.bowIndicator.width.desc"), indicatorWidth, FloatValue(0.f),
                     FloatValue(200.f), FloatValue(2.5f), "visual"_istrue);
    addSliderSetting("rad", LocalizeString::get("client.textmodule.bowIndicator.rad.name"),
                     LocalizeString::get("client.textmodule.bowIndicator.rad.desc"), indicatorRad, FloatValue(0.f),
                     FloatValue(5.f), FloatValue(1.f), "visual"_istrue);
    addSliderSetting("padding", LocalizeString::get("client.textmodule.bowIndicator.padding.name"),
                     LocalizeString::get("client.textmodule.bowIndicator.padding.desc"), padding, FloatValue(0.f),
                     FloatValue(20.f), FloatValue(1.f), "visual"_istrue);
}

BowIndicator::~BowIndicator() {
}

void BowIndicator::render([[maybe_unused]] DrawUtil& dc, [[maybe_unused]] bool isDefault, [[maybe_unused]] bool inEditor) {
}

std::wstringstream BowIndicator::text(bool, bool) {
	std::wstringstream wss;
	return wss;
}

std::optional<float> BowIndicator::getBowCharge([[maybe_unused]] SDK::ItemStack* slot) {
	return std::nullopt;
}
