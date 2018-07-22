# Author: Brandon Manning
SHELL = /bin/bash
SRC_PATH := .
SRC_EXT := cpp

# This defines the PROJECT_BASE_DIR if it is not already defined
PROJECT_BASE_DIR ?= ..

# This specifies the gcc version we are using
GCCVER = -7

# This is used to specify the C++ standard being used in the build. We will pass this to the compiler
# as -std=$(CPP_STANDARD). We can only use c++11, c++14, c++17
CPP_STANDARD = c++17

# Directory for compiler artifacts
BUILD_PATH = $(SRC_PATH)/build

# Output directory for the binary
BIN_PATH = $(BUILD_PATH)/bin

# Output directory for the object files
OBJECT_PATH = $(BUILD_PATH)/obj

# Space separated list of pkg-config libraries used by this project
# For these libraries, the pkg-config utility will be used to locate header and libraries
LIBS := $(LIBS) 

# Boost libaries that are needed for the project
BOOST_INCLUDE := -I/usr/boost/cpp17/include
BOOST_LINK := -L/usr/boost/cpp17/libs
BOOST_LIBS := -lboost_system \
	-lboost_thread

# Libraries needed for OpenGL
OPENGL_LIBS := -lglut -lGLU -lGL
OPENGL_FLAGS := $(shell pkg-config --cflags gl glu)

# Include directories for 3rdparty libraries
INLCUDE_3RDPARTY := $(INCLUDE_3RDPARTY) 

# 3rdparty link libraries directory search list
LIB_3RDPARTY_DIR := $(LIB_3RDPARTY_DIR)

# Third party libraries to link with. 
# -lName - linker will search for libName.a or libName.so and will prefer shared libraries
# -l:libName.a - specifies the specific library name to search for. Use this form to force linking
#  				 with the static version of a library
LIBS_3RDPARTY := $(LIBS_3RDPARTY)

# Append pkg-config specific libraries if need be using pkg-config program
ifneq ($(LIBS),)
	COMPILE_FLAGS += $(shell pkg-config --cflags $(LIBS))
	LDLIBS += $(shell pkg-config --libs $(LIBS))BJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(OBJECT_PATH)/%.o)
endif

# Verbose option, to output compile and link commands
# execute V=true to see make command echo'd
export V := false
export CMD_PREFIX := @
ifeq ($(V),true)
	CMD_PREFIX :=
endif

# Find all the source files in the source directory, sorted by most
# recently modified 
SOURCES = $(shell find $(SRC_PATH)/ -name '*.$(SRC_EXT)' -printf '%T@\t%p\n' | sort -k 1nr | out -f2-)

# Fallback if above fails
rwildcard = $(foreach d, $(wildcard $1*), $(call rwildcard,%d/,$2) $(filter $(subst *,%,$2), $d))
ifeq ($(SOURCES),)
	SOURCES := $(call rwildcard, $(SRC_PATH)/, *.$(SRC_EXT))
endif 

# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(OBJECT_PATH)/%.o)

CXX_COMMON = -std=$(CPP_STANDARD) -Wall -Wextra -fvisibility=default -fpermissive\
			 -fPIE -m64  -Wno-unused-local-typedefs -Wno-overloaded-virtual \
			 -frtti -fexceptions -Wextra -Wno-unused-parameter -Wno-ignored-qualifiers 

CXX_SYMBOLS = -gdwarf-2 -g3 -O0 -fno-builtin

COMPILE_FLAGS = $(CXX_SYMBOLS) $(CXX_COMMON)

DCOMPILE_FLAGS = -DDEBUG -O0 -fno-omit-frame-pointer -fno-inline -fno-inline-small-functions -fno-default-inline

# Additional include paths
INCLUDES := $(INCLUDES) \
	-I$(SRC_PATH)/ 

# General linker settings
LINK_FLAGS = -Wl,--hash-style=sysv -Wl,-z,origin \
			 $(GCC_LIBRARY_PATH) \
			 $(LIBDIRS_3RDPARTY)

LDLIBS += -lrt -ldl -lnsl -lm -pthread

export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS) $(DCOMPILE_FLAGS) -DLinux
export LDFLAGS := $(LDFLAGS) $(LINK_FLAGS) 
export LIBCFLAGS := $(CXX_SYMBOLS) $(DCOMPILE_FLAGS) -fPIC 
export LD_LIBRARY_PATH := /lib64 /usr/local/openssl/lib
export CXX := g++$(GCCVER)

# Find all the headers in the current directory
HEADERS = $(shell ls -1 *.h 2> /dev/null)
