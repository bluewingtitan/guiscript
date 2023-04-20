#include "guiscript.h"

#include "gs_container.h"
#include "gs_rootcontainer.h"
#include "gs_boxcontainer.h"
#include "gs_button.h"
#include "gs_label.h"
#include "gs_separator.h"

using namespace godot;

auto GuiScript::update(const GSArguments& arguments, Ref<GSElement>& OutElement) -> bool {
	return m_root_container->update(arguments, OutElement);
}

auto GuiScript::update(const GSArguments &arguments) -> bool {
	Ref<GSElement> dummy_ref;

	return update(arguments, dummy_ref);
}

auto GuiScript::create_element(Control *parent, const GSArguments &arguments)  -> Ref<GSElement> {
	Ref<GSElement> element;

	switch (arguments.type) {
		case GDElementType::Label:
			element = Ref<GSElement>(memnew(GSLabel));
			break;

		case GDElementType::Box_Start:
			element = Ref<GSElement>(memnew(GSBoxContainer));
		break;

		case GDElementType::Box_End:
			throw std::runtime_error("Misaligned Box End");
		break;

		case GDElementType::Button:
			element = Ref<GSElement>(memnew(GSButton));
		break;

		case GDElementType::Separator:
			element = Ref<GSSeparator>(memnew(GSSeparator));
			break;

		default:
			element = Ref<GSElement>(memnew(GSLabel));
			break;
	}

	element->initialize(parent, arguments);
	return element;
}

void GuiScript::_bind_methods() {
	ClassDB::bind_method(D_METHOD("begin_ui"), &GuiScript::begin_ui);
	ClassDB::bind_method(D_METHOD("label", "text"), &GuiScript::label);
	ClassDB::bind_method(D_METHOD("begin_hbox"), &GuiScript::begin_hbox);
	ClassDB::bind_method(D_METHOD("begin_vbox"), &GuiScript::begin_vbox);
	ClassDB::bind_method(D_METHOD("end_box"), &GuiScript::end_box);
	ClassDB::bind_method(D_METHOD("vseparator"), &GuiScript::vseparator);
	ClassDB::bind_method(D_METHOD("hseparator"), &GuiScript::hseparator);
	ClassDB::bind_method(D_METHOD("button", "text"), &GuiScript::button);
}

void GuiScript::begin_ui() {
	m_ui_changed = false;
	m_root_container->on_begin_ui();
}

auto GuiScript::button(String title) -> bool {
	GSArguments args{GDElementType::Button};
	args.text = title;

	Ref<GSElement> button_ref{};
	m_ui_changed = update(args, button_ref);

	if (button_ref.is_valid()) {
		Ref<GSButton> tbutton_ref = button_ref;

		if (tbutton_ref.is_valid() && tbutton_ref->was_pressed()) {
			tbutton_ref->reset_was_pressed();
			return true;
		}
	}

	return false;
}

auto GuiScript::label(String text) -> void {
	GSArguments args{GDElementType::Label};
	args.text = text;

	m_ui_changed = update(args);
}

auto GuiScript::begin_hbox() -> void {
	GSArguments args{GDElementType::Box_Start};
	args.is_horizontal = true;

	m_ui_changed = update(args);
}

auto GuiScript::begin_vbox() -> void {
	GSArguments args{GDElementType::Box_Start};
	args.is_horizontal = false;

	m_ui_changed = update(args);
}

auto GuiScript::end_box() -> void {
	GSArguments args{GDElementType::Box_End};

	m_ui_changed = update(args);
}

auto GuiScript::vseparator() -> void {
	GSArguments args{GDElementType::Separator};
	args.is_horizontal = false;

	m_ui_changed = update(args);
}

auto GuiScript::hseparator() -> void {
	GSArguments args{GDElementType::Separator};
	args.is_horizontal = true;

	m_ui_changed = update(args);
}

GuiScript::GuiScript() {
	m_root_container = Ref<GSRootContainer>(memnew(GSRootContainer));
	m_root_container->initialize(this, GSArguments{GDElementType::Box_Start});
}

GuiScript::~GuiScript() {
    m_root_container.unref();
}

void GuiScript::_process(float delta){
    // do nothing for now.
}
