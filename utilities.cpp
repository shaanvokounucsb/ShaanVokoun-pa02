#include "utilities.h"
#include <algorithm>
#include <cctype>

using namespace std;

string trimAndLowercase(const string& str) {
    if (str.empty()) return "";
    
    size_t first = str.find_first_not_of(" \t\r\n");
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    
    string trimmed = str.substr(first, (last - first + 1));
    
    for (char &c : trimmed) {
        c = tolower((unsigned char)c);
    }
    
    return trimmed;
}

string cleanPrefixOnly(const string& str) {
    if (str.empty()) return "";
    
    string cleaned = str;
    while (!cleaned.empty() && (cleaned[cleaned.size() - 1] == '\r' || cleaned[cleaned.size() - 1] == '\n')) {
        cleaned.erase(cleaned.size() - 1);
    }
    
    for (char &c : cleaned) {
        c = tolower((unsigned char)c);
    }
    
    return cleaned;
}
