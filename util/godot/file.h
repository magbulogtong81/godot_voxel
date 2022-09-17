#ifndef ZN_GODOT_FILE_H
#define ZN_GODOT_FILE_H

#if defined(ZN_GODOT)
#include <core/io/file_access.h>
#elif defined(ZN_GODOT_EXTENSION)
#include <godot_cpp/classes/file.hpp>
using namespace godot;
#endif

#include "../span.h"
#include "funcs.h"

namespace zylann {

#if defined(ZN_GODOT)
typedef FileAccess GodotFile;
#elif defined(ZN_GODOT_EXTENSION)
typedef File GodotFile;
#endif

inline Ref<GodotFile> open_file(const String path, GodotFile::ModeFlags mode_flags, Error &out_error) {
#if defined(ZN_GODOT)
	return FileAccess::open(path, mode_flags, &out_error);
#elif defined(ZN_GODOT_EXTENSION)
	Ref<File> file;
	file.instantiate();
	out_error = file->open(path, mode_flags);
	if (out_error != godot::OK) {
		return Ref<File>();
	} else {
		return file;
	}
#endif
}

inline uint64_t get_buffer(GodotFile &f, Span<uint8_t> dst) {
#if defined(ZN_GODOT)
	return f.get_buffer(dst.data(), dst.size());
#elif defined(ZN_GODOT_EXTENSION)
	PackedByteArray bytes = f.get_buffer(dst.size());
	copy_to(dst, bytes);
	return bytes.size();
#endif
}

inline uint64_t store_buffer(GodotFile &f, Span<const uint8_t> src) {
#if defined(ZN_GODOT)
	return f.store_buffer(src.data(), src.size());
#elif defined(ZN_GODOT_EXTENSION)
	PackedByteArray bytes;
	copy_to(bytes, src);
	f.store_buffer(bytes);
	// Impossible to tell how many bytes were actually written, the Godot API doesn't return anything...
	return src.size();
#endif
}

inline String get_as_text(GodotFile &f) {
#if defined(ZN_GODOT)
	return f.get_as_utf8_string();
#elif defined(ZN_GODOT_EXTENSION)
	return f.get_as_text();
#endif
}

} // namespace zylann

#endif // ZN_GODOT_FILE_H