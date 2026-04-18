#pragma once
namespace SDK {
	class VisualTree {
		[[maybe_unused]] char pad[8];
	public:
		class UIControl* rootControl;
	};
}