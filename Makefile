CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

runMovies: main.o movies.o utilities.o
	$(CXX) $(CXXFLAGS) main.o movies.o utilities.o -o runMovies

main.o: main.cpp movies.h utilities.h
	$(CXX) $(CXXFLAGS) -c main.cpp

movies.o: movies.cpp movies.h utilities.h
	$(CXX) $(CXXFLAGS) -c movies.cpp

utilities.o: utilities.cpp utilities.h
	$(CXX) $(CXXFLAGS) -c utilities.cpp

clean:
	rm -f *.o runMovies
