CC	     := g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror
LDFLAGS  := -L/usr/lib -lstdc++
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET   := ray
INCLUDE  := -Iinclude/
RM 	     := rm -rf

SRC_FILES = ./src/main.cpp
O_FILES = $(SRC_FILES:%.cc=%.o)

all:
	$(CC) $(INCLUDE) $(LDFLAGS) $(SRC_FILES) -o ${TARGET}

clean:
	$(RM) $(TARGET)
