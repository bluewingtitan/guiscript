#include "gs_element.h"

#include <godot_cpp/classes/control.hpp>

#include "guiscript.h"


GSElement::GSElement() {
}

GSElement::~GSElement() {
}

auto GSElement::_bind_methods() -> void {
}

auto GSElement::on_begin_ui() -> void {
}

auto GSElement::is_opened_container() -> bool{
    return false;
}

auto GSElement::get_control() -> Control*{
    return m_parent;
}

auto GSElement::initialize(Control *parent, const GSArguments &arguments) -> void {
	this->m_parent = parent;
}

auto GSElement::update(const GSArguments& arguments, Ref<GSElement>& out_element) -> bool{
    return false;
}
