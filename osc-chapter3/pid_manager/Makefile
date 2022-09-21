# Common directories, files names and variables
SRC_EXT := c
HDR_EXT := h
NAME := pid_manager
COMNON_PATH := ./
BUILD_PATH := $(COMNON_PATH)build
BIN_PATH := $(COMNON_PATH)bin
SRC_PATH := $(COMNON_PATH)src
INCLUDE_PATH := $(shell find $(SRC_PATH) -type d) ./include /usr/local/include
INCLUDE_FLAGS := $(addprefix -I,$(INCLUDE_PATH))
TARGET := $(BIN_PATH)/$(NAME)

# Source files, headers, objects and dependencies
SRC_FILES := $(shell find $(SRC_PATH) -type f -name '*.${SRC_EXT}' | sort -k 1nr | cut -f2-)
INCLUDE_FILES := $(shell find $(INCLUDE_PATH) -type f -name '*.${HDR_EXT}' | sort -k 1nr | cut -f2-)
OBJ_FILES := $(SRC_FILES:$(SRC_PATH)/%.${SRC_EXT}=$(BUILD_PATH)/%.o)
DEP_FILES := $(OBJECTS:.o=.d)

# Compiler/linker flags and variables
CC ?= g++
INCLUDES := $(INCLUDE_FLAGS)
CFLAGS := -Wall -Werror -Wextra -Wpedantic -g ${INCLUDES} -pipe -std=c99
LDFLAGS  := -lm
LIBS :=

# doxygen documentation
DOX_PATH = doc
DOX_FILE = Doxyfile
ASSETS_PATH = assets

# First and default target
.PHONY: release
release: CFLAGS += -O3 -mtune=native -march=native -fomit-frame-pointer
release: all

# Creating documentation
.PHONY: docs
docs:
	@mkdir -p $(DOX_PATH)
	@doxygen $(DOX_FILE) &>/dev/null

# Project Cleaning
.PHONY: clean
clean:
	@$(RM) -r $(BUILD_PATH)
	@$(RM) -r $(BIN_PATH)
	@$(RM) -r $(DOX_PATH)

# base directories creation
$(BUILD_PATH) $(BIN_PATH) $(DOX_PATH) $(SRC_PATH) $(ASSETS_PATH) include:
	@mkdir -p $@

# all target, which depends on the base dirs and the target file
.PHONY: all
all: $(BUILD_PATH) $(BIN_PATH) $(DOX_PATH) $(SRC_PATH) $(ASSETS_PATH) include $(TARGET)

$(TARGET): $(INCLUDE_FILES) $(OBJ_FILES)
	mkdir -p $(dir $@)
	$(CC) $(OBJ_FILES) -o $@ $(CFLAGS) $(LDFLAGS) $(LIBS)

-include $(DEP_FILES)
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	mkdir -p $(dir $@) # TODO: find a better way to do this
	$(CC) $(CFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@

# Testing
.PHONY: test
test: all
	# TODO

# Debugging
.PHONY: debug
debug: CFLAGS += -g
debug: all
	@gdb ${TARGET}

# Running
.PHONY: run
run: all
	@./${TARGET}

yes:
	@echo $(OBJ_FILES)
