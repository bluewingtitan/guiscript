#include <godot_cpp/classes/h_separator.hpp>
#include <godot_cpp/classes/v_separator.hpp>

#include "guiscript.h"
#include "gs_separator.h"

auto GSSeparator::is_opened_container() -> bool {
	return false;
}

auto GSSeparator::get_control() -> Control * {
	return nullptr;
}

void GSSeparator::initialize(Control *parent, const GSArguments &arguments) {
	GSElement::initialize(parent, arguments);

	m_is_horizontal = arguments.is_horizontal;

	if (!m_separator) {
		if (arguments.is_horizontal) {
			m_separator = memnew(HSeparator);
		} else {
			m_separator = memnew(VSeparator);
		}
		m_parent->add_child(m_separator);
	}
}

auto GSSeparator::update(const GSArguments &arguments, Ref<GSElement> &out_element) -> bool {
	return arguments.type != GDElementType::Separator || arguments.is_horizontal != m_is_horizontal;
}

GSSeparator::GSSeparator() {
}

GSSeparator::~GSSeparator() {
	m_separator->queue_free();
}
