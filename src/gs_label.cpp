#include <godot_cpp/classes/label.hpp>

#include "gs_label.h"
#include "guiscript.h"

using namespace godot;

auto GSLabel::is_opened_container() -> bool {
	return false;
}

auto GSLabel::get_control() -> Control * {
	return m_label;
}

auto GSLabel::initialize(Control *parent, const GSArguments &arguments) -> void {
	GSElement::initialize(parent, arguments);

	if (!m_label) {
		m_label = memnew(Label);
		m_label->set_text(arguments.text);
		m_parent->add_child(m_label);
	} else {
		m_label->set_text(arguments.text);
	}
}

auto GSLabel::update(const GSArguments &arguments, Ref<GSElement>& out_element) -> bool {
	out_element = Ref<GSElement>(this);
	if (arguments.type != GDElementType::Label) {
		return true;
	}

	m_label->set_text(arguments.text);

	// simple text update is considered a soft change, not a hard change
	return false;
}

GSLabel::GSLabel(): GSElement() {
}

GSLabel::~GSLabel() {
	m_label->queue_free();
}
