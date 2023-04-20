#ifndef GS_CONTAINER_H
#define GS_CONTAINER_H

#include "gs_element.h"

using namespace godot;

class GSContainer: public GSElement{
	GDCLASS(GSContainer, GSElement)

protected:
	int m_last_index{0};
	int m_current_index{0};

	bool m_is_opened{false};
	Array m_elements{};
	Array m_opened_containers{};

	virtual auto is_horizontal() -> bool;

public:
	auto on_begin_ui() -> void override;

	auto force_close() -> void;

	auto is_opened_container() -> bool override;

	auto initialize(Control* parent, const GSArguments& arguments) -> void override;
	auto update(const GSArguments& arguments, Ref<GSElement>& out_element) -> bool override;

	explicit GSContainer();
	virtual ~GSContainer() override;
};

#endif