EXE = gameboy
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99 -I$(INCLUDE_DIR) -MMD -MP
LDFLAGS =
LIBS = 
LD = $(CC)

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
DEPS := $(OBJECTS:.o=.d)

.PHONY:	default all clean

default: all

all: $(BUILD_DIR)/$(EXE)

$(BUILD_DIR)/$(EXE): $(OBJECTS)	| $(BUILD_DIR)
	$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

$(BUILD_DIR):
	mkdir -p $@
	
.PHONY: run

run: all
	./$(BUILD_DIR)/$(EXE)

clean:
	rm -rf $(BUILD_DIR)