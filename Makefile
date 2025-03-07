all: game
game: main.cpp
	g++ -g -c -I/home/repository/openGL_test/glm/ main.cpp glad.c -Wall -ldl -lglfw  -I/home/repository/openGL_test
	g++ -g main.o glad.o -I/home/repository/openGL_test/glm -I/home/repository/openGL_test -o main.out -Wall -ldl -lglfw 
clean:
	rm *.o *.out
