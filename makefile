CC = g++
CFLAGS = -g -std=c++11 -Wall -Iinclude

MKDIR = mkdir
TARGET = main
BUILD_DIR = build/
SOURCES = src/*.cpp
.PHONY: clean help


run: $(BUILD_DIR) $(TARGET).exe
	$(BUILD_DIR)$(TARGET).exe

$(TARGET).exe: $(SOURCES)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)$(TARGET).exe $(SOURCES)

$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)


clean:
	$(RM) $(BUILD_DIR)$(TARGET).exe