#ifndef GODOTJS_CONFIG_H
#define GODOTJS_CONFIG_H

#ifndef JSB_DEBUG
#   if defined(DEBUG_ENABLED)
#       define JSB_DEBUG 1
#   else
#       define JSB_DEBUG 0
#   endif
#endif

// Enable the debugger bridge.
// For v8, use Chrome devtools with the following link by default:
//      devtools://devtools/bundled/inspector.html?experiments=true&v8only=true&ws=127.0.0.1:9229/1
// For JavaScriptCore, use Safari.
#define JSB_WITH_DEBUGGER JSB_DEBUG

// lower log levels are completely skipped (at compile-time)
// see `internal/jsb_log_severity.def.h`
#ifndef JSB_MIN_LOG_LEVEL
#   if JSB_DEBUG
#       define JSB_MIN_LOG_LEVEL Verbose
#   else
#       define JSB_MIN_LOG_LEVEL Warning
#   endif
#endif // JSB_MIN_LOG_LEVEL

// enable jsb_check
#ifndef JSB_WITH_CHECK
#define JSB_WITH_CHECK JSB_DEBUG
#endif

// output verbose log anyway even if `OS::get_singleton()->is_stdout_verbose()` is false
#define JSB_VERBOSE_ENABLED 0

// print benchmark
#define JSB_BENCHMARK 1

// [EXPERIMENTAL] enable auto-complete feature in the input field of REPL.
//NOTE this feature introduces side effects since it will try to evaluate the input string before you submit.
#define JSB_REPL_AUTO_COMPLETE 1

// Check if the type of `p_pointer` is really NativeClassType::GodotObject.
#define JSB_VERIFY_GODOT_OBJECT 1

// (only available when using v8)
// enable `RequestGarbageCollectionForTesting` (not recommended)
#define JSB_EXPOSE_GC_FOR_TESTING 0

// (only available when using v8)
// print gc time cost in milliseconds
#define JSB_PRINT_GC_TIME 1

// (only available in editor build)
// support hot-reload for javascript modules
#define JSB_SUPPORT_RELOAD 1

// translate the js source stacktrace with source map (currently, the `.map` file must locate at the same filename & directory of the js source)
#define JSB_WITH_SOURCEMAP 1

// log with C++ [source filename, line number, function name]
#define JSB_LOG_WITH_SOURCE 0

// construct a Variant with `Variant::construct` instead of `VariantUtilityFunctions::type_convert`
#define JSB_CONSTRUCT_DEFAULT_VARIANT_SLOW 0

// NOT IMPLEMENTED YET
#define JSB_WITH_STATIC_BINDINGS 0

// utf16 conversion may have less overhead, but uses more memory?
#define JSB_UTF16_CONV_PREFERRED 1

// quickjs.impl only, all Object(JSValue) must be explicitly free-ed on the Isolate disposing
#define JSB_STRICT_DISPOSE 1

// use bigint if a value can not represented as Integer(Number)
#define JSB_WITH_BIGINT 1

// use `BigInt` if a value from godot greater than JSB_MAX_SAFE_INTEGER which can not represented as Integer(Number).
// used only if `JSB_WITH_BIGINT` is enabled.
// DO NOT CHANGE THIS VALUE.
#define JSB_MAX_SAFE_INTEGER (((int64_t)1 << 53) - 1) // 9007199254740991

// [EXPERIMENTAL] use optimized wrapper function calls if possible
#define JSB_FAST_REFLECTION 1

// implicitly convert a javascript array as godot Vector<T> which is convenient but less performant if massively used
#define JSB_IMPLICIT_PACKED_ARRAY_CONVERSION 1

// not to generate method declaration if already defined as get/set property
#define JSB_EXCLUDE_GETSET_METHODS 1

// [low level] debug value add/remove issues in SArray
#define JSB_SARRAY_DEBUG 0
#define JSB_SARRAY_CONSISTENCY_CHECK 0

// use url scheme to avoid the file separator conversion on windows.
// disable if not supported by the remote debugger.
#define JSB_WITH_URI_SCRIPT_ORIGIN 0

// [EXPERIMENTAL] DONT CHANGE IT
#define JSB_THREADING 1

// [EXPERIMENTAL] DONT CHANGE IT
#define JSB_OBJECT_DB_THREADING 1

// slots for object/script/class info is reallocated on heap (as a whole block of memory)
// a suitable value can avoid unnecessary reallocation
#define JSB_MASTER_INITIAL_OBJECT_SLOTS (1024 * 64)
#define JSB_MASTER_INITIAL_SCRIPT_SLOTS 1024
#define JSB_MASTER_INITIAL_CLASS_EXTRA_SLOTS 0

#define JSB_WORKER_INITIAL_OBJECT_SLOTS (1024 * 8)
#define JSB_WORKER_INITIAL_SCRIPT_SLOTS 1024
#define JSB_WORKER_INITIAL_CLASS_SLOTS 512

#define JSB_DTS_EXT "d.ts"
#define JSB_TYPESCRIPT_EXT "ts"
#define JSB_JAVASCRIPT_EXT "js"
#define JSB_COMMONJS_EXT   "cjs"

// A helper version tag for the jsb.*.bundle.js scripts (which is embedded in .cpp source).
// It could ensure your engine built with the expected version of the jsb bundle scripts.
// If static_assert in `jsb_project_preset.gen.cpp` fails, please run your `scons` command again to update all bundle scripts.
#define JSB_BUNDLE_VERSION 7

#endif
