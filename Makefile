CXX      = g++
SRC_DIR  = src
INC_DIR  = $(SRC_DIR)/headers
OBJ_DIR  = build
TARGET   = main.exe

CXXFLAGS = -Wall -std=c++20 -I$(INC_DIR) -IC:/msys64/ucrt64/include -MMD -MP
LDFLAGS  = -LC:/msys64/ucrt64/lib -lSDL3_image -lSDL3 -mwindows -mconsole

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

# Pick shell-appropriate commands: make uses cmd.exe when no sh.exe is on PATH.
ifneq (,$(findstring cmd,$(SHELL)))
    MKDIR        = if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
    CLEAN        = if exist "$(OBJ_DIR)" rmdir /s /q "$(OBJ_DIR)"
    CLEAN_TARGET = if exist "$(TARGET)" del /q "$(TARGET)"
else
    MKDIR        = mkdir -p $(OBJ_DIR)
    CLEAN        = rm -rf $(OBJ_DIR)
    CLEAN_TARGET = rm -f $(TARGET)
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(MKDIR)

run: $(TARGET)
	./$(TARGET)

clean:
	@$(CLEAN)
	@$(CLEAN_TARGET)

-include $(DEPS)

.PHONY: all run clean
