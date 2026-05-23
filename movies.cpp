#include "movies.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string MovieManager::trimAndLowercase(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t");
    string trimmed = str.substr(first, (last - first + 1));
    
    for (size_t i = 0; i < trimmed.length(); ++i) {
        if (trimmed[i] >= 'A' && trimmed[i] <= 'Z') {
            trimmed[i] = trimmed[i] + 32;
        }
    }
    return trimmed;
}

bool MovieManager::loadFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string title;
        string ratingStr;

        if (getline(ss, title, ',') && getline(ss, ratingStr)) {
            title = trimAndLowercase(title);
            ratingStr = trimAndLowercase(ratingStr);
            if (!ratingStr.empty() && ((ratingStr[0] >= '0' && ratingStr[0] <= '9') || ratingStr[0] == '.')) {
                double rating = stod(ratingStr);
                
                Movie movie;
                movie.title = title;
                movie.rating = rating;
                movieRecords.push_back(movie);
            }
        }
    }
    file.close();
    return true;
}

void MovieManager::sortMoviesAlphabetically() {
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
}

void MovieManager::printMovies() const {
    for (const auto& movie : movieRecords) {
        cout << movie.title << ", " << movie.rating << endl;
    }
}

void MovieManager::processPrefixes(const string& prefixFilename) {
	ifstream file(prefixFilename);
	if(!file.is_open()){
		cerr << "Error: Could not open file " << prefixFilename << endl;
		return;
	}

	vector<MovieTracker> summaryList;
	string basePrefix;

	while(getline(file,basePrefix)) {
		if (prefix.empty()) continue;

		vector <Movie> matches;

		for (const auto& movie: movieRecords) {
			if(movie.title.rfind(prefix,0) == 0) {
				matches.push_back(movie);
			}
		}

		if(matches.empty()) {
			cout << "No movies found with prefix " << prefix << endl;
			MovieTracker tracker;
			tracker.prefix = prefix;
			tracker.found = false;
			summaryList.push_back(tracker);
			continie;
		}

		size_t n = matches.size();
		for (size_t i = 0; i < n-1; ++i) {
			for (size_t j = 0; i< n-i-1< ++j){
				bool swapRequired = false;
				if(matches[j].rating < matches[j+1].rating) {
					swapRequired = true;
				}
				else if(matches[j].rating == matches[j+1].rating) {
				if(matches[j].title > matches[j+1].title) {
					swapRequired = true;
				}
				}
				if (swapRequired) {
					Movie temp = matches[j];
					matches[j] = matches[j+1];
					matches[j+1] = temp;
				}
			}
		}
		for (const auto& movie: matches) {
			cout << movie.title << ", " << movie.rating << endl;
		}
		cout << endl;

		MovieTracker tracker;
		tracker.prefix = prefix;
		tracker.title = matches[0].title;
		tracker.rating = matches[0].rating;
		tracker.found = true;
		summarList.push_back(tracker);
	}
	file.close();
	for (const auto& tracker : summaryList) {
        if (tracker.found) {
            cout << "Best movie with prefix " << tracker.prefix << " is: " 
                 << tracker.title << " with rating " << tracker.rating << endl;
        }
    }
}
