#include "pch.h"
#include "BreakIndicator.h"

BreakIndicator::BreakIndicator() : TextModule("BreakProgress",
                                              LocalizeString::get("client.textmodule.breakIndicator.name"),
                                              LocalizeString::get("client.textmodule.breakIndicator.desc"), HUD, 400.f,
                                              0, true) {
    addSetting("last", LocalizeString::get("client.textmodule.breakIndicator.lastProgress.name"),
               LocalizeString::get("client.textmodule.breakIndicator.lastProgress.desc"), this->last);
    addSetting("visual", LocalizeString::get("client.textmodule.breakIndicator.visual.name"),
               LocalizeString::get("client.textmodule.breakIndicator.visual.desc"), this->visual);
    addSetting("fgCol", LocalizeString::get("client.textmodule.breakIndicator.fgCol.name"),
               LocalizeString::get("client.textmodule.breakIndicator.fgCol.desc"), this->indicatorCol2,
               "visual"_istrue);
    addSetting("bgCol", LocalizeString::get("client.textmodule.breakIndicator.bgCol.name"),
               LocalizeString::get("client.textmodule.breakIndicator.bgCol.desc"), this->indicatorCol, "visual"_istrue);
    addSetting("horizontal", LocalizeString::get("client.textmodule.breakIndicator.horizontal.name"),
               LocalizeString::get("client.textmodule.breakIndicator.horizontal.desc"), this->horizontal,
               "visual"_istrue);

    addSliderSetting("size", LocalizeString::get("client.textmodule.breakIndicator.size.name"),
                     LocalizeString::get("client.textmodule.breakIndicator.size.desc"), indicatorSize, FloatValue(0.f),
                     FloatValue(200.f), FloatValue(2.5f), "visual"_istrue);
    addSliderSetting("width", LocalizeString::get("client.textmodule.breakIndicator.width.name"),
                     LocalizeString::get("client.textmodule.breakIndicator.width.desc"), indicatorWidth,
                     FloatValue(0.f),
                     FloatValue(200.f), FloatValue(2.5f), "visual"_istrue);
    addSliderSetting("rad", LocalizeString::get("client.textmodule.breakIndicator.rad.name"),
                     LocalizeString::get("client.textmodule.breakIndicator.rad.desc"), indicatorRad, FloatValue(0.f),
                     FloatValue(5.f), FloatValue(1.f), "visual"_istrue);
    addSliderSetting("padding", LocalizeString::get("client.textmodule.breakIndicator.padding.name"),
                     LocalizeString::get("client.textmodule.breakIndicator.padding.desc"), padding, FloatValue(0.f),
                     FloatValue(20.f), FloatValue(1.f), "visual"_istrue);
}

BreakIndicator::~BreakIndicator() {
}

void BreakIndicator::render([[maybe_unused]] DrawUtil& dc, [[maybe_unused]] bool isDefault, [[maybe_unused]] bool inEditor) {
}

std::wstringstream BreakIndicator::text([[maybe_unused]] bool isDefault, [[maybe_unused]] bool inEditor) {
    std::wstringstream wss;
    return wss;
}
