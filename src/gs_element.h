#ifndef GS_ELEMENT_H
#define GS_ELEMENT_H

#include <godot_cpp/classes/ref_counted.hpp>

namespace godot{
	class Control;
}

using namespace godot;

struct GSArguments;

class GSElement: public RefCounted {
	GDCLASS(GSElement, RefCounted)

protected:
    static void _bind_methods();

	Control* m_parent{nullptr};

public:
	GSElement();
	virtual ~GSElement() override;
    
	/**
	 * \brief Declares whether this gui element is representing a container
	 * \return True if is container
	 */
	virtual auto is_opened_container() -> bool;

	/**
	 * \brief Returns a underlying control
	 * \return underlying control
	 */
	virtual auto get_control() -> Control*;

	virtual auto on_begin_ui() -> void;

	virtual auto initialize(Control* parent, const GSArguments& arguments) -> void;


    /**
     * \returns True if this element shall be handled as invalid
    */
	virtual auto update(const GSArguments& arguments, Ref<GSElement>& out_element) -> bool;
};

#endif