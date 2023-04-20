#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/h_box_container.hpp>

#include "gs_boxcontainer.h"
#include "guiscript.h"

using namespace godot;

auto GSBoxContainer::is_horizontal() -> bool {
	return m_is_horizontal;
}

auto GSBoxContainer::initialize(Control *parent, const GSArguments &arguments) -> void {
	GSContainer::initialize(parent, arguments);

	m_is_horizontal = arguments.is_horizontal;

	if (!m_container) {
		if (arguments.is_horizontal) {
			m_container = memnew(HBoxContainer);
			m_container->set_h_size_flags(BoxContainer::SIZE_FILL);
			m_container->set_v_size_flags(BoxContainer::SIZE_EXPAND_FILL);
		} else {
			m_container = memnew(VBoxContainer);
			m_container->set_h_size_flags(BoxContainer::SIZE_EXPAND_FILL);
			m_container->set_v_size_flags(BoxContainer::SIZE_FILL);
		}
		m_parent->add_child(m_container);
	}
}

auto GSBoxContainer::get_control() -> Control * {
	return m_container;
}

GSBoxContainer::GSBoxContainer() {
}

GSBoxContainer::~GSBoxContainer() {
	m_container->queue_free();
}
