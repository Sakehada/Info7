EXE = test
CPP = g++
SDL_INC = -I./../../src/include
SDL_LIB = -L./ -lSDL2 -lSDL2_image -lSDL2_ttf
CFLAGS = -O3 -Wall $(SDL_INC)
LIBS = $(SDL_LIB)

ALL = $(EXE)

./../../obj/%.o: ./../../src/%.cpp ./../../src/%.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(EXE): ./../../obj/window.o ./../../obj/world.o main.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	-$(RM) ./../../obj/*.o $(EXE)
