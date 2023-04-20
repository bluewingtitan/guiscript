#pragma once

#include <godot_cpp/classes/control.hpp>

using namespace godot;


enum class GDElementType {
	Label,
	Button,
	Separator,

	Box_Start,
	Box_End,
};

class GSElement;
class GSRootContainer;

/**
* \brief Summarizes an element GUIScript wants to create
*/
struct GSArguments {
	/**
	 * \brief (For Box_Start and Separator) determines whether the container acts horizontally or vertically
	 */
	bool is_horizontal{false};

	GDElementType type;
	String text {""};

	GSArguments(GDElementType in_type): type(in_type){}
};

class GuiScript : public Control {
    GDCLASS(GuiScript, Control)

private:
	bool m_ui_changed = false;
	Ref<GSRootContainer> m_root_container;

	auto update(const GSArguments& arguments, Ref<GSElement>& OutElement) -> bool;
	auto update(const GSArguments& arguments) -> bool;

	/**
	 * \brief Called to update the ui
	 */
	//auto _process_ui() -> void;

protected:
    static void _bind_methods();

public:
    GuiScript();
    ~GuiScript();

    void _process(float delta);

	virtual void begin_ui();

    // GuiScript-Elements
	static auto create_element(Control *parent, const GSArguments &arguments) -> Ref<GSElement>;

    /// Creates a button with the passed text
    /// \returns true if button was pressed in last frame
	auto button(String text) -> bool;

    /// Creates a label with the passed text
	auto label(String text) -> void;

    /// Puts all following elements into a hbox (until closed with end_box)
	auto begin_hbox() -> void;


    /// Puts all following elements into a vbox (until closed with end_box)
	auto begin_vbox() -> void;

    /// Closes the box that was last opened
	auto end_box() -> void;

    /// Inserts a vertical seperator
	auto vseparator() -> void;

    /// Inserts a horizontal separator
	auto hseparator() -> void;
};

