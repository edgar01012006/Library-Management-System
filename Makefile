# Force use of Windows CMD to avoid Bash path/command conflicts
ifeq ($(OS),Windows_NT)
    SHELL := cmd.exe
endif

# =========================
# Compiler and Flags
# =========================
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# =========================
# Source / Object files
# =========================
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

# =========================
# Target executable
# =========================
TARGET = libratrack

# =========================
# OS-specific settings
# =========================
ifeq ($(OS),Windows_NT)
    TARGET := $(TARGET).exe
    RM = del /Q /F
    # Correctly handles the backslashes Windows 'del' requires
    FIXPATH = $(subst /,\,$1)
else
    RM = rm -f
    FIXPATH = $1
endif

# =========================
# Rules
# =========================
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo Cleaning project...
	-$(RM) $(call FIXPATH,$(OBJ)) $(call FIXPATH,$(TARGET))

.PHONY: all clean