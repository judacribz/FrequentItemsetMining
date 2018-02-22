CC = g++

CFLAGS = -g -std=c++11 -Wall

TARGET = main
SOURCES = *.cpp
.PHONY: clean help

run: $(OBJECTS)
	./$(TARGET).exe

$(TARGET).exe: $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET).exe $(SOURCES)

clean:
	$(RM) $(TARGET).exe