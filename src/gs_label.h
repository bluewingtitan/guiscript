#pragma once

#include "gs_element.h"

namespace godot{
    class Label;
}

using namespace godot;

class GSLabel: public GSElement {
	GDCLASS(GSLabel, GSElement)

private:
	Label* m_label {nullptr};

public:
	auto is_opened_container() -> bool override;
	auto get_control() -> Control * override;

	auto initialize(Control* parent, const GSArguments& arguments) -> void override;
	auto update(const GSArguments& arguments, Ref<GSElement>& out_element) -> bool override;

	explicit GSLabel();
	virtual ~GSLabel() override;

};

