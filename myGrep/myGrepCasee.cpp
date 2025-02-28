#include <iostream> //cout cin cerr
#include <fstream> // files management
#include <string> // string manipulation
#include <algorithm>  // transform
#include <cctype>     // tolower
#include <limits>     // numeric_limits
#include <vector>     // line storage
using namespace std;

// check if a file is given
bool fileGiven(int argc) {
    return argc == 4;
}

// convert a string to lowercase
string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// increment 1
void interactiveStringSearch() {
    string largeString, searchString;

    cout << "Give a string from which to search for: ";
    getline(cin, largeString);

    cout << "Give search string: ";
    getline(cin, searchString);

    size_t found = largeString.find(searchString);

    if (found != string::npos) {
        cout << "\"" << searchString << "\" found in \"" << largeString << "\" in position " << found+1  << endl;
    } else {
        cout << "\"" << searchString << "\" NOT found in \"" << largeString << "\"" << endl;
    }
}
// increment 2 & 3, when using a file
void searchWord(const string& word, istream& input, bool showLineNumbers, bool countOccurrences) {
    string line;
    int lineNumber = 0;
    int occurrences = 0;
    string lowerWord = toLower(word);

    while (getline(input, line)) {
        lineNumber++;
        string lowerLine = toLower(line);
        if (lowerLine.find(lowerWord) != string::npos) {
            if (showLineNumbers) {
                cout << lineNumber << ": ";
            }
            cout << line << endl;
            occurrences++;
        }
    }

    if (countOccurrences) {
        cout << "\nTotal occurrences: " << occurrences << endl;
    }
}

// increment 3, when using manual input
void handleManualInput(const string& word, bool showLineNumbers, bool countOccurrences) {
    cout << "Enter text (Ctrl+D to end):" << endl;

    string line;
    int lineNumber = 0;
    int occurrences = 0;
    string lowerWord = toLower(word);
    vector<string> matchedLines; 

    while (getline(cin, line)) {  
        lineNumber++;
        string lowerLine = toLower(line);
        if (lowerLine.find(lowerWord) != string::npos) {  
            string output = (showLineNumbers ? to_string(lineNumber) + ": " : "") + line;
            matchedLines.push_back(output);
            occurrences++;
        }
    }

    for (const string& matchedLine : matchedLines) {
        cout << matchedLine << endl;
    }

    if (countOccurrences) {
        cout << "\nTotal occurrences: " << occurrences << endl;
    }
}

// usage of switch-case to handle different usages
int main(int argc, char* argv[]) {
    switch (argc) {
        case 1: { // when run with no arguments
            interactiveStringSearch();
            break;
        }

        case 3: { // manual input
            string options = argv[1];
            string word = argv[2];
            bool showLineNumbers = options.find('l') != string::npos;
            bool countOccurrences = options.find('o') != string::npos;

            handleManualInput(word, showLineNumbers, countOccurrences);
            break;
        }

        case 4: { // file input
            string options = argv[1];
            string word = argv[2];
            bool showLineNumbers = options != "-o" && options.find('l') != string::npos;
            bool countOccurrences = options != "-o" && options.find('o') != string::npos;


            ifstream file(argv[3]);
            if (!file.is_open()) {
                cerr << "Could not open the file: " << argv[3] << endl;
                return 1;
            }
            searchWord(word, file, showLineNumbers, countOccurrences);
            file.close();
            break;
        }

        default: { // incorrect usage
            cerr << "Usage: " << argv[0] << " (-options(use -o for no options)) [word] [optional: filename]" << endl;
            return 1;
        }
    }

    return 0;
}
