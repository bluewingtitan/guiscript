#pragma once

#include "gs_element.h"

namespace godot {
class Separator;
}

using namespace godot;

class GSSeparator: public GSElement {
	GDCLASS(GSSeparator, GSElement)

private:
	bool m_is_horizontal{false};
	Separator* m_separator {nullptr};

public:
	auto is_opened_container() -> bool override;
	auto get_control() -> Control * override;

	auto initialize(Control* parent, const GSArguments& arguments) -> void override;
	auto update(const GSArguments& arguments, Ref<GSElement>& out_element) -> bool override;

	explicit GSSeparator();
	virtual ~GSSeparator() override;
};

