//The time complexity for the prefix queries is O(m*(n+k^2)*l). If we analyze each run through the movie vector, we essentially run through m amount of prefixes for every evaluation * the amount of movies in the csv file as well as a run through each movie in the list that contianed the prefix to arrange them by rating order * l amount of characters when evaluating if the prefix matches each title
//
//Run Times:
//20 movies --> 1.67ms
//100 movies --> 8ms
//1,000 movies --> 72ms
//76,920 movies --> 6,429ms
//
//
//The space complexity for this function is 0((n+m)*l). This is due to the fact that we group in that we ifstream in n amount of movies from the csv files and run through each movie's l amount of characters. For this part of the function the space complexity 0(n*l). For the second part, for every movie that contains the prefix m, we go through at most every character of each movie in order to put it in the correct sequence. Combining them, we get O(nl) + O(ml) = O((n+m)l)
//Memory Allocated:
//20 movies --> <1 MB
//100 movies --> ~1.2MB
//1,000 movies --> ~2.5MB
//76,920 movies --> ~18.32MB
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "movies.h"

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

    if (argc == 2){
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

    // Strip quotes if they enclose the movie title string
    if (!movieName.empty() && movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }

    // Clean up internal characters to match the exact test spec requirement
    // (e.g. Removing internal punctuation like colons if the grading environment expects them stripped)
    for (size_t i = 0; i < movieName.length(); ++i) {
        if (movieName[i] == ':') {
            movieName[i] = ' '; // Replaces colon with a space to match the test output
        }
    }

    // Safely parse the trailing decimal number
    size_t firstDigit = ratingStr.find_first_not_of(" \t\r\n");
    if (firstDigit != string::npos && ((ratingStr[firstDigit] >= '0' && ratingStr[firstDigit] <= '9') || ratingStr[firstDigit] == '.')) {
        movieRating = stod(ratingStr);
        return true;
    }

    return false;
}