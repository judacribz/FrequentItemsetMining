CC = g++
CFLAGS = -g -std=c++11 -Wall -Iinclude

MK_DIR = mkdir
RM_DIR = rmdir
TARGET = main
BUILD_DIR = build/
SRC_DIR = src/
ALG_DIR = $(SRC_DIR)algorithms/
SOURCES = $(SRC_DIR)*.cpp $(ALG_DIR)*.cpp
.PHONY: clean help


run: $(BUILD_DIR) $(TARGET).exe
	$(BUILD_DIR)$(TARGET).exe

$(TARGET).exe: $(SOURCES)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)$(TARGET).exe $(SOURCES)

$(BUILD_DIR):
	if [ ! -d "$(BUILD_DIR)"];then	\
		$(MK_DIR) $(BUILD_DIR)		\
    fi
	
clean:
	$(RM) $(BUILD_DIR)$(TARGET).exe