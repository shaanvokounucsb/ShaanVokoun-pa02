CXX_FLAGS = -std=c++20 -Ofast

all: runMovies

runMovies: movies.o main.cpp
	g++ $(CXX_FLAGS) -o runMovies movies.o main.cpp

movies.o: movies.h movies.cpp 
	g++ -c $(CXX_FLAGS) movies.cpp

clean:
	rm -f *.o
	rm -f runMovies
