# System
import atexit
import glob
import os
import pickle
import sys
import time
from types import ModuleType
from collections import OrderedDict
from importlib.util import spec_from_file_location, module_from_spec

from SCons.Script import Environment , Repository, Export
from glob import glob
# Env
env = Environment()

# Include core sources

env_core = [
    "core/config/engine.cpp",
    "core/config/project_settings.cpp",
    "core/error/error_list.cpp",
    "core/error/error_macros.cpp",
    "core/debugger/engine_debugger.cpp",
    "core/debugger/script_debugger.cpp",
    "core/string/string.cpp",
    "core/string/print_string.cpp",
    "core/string/cstring.cpp",
    "core/string/string_buffer.cpp",
    "core/string/string_builder.cpp",
    "core/input/input.cpp",
    "core/input/input_map.cpp",
    "core/input/input_list.cpp",
    "core/input/input_game_pad.cpp",
    "core/math/geometry_2d.cpp",
    "core/math/geometry_3d.cpp",
    "core/math/color.cpp",
    "core/math/projection.cpp",
    "core/math/aabb.cpp",
    "core/math/face3.cpp",
    "core/math/math_func.cpp",
    "core/math/size2i.cpp",
    "core/math/rect2i.cpp",
    "core/math/transform_2d.cpp",
    "core/math/transform_3d.cpp",
    "core/math/vector2.cpp",
    "core/math/vector3.cpp",
    "core/math/vector4.cpp",
    "core/version.gen.h"

]

# Env thidrparty sources
env_thirdparty = [
    "libgl/raylib.h"
    "libgl/rcore.c",
    "libgl/rglfw.c",
    "libgl/rgl.h",
    "libgl/utils.c",
    "libgl/utils.h",
    "libgl/config.h",
    "libgl/rcamera.h",
    "libgl/platforms/rcore_android.c",
    "libgl/platforms/rcore_desktop_sdl.c",
    "libgl/platforms/rcore_web.c",
    "rcore_template.c",
    "rcore_dm.c",
    "libgui/raygui.h",
    "libjson/common.h",
    "libjson/json.h",
    "libgl/util.h",
    "libjson/src/json.c",
    "libjson/call/json.h",
    "libjson/impl/json.h",
    "libjson/impl/impl_objmap.h",
    "libjson/impl/impl_mem.h"


]

# Env Main
env_main = [
    "main/main.cpp",
    "main/main_toolbar.cpp",
    "main/main_timer.cpp",
    "main_splash_screen.cpp"
]





# Global Ps = ["default"]
platform_arg = ARGUMENTS.get("platform", ARGUMENTS.get("p", False))


platform = sys.platform  # Get the current platform

# Define platform-specific settings
env_windows = env.Clone()
env_linuxbsd = env.Clone()
env_macos = env.Clone()
env_android = env.Clone()


# Include System Libs
base_env = Environment(CPPPATH=['/usr/include'], CC='gcc')
# ... 

customs = ["custom.py"]

opts = Variables(customs, ARGUMENTS)

# Build Platform


# Platform specific settings
if platform_arg in libs:
    env = Environment(CXX='g++', CXXFLAGS=['-Wall', '-O2'], LIBS=libs[platform_arg])
else:
    print(f"Unsupported platform: {platform_arg}")
    print("Supported platforms: Windows, Linux, Darwin (MacOS), Android")
    sys.exit(1)

# Compiler platform
# Set compiler and compiler flags based on platform argument or default to the current system
platform_arg = sys.argv[1] if len(sys.argv) > 1 else platform.system()

# Add platform-specific libraries
env_windows.Append(LIBS=['wsock32', 'advapi32'])
env_linuxbsd.Append(LIBS=['pthread'])
env_macos.Append(LIBS=['CoreFoundation'])
env_android.Append(LIBS=['android', 'log'])

# Environment based on the platform
if platform == 'win32':
    current_env = env_windows
elif platform.startswith('linux') or platform.startswith('freebsd'):
    current_env = env_linuxbsd
elif platform == 'darwin':
    current_env = env_macos
elif platform == 'android':
    current_env = env_android
else:
    # Default to common settings for unknown platforms
    current_env = build_env


# Compilation environment setup
opts.Add("CXX", "C++ compiler")
opts.Add("CC", "C compiler")
opts.Add("LINK", "Linker")
opts.Add("CCFLAGS", "Custom flags for both the C and C++ compilers")
opts.Add("CFLAGS", "Custom flags for the C compiler")
opts.Add("CXXFLAGS", "Custom flags for the C++ compiler")
opts.Add("LINKFLAGS", "Custom flags for the linker")

# Include Dir
Repository('/core')
Repository('/editor')
Repository('/scene')
Repository('/server')
Repository('/doc')
Repository('/misc')
Repository('/modules')
Repository('/thirdparty')
Repository('/platform')
Repository('/main')
Repository('/tests')

# Include other

Repository('/usr/')
Repository('/usr/include/')
Repository('/usr/bin/')
Repository('/usr/lib/')

# Create a build directory if it doesn't exist
VariantDir('build', '.')

# Compile source files
objects = [env.Object('build/' + src.replace('.cpp', '.o'), src) for src in source_files]

# Build program
env.Program('config', objects)


Export('env')
