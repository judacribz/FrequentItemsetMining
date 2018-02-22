CC = g++

CFLAGS = -g -std=c++11 -Wall

TARGET = main
SOURCES = main.cpp util.cpp pcy.cpp a_priori.cpp
.PHONY: clean help

run: $(TARGET).exe
	./$(TARGET).exe

$(TARGET).exe: $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET).exe $(SOURCES)

clean:
	$(RM) $(TARGET).exe