CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

runMovies: main.o movies.o
	$(CXX) $(CXXFLAGS) main.o movies.o -o runMovies

main.o: main.cpp movies.h
	$(CXX) $(CXXFLAGS) -c main.cpp

movies.o: movies.cpp movies.h
	$(CXX) $(CXXFLAGS) -c movies.cpp

clean:
	rm -f *.o runMovies
