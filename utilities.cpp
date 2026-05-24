#include "utilities.h"

using namespace std;

string trimAndLowercase(const string& str) {
    if (str.empty()) return "";
    size_t first = str.find_first_not_of(" \t\r\n");
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    string trimmed = str.substr(first, (last - first + 1));
    
    string result = "";
    bool lastWasSpace = false;

    for (size_t i = 0; i < trimmed.length(); ++i) {
        char ch = trimmed[i];

        if (ch == ' ' || ch == '\t'){
            if (!lastWasSpace){
                result += ' ';
                lastWasSpace = true;
            }
            else {
                result += ch;
                lastWasSpace = false;
            }
        }
        
    }
    return result;
}

string cleanPrefixOnly(const string& str) {
    if (str.empty()) return "";
    
    string cleaned = str;
    
    while (!cleaned.empty() && (cleaned[cleaned.size() - 1] == '\r' || cleaned[cleaned.size() - 1] == '\n')) {
        cleaned.erase(cleaned.size() - 1);
    }
    
    for (size_t i = 0; i < cleaned.length(); ++i) {
        if (cleaned[i] >= 'A' && cleaned[i] <= 'Z') {
            cleaned[i] = cleaned[i] + 32;
        }
    }
    
    return cleaned;
}
