CXX=g++
CXXFLAGS=-Wall -O3 -g -std=c++0x

all: he2

he2: ground.o background.o person.o dud.o particle.o p_engine.o main.o
	$(CC) $(CFLAGS) -o $@ $^ -lSDL -lSDL_mixer -lGLU -lGL -lstarlia

ground.o: ground.h
background.o: background.h
person.o: person.h
dud.o: dud.h
particle.o: particle.h
p_engine.o: p_engine.h

clean:
	$(RM) *.o

distclean: clean
	$(RM) he2 

