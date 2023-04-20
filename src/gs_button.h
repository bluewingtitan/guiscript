#pragma once
#include "gs_element.h"

namespace godot{
    class Button;
}

using namespace godot;

class GSButton: public GSElement{
	GDCLASS(GSButton, GSElement)

private:
	bool m_was_pressed {false};
	Button* m_button {nullptr};

	auto _on_pressed() -> void;

protected:
	static auto _bind_methods() -> void;

public:

	auto was_pressed() const -> bool;
	auto reset_was_pressed() -> void;

	auto is_opened_container() -> bool override;
	auto get_control() -> Control * override;

	auto initialize(Control* parent, const GSArguments& arguments) -> void override;
	auto update(const GSArguments& arguments, Ref<GSElement>& out_element) -> bool override;

	GSButton();
	virtual ~GSButton() override;


};

