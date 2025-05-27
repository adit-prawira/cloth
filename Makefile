include .env

CFLAGS = -std=c++17

TARGET = a.out
$(TARGET): *.cpp
	g++ $(CFLAGS) -o $(TARGET) *.cpp

.PHONY: test clean

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
