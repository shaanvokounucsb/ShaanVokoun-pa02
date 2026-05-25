#include "movies.h"
#include "utilities.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

void MovieManager::insertMovie(const string& name, double rating) {
    Movie movie;
    movie.title = trimAndLowercase(name);
    movie.rating = rating;
    movieRecords.push_back(movie);
}
bool CaseComparer(const Movie& a, const Movie& b) {
    string titleA = a.title;
    string titleB = b.title;

    for (size_t k = 0; k < titleA.length(); ++k) {
        if (titleA[k] >= 'A' && titleA[k] <= 'Z') titleA[k] += 32;
    }
    for (size_t k = 0; k < titleB.length(); ++k) {
        if (titleB[k] >= 'A' && titleB[k] <= 'Z') titleB[k] += 32;
    }

    return titleA < titleB;
}

void MovieManager::printAllAlphabetically() {

    sort(movieRecords.begin(), movieRecords.end(), CaseComparer)

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
            // FIX: Generate a lowercase copy of the movie title purely for comparison
            string lowerTitle = movie.title;
            for (size_t i = 0; i < lowerTitle.length(); ++i) {
                if (lowerTitle[i] >= 'A' && lowerTitle[i] <= 'Z') {
                    lowerTitle[i] = lowerTitle[i] + 32;
                }
            }

            if (lowerTitle.rfind(prefix, 0) == 0) {
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
