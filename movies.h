#ifndef MOVIES_H
#define MOVIES_H

#include <string>
#include <vector>

using namespace std;
struct Movie {
    string title;
    double rating;
};

struct MovieTracker{
	string prefix;
	string title;
	double rating;
	bool found;
};

class MovieManager {
private:
    vector<Movie> movieRecords;

    string trimAndLowercase(const string& str);

public:

    bool loadFromCSV(const string& filename);

    void sortMoviesAlphabetically();
    void printMovies() const;
    void processPrefixeQueries(const string& prefixFilename);
};

#endif
