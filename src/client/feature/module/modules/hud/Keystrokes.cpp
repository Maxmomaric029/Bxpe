#include "pch.h"
#include "Keystrokes.h"
#include "sdk/minecraft.h"
#include "sdk/options.h"
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

void Keystrokes::render(DrawUtil& ct, bool isDefault, bool inEditor) {
    if (!this->isActive() || !this->isEnabled()) return;

    auto opt = CMinecraft::getOptions();
    if (!opt.isValid()) return;

    bool w = opt.getKeyForward().isPressed();
    bool s = opt.getKeyBack().isPressed();
    bool a = opt.getKeyLeft().isPressed();
    bool d = opt.getKeyRight().isPressed();
    bool space = opt.getKeyJump().isPressed();
    bool shift = opt.getKeySneak().isPressed();

    // Rendering logic (simplified for now, using ct)
    float x = rect.left;
    float y = rect.top;
    float size = 20.f;
    float padding = 2.f;

    auto drawKey = [&](bool pressed, std::wstring const& label, float kx, float ky) {
        d2d::Color col = pressed ? d2d::Color(1.f, 1.f, 1.f, 0.5f) : d2d::Color(0.f, 0.f, 0.f, 0.3f);
        ct.fillRoundedRectangle({ kx, ky, kx + size, ky + size }, col, 2.f);
        ct.drawText({ kx, ky, kx + size, ky + size }, label, { 1.f, 1.f, 1.f, 1.f }, Renderer::FontSelection::PrimaryRegular, 12.f, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    };

    drawKey(w, L"W", x + size + padding, y);
    drawKey(a, L"A", x, y + size + padding);
    drawKey(s, L"S", x + size + padding, y + size + padding);
    drawKey(d, L"D", x + (size + padding) * 2, y + size + padding);

    this->rect.right = x + (size + padding) * 3;
    this->rect.bottom = y + (size + padding) * 2;
}

void Keystrokes::onRenderLayer(Event& evG) {
}

Keystrokes::Keystroke::Keystroke(std::string const& inputMapping, GetInputFunc getInput) : Stroke(getInput)
	, mapping(inputMapping) {
}

void Keystrokes::Keystroke::updateKeyName() {
	vKey = Latite::getKeyboard().getMappedKey(mapping);
	keyName = util::StrToWStr(util::KeyToString(vKey));
}
