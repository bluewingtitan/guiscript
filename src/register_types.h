#ifndef GUISCRIPT_REGISTER_TYPES_H
#define GUISCRIPT_REGISTER_TYPES_H

#include <godot_cpp/core/class_db.hpp>
using namespace godot;

void register_guiscript_types(ModuleInitializationLevel p_level);
void unregister_guiscript_types(ModuleInitializationLevel p_level);

#endif