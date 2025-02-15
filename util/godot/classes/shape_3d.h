#ifndef ZN_GODOT_SHAPE_3D_H
#define ZN_GODOT_SHAPE_3D_H

#include "../core/version.h"

#if defined(ZN_GODOT)

#if GODOT_VERSION_MAJOR == 4 && GODOT_VERSION_MINOR <= 2
#include <scene/resources/shape_3d.h>
#else
#include <scene/resources/3d/shape_3d.h>
#endif

#elif defined(ZN_GODOT_EXTENSION)
#include <godot_cpp/classes/shape3d.hpp>
using namespace godot;
#endif

namespace zylann::godot {

#ifdef DEBUG_ENABLED
inline void set_shape_3d_debug_color(Shape3D &shape, const Color color) {
	// TODO GDX: `set_debug_color` is not exposed to GDExtensions
	// Which means there is no way for us to show debug shapes of the terrain when the option is enabled, because they
	// default to transparent black, which is invisible
#if defined(ZN_GODOT)
#if GODOT_VERSION_MAJOR == 4 && GODOT_VERSION_MINOR >= 4
	shape.set_debug_color(color);
#endif
#endif
}
#endif

} // namespace zylann::godot

#endif // ZN_GODOT_SHAPE_3D_H
