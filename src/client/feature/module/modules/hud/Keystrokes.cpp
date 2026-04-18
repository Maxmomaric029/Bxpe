#include "pch.h"
#include "Keystrokes.h"
#include "client/input/Keyboard.h"
#include <array>
#include <client/Latite.h>

Keystrokes::Keystrokes() : HUDModule("Keystrokes", LocalizeString::get("client.hudmodule.keystrokes.name"),
                                     LocalizeString::get("client.hudmodule.keystrokes.desc"), HUD) {
    addSetting("mouseButtons", LocalizeString::get("client.hudmodule.keystrokes.mouseButtons.name"),
               LocalizeString::get("client.hudmodule.keystrokes.mouseButtons.desc"), mouseButtons);
    addSetting("showCps", LocalizeString::get("client.hudmodule.keystrokes.showCps.name"),
               LocalizeString::get("client.hudmodule.keystrokes.showCps.desc"), cps);
    addSetting("spaceBar", LocalizeString::get("client.hudmodule.keystrokes.spaceBar.name"),
               LocalizeString::get("client.hudmodule.keystrokes.spaceBar.desc"), spaceBar);
    addSetting("border", LocalizeString::get("client.hudmodule.keystrokes.border.name"),
               LocalizeString::get("client.hudmodule.keystrokes.border.desc"), border);
    addSetting("showSneak", LocalizeString::get("client.hudmodule.keystrokes.showSneak.name"),
               LocalizeString::get("client.hudmodule.keystrokes.showSneak.desc"), shiftKey);

    addSliderSetting("radius", LocalizeString::get("client.hudmodule.keystrokes.radius.name"),
                     LocalizeString::get("client.hudmodule.keystrokes.radius.desc"), radius, FloatValue(0.f),
                     FloatValue(10.f), FloatValue(1.f));
    addSliderSetting("textSize", LocalizeString::get("client.hudmodule.keystrokes.textSize.name"),
                     LocalizeString::get("client.hudmodule.keystrokes.textSize.desc"), textSize, FloatValue(2.f),
                     FloatValue(40.f), FloatValue(0.2f));
    addSliderSetting("keySize", LocalizeString::get("client.hudmodule.keystrokes.keySize.name"),
                     LocalizeString::get("client.hudmodule.keystrokes.keySize.desc"), keystrokeSize, FloatValue(15.f),
                     FloatValue(90.f), FloatValue(2.f));
    addSliderSetting("spaceSize", LocalizeString::get("client.hudmodule.keystrokes.spaceSize.name"),
                     LocalizeString::get("client.hudmodule.keystrokes.spaceSize.desc"), spaceSize, FloatValue(0.f),
                     FloatValue(90.f), FloatValue(2.f));
    addSliderSetting("mouseButtonHeight", LocalizeString::get("client.hudmodule.keystrokes.mouseButtonHeight.name"),
                     LocalizeString::get("client.hudmodule.keystrokes.mouseButtonHeight.desc"), mouseButtonHeight,
                     FloatValue(15.f), FloatValue(90.f), FloatValue(2.f), "mouseButtons"_istrue);
    addSliderSetting("padding", LocalizeString::get("client.hudmodule.keystrokes.padding.name"),
                     LocalizeString::get("client.hudmodule.keystrokes.padding.desc"), padding, FloatValue(0.f),
                     FloatValue(6.f), FloatValue(0.25f));
    addSliderSetting("borderLength", LocalizeString::get("client.hudmodule.keystrokes.borderLength.name"),
                     LocalizeString::get("client.hudmodule.keystrokes.borderLength.desc"), borderLength, FloatValue(0.f),
                     FloatValue(6.f), FloatValue(0.25f), "border"_istrue);
    addSliderSetting("transition", LocalizeString::get("client.hudmodule.keystrokes.transition.name"),
                     LocalizeString::get("client.hudmodule.keystrokes.transition.desc"), lerpSpeed, FloatValue(0.f),
                     FloatValue(3.f), FloatValue(0.05f));

    addSetting("borderCol", LocalizeString::get("client.hudmodule.keystrokes.borderCol.name"),
               LocalizeString::get("client.hudmodule.keystrokes.borderCol.desc"), borderColor);
    addSetting("pressedCol", LocalizeString::get("client.hudmodule.keystrokes.pressedCol.name"),
               LocalizeString::get("client.hudmodule.keystrokes.pressedCol.desc"), pressedColor);
    addSetting("unpressedCol", LocalizeString::get("client.hudmodule.keystrokes.unpressedCol.name"),
               LocalizeString::get("client.hudmodule.keystrokes.unpressedCol.desc"), unpressedColor);
    addSetting("ptCol", LocalizeString::get("client.hudmodule.keystrokes.ptCol.name"),
               LocalizeString::get("client.hudmodule.keystrokes.ptCol.desc"), pressedTextColor);
    addSetting("uptCol", LocalizeString::get("client.hudmodule.keystrokes.uptCol.name"),
               LocalizeString::get("client.hudmodule.keystrokes.uptCol.desc"), unpressedTextColor);

    listen<ClickEvent>((EventListenerFunc)&Keystrokes::onClick);
}


Vec2 Keystrokes::drawKeystroke(DrawUtil& ctx, Vec2 const& pos, Keystroke& stroke) {
	d2d::Rect front = { pos.x, pos.y, pos.x + std::get<FloatValue>(keystrokeSize), pos.y + std::get<FloatValue>(keystrokeSize) };
	float scale = std::get<FloatValue>(textSize);//ctx.scaleTextInBounds(key, 1 * textSize, (front.right - front.left), 2);
	ctx.fillRoundedRectangle(front, stroke.col, std::min(std::get<FloatValue>(this->radius).value, std::get<FloatValue>(keystrokeSize) / 2.f));
	if (std::get<BoolValue>(border)) ctx.drawRoundedRectangle(front, std::get<ColorValue>(borderColor).getMainColor(), std::get<FloatValue>(this->radius), std::get<FloatValue>(borderLength));
	ctx.drawText(front, stroke.keyName, stroke.textCol, Renderer::FontSelection::SecondaryLight, std::get<FloatValue>(textSize), DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	return { front.right - front.left, front.bottom - front.top };
}

void Keystrokes::onClick(Event& evG) {
	auto& ev = reinterpret_cast<ClickEvent&>(evG);

	if (ev.getMouseButton() == 1) {
		primaryClickState = ev.isDown();
	}
	else if (ev.getMouseButton() == 2) {
		secondaryClickState = ev.isDown();
	}
}

void Keystrokes::render(DrawUtil& dc, bool, bool inEditor) {
};

Keystrokes::Keystroke::Keystroke(std::string const& inputMapping, GetInputFunc getInput) : Stroke(getInput)
	, mapping(inputMapping) {
}

void Keystrokes::Keystroke::updateKeyName() {
	vKey = Latite::getKeyboard().getMappedKey(mapping);
	keyName = util::StrToWStr(util::KeyToString(vKey));
}
