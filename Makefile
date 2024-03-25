.PHONY: all clean

# Define required environment variables
#------------------------------------------------------------------------------------------------
# Define target platform: PLATFORM_DESKTOP, PLATFORM_DESKTOP_SDL, PLATFORM_DRM, PLATFORM_ANDROID, PLATFORM_WEB
PLATFORM              ?= PLATFORM_DESKTOP

# Define required raylib variables
PROJECT_NAME          ?= patsher-engine
RAYLIB_VERSION        ?= 2.4.0
RAYLIB_PATH           ?= ..

# Define raylib source code path
RAYLIB_SRC_PATH       ?= ./thirdparty/libgl/

# Locations of raylib.h and libraylib.a/libraylib.so
# NOTE: Those variables are only used for PLATFORM_OS: LINUX, BSD
RAYLIB_INCLUDE_PATH   ?= /usr/local/include
RAYLIB_LIB_PATH       ?= /usr/local/lib

# Library type compilation: STATIC (.a) or SHARED (.so/.dll)
RAYLIB_LIBTYPE        ?= STATIC

# Build mode for project: DEBUG or RELEASE
BUILD_MODE            ?= RELEASE


# Use external GLFW library instead of rglfw module
USE_EXTERNAL_GLFW     ?= FALSE

# PLATFORM_DESKTOP_SDL: It requires SDL library to be provided externally
# WARNING: Library is not included in raylib, it MUST be configured by users
SDL_INCLUDE_PATH      ?= $(RAYLIB_SRC_PATH)/thirdparty/libgl/external/SDL2/include
SDL_LIBRARY_PATH      ?= $(RAYLIB_SRC_PATH)/thirdparty/libgl/external/SDL2/lib


# Determine PLATFORM_OS when required
ifeq ($(PLATFORM),$(filter $(PLATFORM),PLATFORM_DESKTOP PLATFORM_DESKTOP_SDL PLATFORM_WEB))
    # No uname.exe on MinGW!, but OS=Windows_NT on Windows!
    # ifeq ($(UNAME),Msys) -> Windows
    ifeq ($(OS),Windows_NT)
        PLATFORM_OS = WINDOWS
    else
        UNAMEOS = $(shell uname)
        ifeq ($(UNAMEOS),Linux)
            PLATFORM_OS = LINUX
        endif
        ifeq ($(UNAMEOS),FreeBSD)
            PLATFORM_OS = BSD
        endif
        ifeq ($(UNAMEOS),OpenBSD)
            PLATFORM_OS = BSD
        endif
        ifeq ($(UNAMEOS),NetBSD)
            PLATFORM_OS = BSD
        endif
        ifeq ($(UNAMEOS),DragonFly)
            PLATFORM_OS = BSD
        endif
        ifeq ($(UNAMEOS),Darwin)
            PLATFORM_OS = OSX
        endif
    endif
endif
ifeq ($(PLATFORM),PLATFORM_DRM)
    UNAMEOS = $(shell uname)
    ifeq ($(UNAMEOS),Linux)
        PLATFORM_OS = LINUX
    endif
endif


# Use Wayland display server protocol on Linux desktop (by default it uses X11 windowing system)
# NOTE: This variable is only used for PLATFORM_OS: LINUX
USE_WAYLAND_DISPLAY   ?= FALSE

# Define default C compiler: CC
#------------------------------------------------------------------------------------------------
CC = g++
CFLAGS = -std=c++11

MAIN_OBJECT = bin/main.o

# Source directories
SRC_DIRS := core/config/engine.cpp \
			 core/config/engine.h \
			 core/config/project_settings.cpp \
			 core/error/error_list.cpp \
			 core/error/error_list.h \
			 core/error/error_macros.cpp \
			 core/error/error_macros.h

# Source files
SRCS := $(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))


# Object files
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

# Output executable
TARGET := main


# Define default make program: MAKE
#------------------------------------------------------------------------------------------------
MAKE ?= make


# Define libraries required on linking: LDLIBS
# NOTE: To link libraries (lib<name>.so or lib<name>.a), use -l<name>
#------------------------------------------------------------------------------------------------
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),WINDOWS)
        # Libraries for Windows desktop compilation
        # NOTE: WinMM library required to set high-res timer resolution
        LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
    endif
    ifeq ($(PLATFORM_OS),LINUX)
        # Libraries for Debian GNU/Linux desktop compiling
        # NOTE: Required packages: libegl1-mesa-dev
        LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt

        # On X11 requires also below libraries
        LDLIBS += -lX11
        # NOTE: It seems additional libraries are not required any more, latest GLFW just dlopen them
        #LDLIBS += -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor

        # On Wayland windowing system, additional libraries requires
        ifeq ($(USE_WAYLAND_DISPLAY),TRUE)
            LDLIBS += -lwayland-client -lwayland-cursor -lwayland-egl -lxkbcommon
        endif
        # Explicit link to libc
        ifeq ($(RAYLIB_LIBTYPE),SHARED)
            LDLIBS += -lc
        endif

        # NOTE: On ARM 32bit arch, miniaudio requires atomics library
        LDLIBS += -latomic
    endif
    ifeq ($(PLATFORM_OS),OSX)
        # Libraries for OSX 10.9 desktop compiling
        # NOTE: Required packages: libopenal-dev libegl1-mesa-dev
        LDLIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
    endif
    ifeq ($(PLATFORM_OS),BSD)
        # Libraries for FreeBSD, OpenBSD, NetBSD, DragonFly desktop compiling
        # NOTE: Required packages: mesa-libs
        LDLIBS = -lraylib -lGL -lpthread -lm

        # On XWindow requires also below libraries
        LDLIBS += -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor
    endif
    ifeq ($(USE_EXTERNAL_GLFW),TRUE)
        # NOTE: It could require additional packages installed: libglfw3-dev
        LDLIBS += -lglfw
    endif
endif


all: directories $(TARGET)

directories:
	mkdir -p bin
	mkdir -p bin/main
	mkdir -p $(addprefix bin/,$(SRC_DIRS))
    
$(TARGET): $(OBJECTS) $(MAIN_OBJECT)
	$(CXX) $^ -o $@ $(LDFLAGS)

bin/%.o: $(addsuffix /%.cpp,$(SRC_DIRS))
	$(CXX) -c $< -o $@ $(CXXFLAGS)

bin/main.o: main/main.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -rf bin $(TARGET)

