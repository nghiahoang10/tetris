main: src/game.cpp src/main.cpp
		g++	-o game src/game.cpp src/main.cpp `pkg-config --cflags --libs sdl2 SDL2_ttf`