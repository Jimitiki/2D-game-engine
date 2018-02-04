C = g++ -std=c++11
CFLAGS = -Wall
LFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

TARGET = JAM

OBJS = Animation.o AssetManager.o Cursor.o Entity.o FPSDisplay.o GameCore.o Game.o HUDElement.o HUDManager.o InputManager.o main.o Menu.o MenuElement.o Sprite.o Timer.o World.o

all : game

game : $(OBJS)
	$(C) $(CFLAGS) -o $(TARGET) $^ $(LFLAGS)
	rm ../src/*.gch

Animation.o : ../src/Animation.hpp ../src/Animation.cpp
	$(C) $(CFLAGS) -c -g $^ $(LFLAGS)

AssetManager.o : ../src/AssetManager.hpp ../src/AssetManager.cpp
	$(C) $(CFLAGS) -c -g $^ $(LFLAGS)

Cursor.o : ../src/Cursor.hpp ../src/Cursor.cpp
	$(C) $(CFLAGS) -c -g $^ $(LFLAGS)

Entity.o : ../src/Entity.hpp ../src/Entity.cpp
	$(C) $(CFLAGS) -c -g $^ $(LFLAGS)

FPSDisplay.o : ../src/FPSDisplay.hpp ../src/FPSDisplay.cpp
	$(C) $(CFLAGS) -c -g $^ $(LFLAGS)

GameCore.o : ../src/GameCore.hpp ../src/GameCore.cpp ../src/FPSDisplay.cpp
	$(C) $(CFLAGS) -c -g $^ $(LFLAGS)

Game.o : ../src/Game.hpp ../src/Game.cpp
	$(C) $(CFLAGS) -c -g $^ $(LFLAGS)

HUDElement.o : ../src/HUDElement.hpp ../src/HUDElement.cpp
	$(C) $(CFLAGS) -c -g $^ $(LFLAGS)

HUDManager.o : ../src/HUDManager.hpp ../src/HUDManager.cpp
	$(C) $(CFLAGS) -c -g $^ $(LFLAGS)

InputManager.o : ../src/InputManager.hpp ../src/InputManager.cpp
	$(C) $(CFLAGS) -c -g $^ $(LFLAGS)

main.o : ../src/main.cpp ../src/InputManager.cpp
	$(C) $(CFLAGS) -c -g $^ $(LFLAGS)

Menu.o : ../src/Menu.hpp ../src/Menu.cpp ../src/InputManager.cpp
	$(C) $(CFLAGS) -c -g $^ $(LFLAGS)

MenuElement.o : ../src/MenuElement.hpp ../src/MenuElement.cpp
	$(C) $(CFLAGS) -c -g $^ $(LFLAGS)

Sprite.o : ../src/Sprite.hpp ../src/Sprite.cpp
	$(C) $(CFLAGS) -c -g $^ $(LFLAGS)

Timer.o : ../src/Timer.hpp ../src/Timer.cpp
	$(C) $(CFLAGS) -c -g $^ $(LFLAGS)

World.o : ../src/World.hpp ../src/World.cpp
	$(C) $(CFLAGS) -c -g $^ $(LFLAGS)

clean :
	rm ./*.o
	rm ../src/*.gch

