#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "movies.h"
#include "utilities.h"

using namespace std;

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }

    MovieManager manager;
    string line, movieName;
    double movieRating;
    
    while (getline(movieFile, line)) {
        if (line.empty()) continue;
        if (parseLine(line, movieName, movieRating)) {
            manager.insertMovie(movieName, movieRating);
        }
    }
    movieFile.close();

    if (argc < 3){
        manager.printAllAlphabetically();
        return 0;
    }

    ifstream prefixFile (argv[2]);
    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            if (line[line.size() - 1] == '\r') {
                line.erase(line.size() - 1);
            }
            if (!line.empty()) {
                prefixes.push_back(line);
            }
        }
    }
    prefixFile.close();

    manager.processPrefixQueries(prefixes);
    return 0;
}

bool parseLine(string &line, string &movieName, double &movieRating) {
    size_t commaIndex = line.find_last_of(",");
    if (commaIndex == string::npos) return false;

    movieName = line.substr(0, commaIndex);
    string ratingStr = line.substr(commaIndex + 1);

    if (!movieName.empty() && movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }


    movieName = trimAndLowercase(movieName);

    size_t firstDigit = ratingStr.find_first_not_of(" \t\r\n");
    if (firstDigit != string::npos) {
        char ch = ratingStr[firstDigit];
        if ((ch >= '0' && ch <= '9') || ch == '.') {
            movieRating = stod(ratingStr.substr(firstDigit));
            return true;
        }
    }
    return false;
}
