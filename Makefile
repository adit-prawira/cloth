include .env

CFLAGS = -std=c++17 -I. -I$(SFML_PATH)/include
LDFLAGS = -L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system

TARGET = a.out
$(TARGET): *.cpp
	g++ $(CFLAGS) -o $(TARGET) *.cpp $(LDFLAGS)

.PHONY: test clean

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
