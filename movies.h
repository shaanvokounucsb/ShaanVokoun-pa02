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
    void insertMovie(const string& name, double rating);
    void printAllAlphabetically();
    void processPrefixQueries(const vector<string>& rawPrefixes);
};

#endif