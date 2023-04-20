#include "register_types.h"

#include "gs_element.h"
#include "gs_label.h"
#include "gs_separator.h"
#include "gs_boxcontainer.h"
#include "gs_container.h"
#include "gs_rootcontainer.h"
#include "guiscript.h"
#include "gs_button.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void register_guiscript_types(ModuleInitializationLevel p_level){
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

	ClassDB::register_class<GuiScript>();
	ClassDB::register_abstract_class<GSElement>();
	ClassDB::register_abstract_class<GSContainer>();
	ClassDB::register_class<GSRootContainer>();
	ClassDB::register_class<GSLabel>();
	ClassDB::register_class<GSSeparator>();
	ClassDB::register_class<GSButton>();
	ClassDB::register_class<GSBoxContainer>();
}

void unregister_guiscript_types(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT guiscript_init(const GDExtensionInterface *p_interface, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
    godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

    init_obj.register_initializer(register_guiscript_types);
    init_obj.register_terminator(unregister_guiscript_types);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
}
}