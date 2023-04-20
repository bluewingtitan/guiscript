#pragma once

#include "gs_container.h"

using namespace godot;

class GSBoxContainer: public GSContainer{
	GDCLASS(GSBoxContainer, GSContainer)

	class BoxContainer* m_container{nullptr};

	bool m_is_horizontal{false};

protected:
	auto is_horizontal() -> bool override;

public:
	auto initialize(Control *parent, const GSArguments &arguments) -> void override;
	auto get_control() -> Control * override;

	GSBoxContainer();
	virtual ~GSBoxContainer() override;

};

