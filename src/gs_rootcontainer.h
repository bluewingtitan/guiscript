#pragma once
#include "gs_container.h"

namespace godot {
class VBoxContainer;
}

using namespace godot;

class GSRootContainer: public GSContainer{
	GDCLASS(GSRootContainer, GSContainer)

	int m_last_index{0};
	VBoxContainer* m_container{nullptr};

protected:
	auto is_horizontal() -> bool override;

public:
	auto is_opened_container() -> bool override;
	auto initialize(Control *parent, const GSArguments &arguments) -> void override;
	auto get_control() -> Control * override;

	auto update(const GSArguments &arguments, Ref<GSElement>& out_element) -> bool override;

	GSRootContainer();
	virtual ~GSRootContainer() override;

};

