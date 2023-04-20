#include "gs_container.h"
#include "guiscript.h"


using namespace godot;

GSContainer::GSContainer(){

}
GSContainer::~GSContainer(){

}

auto GSContainer::is_horizontal() -> bool{
	return false;
}

void GSContainer::on_begin_ui() {
	// remove un-ticked components

	// m_current_index always is the index of the next to be generated/updated element, making it the actual size of the subset of updated elements last tick
	while (m_elements.size() > m_current_index) {
		m_elements.pop_back();
	}

	// check for invalidly opened nested containers
	if (!m_opened_containers.is_empty()) {
		printf("One or more Boxes weren't properly closed last tick. Make sure to call end_box() for each box you open!");
        

		// force close all opened nested containers.
		force_close();
	}

	// reset the internal index
	m_current_index = 0;

	// relay event to contained elements
	for (int i = 0; i < m_elements.size(); ++i) {
		Ref<GSElement> element = m_elements[i];
		element->on_begin_ui();
	}
}

auto GSContainer::force_close() -> void {
	m_is_opened = false;

	while (!m_opened_containers.is_empty()) {
		Ref<GSContainer> nested_container = m_opened_containers.pop_back();
		nested_container->force_close();
	}
}

auto GSContainer::is_opened_container() -> bool {
	return m_is_opened;
}

void GSContainer::initialize(Control *parent, const GSArguments &arguments) {
	GSElement::initialize(parent, arguments);
}

auto GSContainer::update(const GSArguments& arguments, Ref<GSElement>& out_element) -> bool {
	// if this containers wasn't called open, this has to be an open call, or this container actually is invalid
	if (!is_opened_container()) {
		if (arguments.type != GDElementType::Box_Start) {
			// this should not be a container!
			return true;
		}

		// consider opened now.
		m_is_opened = true;

		// only keep if this is the right container type
		out_element = Ref<GSElement>(this);
		return is_horizontal() != arguments.is_horizontal;
	}


	// pass updates to opened nested containers if there are any
	if (!m_opened_containers.is_empty()) {
		Ref<GSContainer> c = m_opened_containers.pop_back();

		c->update(arguments, out_element);

		if (c->is_opened_container()) {
			m_opened_containers.push_back(c);
		}

		return false;
	}

	// check for close directed towards this box
	if (arguments.type == GDElementType::Box_End) {
		m_is_opened = false;
		out_element = Ref<GSElement>(this);
		return false;
	}

	// at this point, this update has to do with any element other than the opened containers and "this"

	if (m_elements.size() <= m_current_index) {
		// out of bounds -> this is a new element this container doesn't have
		// => create new element, append it.
		Ref<GSElement> new_element = GuiScript::create_element(get_control(), arguments);
		new_element->update(arguments, out_element);
		m_elements.append(new_element);

		if (new_element->is_opened_container()) {
			m_opened_containers.push_back(new_element);
		}

	} else {

		Ref<GSElement> element = m_elements[m_current_index];
		const bool do_hard_change = element->update(arguments, out_element);

		if (!do_hard_change && element->is_opened_container()) {
			m_opened_containers.push_back(element);
		}

		if (do_hard_change) {
			while (m_elements.size() > m_current_index) {
				m_elements.pop_back();
			}

			Ref<GSElement> new_element = GuiScript::create_element(get_control(), arguments);
			new_element->update(arguments, out_element);
			m_elements.append(new_element);

			if (new_element->is_opened_container()) {
				m_opened_containers.push_back(new_element);
			}
		}
	}

	m_current_index++;
	return false;
}
