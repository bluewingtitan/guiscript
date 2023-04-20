#include <godot_cpp/classes/button.hpp>

#include "guiscript.h"
#include "gs_button.h"

using namespace godot;

auto GSButton::_on_pressed() -> void {
	m_was_pressed = true;
}

auto GSButton::_bind_methods() -> void {
	ClassDB::bind_method(D_METHOD("on_pressed"), &GSButton::_on_pressed);
}

auto GSButton::was_pressed() const -> bool {
	return m_was_pressed;
}

auto GSButton::reset_was_pressed() -> void {
	m_was_pressed = false;
}

auto GSButton::is_opened_container() -> bool {
	return false;
}

auto GSButton::get_control() -> Control * {
	return m_button;
}

void GSButton::initialize(Control *parent, const GSArguments &arguments) {
	GSElement::initialize(parent, arguments);

	if (!m_button) {
		m_button = memnew(Button);
		m_button->set_text(arguments.text);
		m_button->connect("pressed", godot::Callable(this, "on_pressed"));
		m_parent->add_child(m_button);
	} else {
		m_button->set_text(arguments.text);
	}
}

auto GSButton::update(const GSArguments &arguments, Ref<GSElement> &out_element) -> bool {
	out_element = Ref<GSElement>(this);
	if (arguments.type != GDElementType::Button) {
		return true;
	}

	m_button->set_text(arguments.text);

	// simple text update is considered a soft change, not a hard change
	return false;
}

GSButton::GSButton() {
}

GSButton::~GSButton() {
	m_button->queue_free();
}
