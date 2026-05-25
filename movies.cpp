#include "movies.h"
#include "utilities.h"
#include <iostream>
#include <iomanip>
#include <algorithm> 

using namespace std;

void MovieManager::insertMovie(const string& name, double rating) {
    Movie movie;
    movie.title = name;
    movie.rating = rating;
    movieRecords.push_back(movie);
}

bool compareMoviesAlphabetically(const Movie& a, const Movie& b) {
    return a.title < b.title;
}

bool comparePrefixMatches(const Movie& a, const Movie& b) {
    if (a.rating != b.rating) {
        return a.rating > b.rating;
    }
    return a.title < b.title;
}

void MovieManager::printAllAlphabetically() {
    if (movieRecords.empty()) return;

    stable_sort(movieRecords.begin(), movieRecords.end(), compareMoviesAlphabetically);

    for (const auto& movie : movieRecords) {
        cout << movie.title << ", " << fixed << setprecision(1) << movie.rating << endl;
    }
}

void MovieManager::processPrefixQueries(const vector<string>& rawPrefixes) {
    vector<MovieTracker> summaryList;

    for (const auto& rawPrefix : rawPrefixes) {
        string prefix = cleanPrefixOnly(rawPrefix);
        if (prefix.empty()) continue;

        vector<Movie> matches;
        for (const auto& movie : movieRecords) {
            if (movie.title.rfind(prefix, 0) == 0) {
                matches.push_back(movie);
            }
        }

        if (matches.empty()) {
            cout << "No movies found with prefix " << prefix << endl;
            continue; 
        }

        stable_sort(matches.begin(), matches.end(), comparePrefixMatches);

        for (const auto& movie : matches) {
            cout << movie.title << ", " << fixed << setprecision(1) << movie.rating << endl;
        }
        cout << endl;

        MovieTracker tracker;
        tracker.prefix = prefix;
        tracker.title = matches[0].title;
        tracker.rating = matches[0].rating;
        summaryList.push_back(tracker);
    }

    for (const auto& tracker : summaryList) {
        cout << "Best movie with prefix " << tracker.prefix << " is: " 
             << tracker.title << " with rating " << fixed << setprecision(1) << tracker.rating << endl;
    }
}
