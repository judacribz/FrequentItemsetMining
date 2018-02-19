CC = g++

CFLAGS = -g -std=c++11 -Wall

TARGET = main

run: $(TARGET).exe; ./$(TARGET).exe

$(TARGET).exe: $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET).exe $(TARGET).cpp

clean:
	$(RM) $(TARGET)