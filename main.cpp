// Winter'24
// Instructor: Diba Mirza
// Student name: Shaan Vokoun
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

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
  
    // Create an object of a STL data-structure to store all the movies

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
    }

    movieFile.close();

    if (argc == 2){
            //print all the movies in ascending alphabetical order of movie names
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
            prefixes.push_back(line);
        }
    }

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    cout << "No movies found with prefix "<<"<replace with prefix>" << endl;

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    cout << "Best movie with prefix " << "<replace with prefix>" << " is: " << "replace with movie name" << " with rating " << std::fixed << std::setprecision(1) << "replace with movie rating" << endl;

    return 0;
}
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
bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}
