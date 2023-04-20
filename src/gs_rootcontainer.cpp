#include <godot_cpp/classes/v_box_container.hpp>

#include "gs_rootcontainer.h"

using namespace godot;

auto GSRootContainer::is_horizontal() -> bool  {
	return false;
}

bool GSRootContainer::is_opened_container() {
	return true;
}

void GSRootContainer::initialize(Control *parent, const GSArguments &arguments) {
	GSContainer::initialize(parent, arguments);

	if (!m_container) {
		m_container = memnew(VBoxContainer);
		m_container->set_h_size_flags(BoxContainer::SIZE_EXPAND_FILL);
		m_container->set_v_size_flags(BoxContainer::SIZE_FILL);
		m_parent->add_child(m_container);
	}

}

auto GSRootContainer::get_control() -> Control * {
	return m_container;
}

bool GSRootContainer::update(const GSArguments &arguments, Ref<GSElement>& out_element) {
	m_current_index += 0;
	return GSContainer::update(arguments, out_element);
}

GSRootContainer::GSRootContainer() {
}

GSRootContainer::~GSRootContainer() {
	m_container->queue_free();
}
