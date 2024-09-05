#include "jsb_settings.h"

#include "core/config/engine.h"
#include "core/config/project_settings.h"
#include "core/variant/variant.h"

#ifdef TOOLS_ENABLED
#include "editor/editor_settings.h"
#endif

#include "jsb_internal_pch.h"

#define JSB_SET_RESTART(val) (val)
#define JSB_SET_IGNORE_DOCS(val) (val)
#define JSB_SET_BASIC(val) (val)
#define JSB_SET_INTERNAL(val) (val)

namespace jsb::internal
{
#ifdef TOOLS_ENABLED
    static constexpr char kEdDebuggerPort[] =     JSB_MODULE_NAME_STRING "/debugger/editor_port";
    static constexpr char kEdIgnoredClasses[] =     JSB_MODULE_NAME_STRING "/codegen/ignored_classes";
#endif

    static constexpr char kRtDebuggerPort[] =     JSB_MODULE_NAME_STRING "/debugger/runtime_port";
    static constexpr char kRtSourceMapEnabled[] = JSB_MODULE_NAME_STRING "/logger/source_map_enabled";
    static constexpr char kRtPackagingWithSourceMap[] = JSB_MODULE_NAME_STRING "/packaging/source_map_included";

    void init_settings()
    {
        static bool inited = false;
        if (!inited)
        {
            inited = true;
#ifdef TOOLS_ENABLED
            if (!EditorSettings::get_singleton()) {
                EditorSettings::create();
                jsb_check(EditorSettings::get_singleton());
            }
            _EDITOR_DEF(kEdDebuggerPort, 9230, true);
            _EDITOR_DEF(kEdIgnoredClasses, PackedStringArray(), false);
#endif
            _GLOBAL_DEF(kRtDebuggerPort, 9229, JSB_SET_RESTART(true), JSB_SET_IGNORE_DOCS(false), JSB_SET_BASIC(false), JSB_SET_INTERNAL(false));
            _GLOBAL_DEF(kRtSourceMapEnabled, true, JSB_SET_RESTART(false), JSB_SET_IGNORE_DOCS(false), JSB_SET_BASIC(true),  JSB_SET_INTERNAL(false));
            _GLOBAL_DEF(kRtPackagingWithSourceMap, true, JSB_SET_RESTART(false), JSB_SET_IGNORE_DOCS(false), JSB_SET_BASIC(true),  JSB_SET_INTERNAL(false));
        }
    }

#ifdef TOOLS_ENABLED
    PackedStringArray Settings::get_ignored_classes()
    {
        init_settings();
        return EDITOR_GET(kEdIgnoredClasses);
    }
#endif

    uint16_t Settings::get_debugger_port()
    {
        init_settings();
#ifdef TOOLS_ENABLED
        if (Engine::get_singleton()->is_editor_hint())
        {
            return EDITOR_GET(kEdDebuggerPort);
        }
#endif
        return GLOBAL_GET(kRtDebuggerPort);
    }

    bool Settings::get_sourcemap_enabled()
    {
        init_settings();
        return GLOBAL_GET(kRtSourceMapEnabled);
    }

    bool Settings::is_packaging_with_source_map()
    {
        init_settings();
        return GLOBAL_GET(kRtPackagingWithSourceMap);
    }

    String Settings::get_jsb_out_dir_name()
    {
        return ProjectSettings::get_singleton()->get_project_data_dir_name().path_join(JSB_MODULE_NAME_STRING);
    }

    String Settings::get_tsbuildinfo_path()
    {
        return ProjectSettings::get_singleton()->get_project_data_dir_name().path_join(".tsbuildinfo");
    }

    String Settings::get_jsb_out_res_path()
    {
        return "res://" + get_jsb_out_dir_name();
    }

    String Settings::get_indentation()
    {
#ifdef TOOLS_ENABLED
        if (Engine::get_singleton()->is_editor_hint())
        {
            init_settings();
            // use_space_indentation
            if (!!EDITOR_GET("text_editor/behavior/indent/type"))
            {
                const int indent_size = EDITOR_GET("text_editor/behavior/indent/size");
                return String(" ").repeat(indent_size);
            }
        }
#endif
        return "\t";
    }

}
