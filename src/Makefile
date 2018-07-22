# Set the APPNAME if it hasn't been set 
APPNAME ?= openGLTest

VPATH=src

# The name of the executable to be created
BIN_NAME := $(APPNAME)

include CommonMake.mk

debug: dobuild

# Removes all build files
clean:
	$(CMD_PREFIX)echo "Deleting $(BIN_NAME) symlink"
	$(CMD_PREFIX)$(RM) $(BIN_NAME)
	$(CMD_PREFIX)echo "Deleting directories"
	$(CMD_PREFIX)$(RM) -r $(SRC_PATH)/build

# Perform the build
dobuild: dirs
	$(CMD_PREFIX)echo "Beginning build"
	$(CMD_PREFIX)$(MAKE) $(MAKE_MULTI_FLAGS) all $(NO_PRINT_DIRECTORY)

# Create the directories used in the build
dirs:
	$(CMD_PREFIX)echo "Creating directories"
	$(CMD_PREFIX) if [ -n "$(OBJECTS)" ]; then mkdir -p $(dir $(OBJECTS)); fi
	$(CMD_PREFIX)mkdir -p $(BIN_PATH)


# Main rule, checks the executable and symlinks to the output
all: $(BIN_PATH)/$(BIN_NAME)
	$(CMD_PREFIX)echo "Making symlink: $(BIN_NAME) -> $<"
	$(CMD_PREFIX)$(RM) $(BIN_NAME)
	$(CMD_PREFIX)ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)


# Link the executable
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "Linking..."
	$(CMD_PREFIX)$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) $(OPENGL_LIBS) -o $@ 

$(OBJECT_PATH)/%.o: %.$(SRC_EXT)
	@echo "Compiling $< --> $@"
	$(CMD_PREFIX)$(CXX) $(CXXFLAGS) $(OPENGL_FLAGS) -MP -MMD -c $< -o $@
