#include "movies.h"
#include "utilities.h"
#include <iostream>
#include <iomanip>

using namespace std;

void MovieManager::insertMovie(const string& name, double rating) {
    Movie movie;
    movie.title = trimAndLowercase(name);
    movie.rating = rating;
    movieRecords.push_back(movie);
}

void MovieManager::printAllAlphabetically() {
    if (movieRecords.empty()) return;

    size_t n = movieRecords.size();
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (movieRecords[j].title > movieRecords[j + 1].title) {
                Movie temp = movieRecords[j];
                movieRecords[j] = movieRecords[j + 1];
                movieRecords[j + 1] = temp;
            }
        }
    }

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
            
            MovieTracker tracker;
            tracker.prefix = prefix;
            tracker.found = false;
            summaryList.push_back(tracker);
            continue;
        }

        size_t n = matches.size();
        for (size_t i = 0; i < n - 1; ++i) {
            for (size_t j = 0; j < n - i - 1; ++j) {
                bool swapRequired = false;
                if (matches[j].rating < matches[j + 1].rating) {
                    swapRequired = true;
                } else if (matches[j].rating == matches[j + 1].rating) {
                    if (matches[j].title > matches[j + 1].title) {
                        swapRequired = true;
                    }
                }

                if (swapRequired) {
                    Movie temp = matches[j];
                    matches[j] = matches[j + 1];
                    matches[j + 1] = temp;
                }
            }
        }

        for (const auto& movie : matches) {
            cout << movie.title << ", " << fixed << setprecision(1) << movie.rating << endl;
        }
        cout << endl;

        MovieTracker tracker;
        tracker.prefix = prefix;
        tracker.title = matches[0].title;
        tracker.rating = matches[0].rating;
        tracker.found = true;
        summaryList.push_back(tracker);
    }

    for (const auto& tracker : summaryList) {
        if (tracker.found) {
            cout << "Best movie with prefix " << tracker.prefix << " is: " 
                 << tracker.title << " with rating " << fixed << setprecision(1) << tracker.rating << endl;
        }
    }
}
