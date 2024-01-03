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

# Env
env = Environment()

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

# Build Platform
def _build_platform() -> None:
	# Modify settings specific to each platform
	env_windows.Append(CPPFLAGS=['-DWINDOWS'])
	env_linuxbsd.Append(CPPFLAGS=['-DLINUX_BSD'])
	env_macos.Append(CPPFLAGS=['-DMACOS'])
	env_android.Append(CPPFLAGS=['-DANDROID'])
	
	selected_platform = ""
	
	if env_base["platform"] != "":
		selected_platform = env_base["platform"]
	elif env_base["p"] != "":
		selected_platform = env_base["p"]
	else:
    # Missing `platform` argument, try to detect platform automatically
	if (
	sys.platform.startswith("linux")
        or sys.platform.startswith("dragonfly")
        or sys.platform.startswith("freebsd")
        or sys.platform.startswith("netbsd")
        or sys.platform.startswith("openbsd")
    ):
        selected_platform = "linuxbsd"
    elif sys.platform == "darwin":
        selected_platform = "macos"
    elif sys.platform == "win32":
        selected_platform = "windows"
    else:
        print("Could not detect platform automatically. Supported platforms:")
        for x in platform_list:
            print("\t" + x)
        print("\nPlease run SCons again and select a valid platform: platform=<string>")

    if selected_platform != "":
        print("Automatically detected platform: " + selected_platform)

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
Repository(/'editor')
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

Repository(/'usr/')
Repository('/usr/include/')
Repository('/usr/bin/')
Repository('/usr/lib/')

# Include SCsub files
SConsript('core/SCsub')
SConsript('editor/SCsub')
SConsript('modules/SCsub')
SConsript('scene/SCsub')
SConsript('resources/SCsub')
SConsript('servers/SCsub')
SConsript('thirdparty/SCsub')
Export("env")
