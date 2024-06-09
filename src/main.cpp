
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;

// Define state structure for DFA
struct State {
    bool isFinal;
    unordered_map<char, State*> transitions;
};

class SpellChecker {
private:
    State* initialState;
    unordered_set<string> dictionary;

    // Create a new state for the DFA
    State* createState(bool isFinal) {
        State* newState = new State();
        newState->isFinal = isFinal;
        return newState;
    }

    // Add a word to the DFA dictionary
    void addWord(const string& word) {
        State* currentState = initialState;
        for (char c : word) {
            if (currentState->transitions.find(c) == currentState->transitions.end()) {
                currentState->transitions[c] = createState(false);
            }
            currentState = currentState->transitions[c];
        }
        currentState->isFinal = true;
    }

    // Load dictionary from file and build DFA
    void loadDictionary(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening dictionary file" << endl;
            return;
        }
        string word;
        while (getline(file, word)) {
            dictionary.insert(word);
            addWord(word);
        }
        file.close();
    }
    
    

    // Compute Levenshtein distance between two words
    int levenshteinDistance(const string& word1, const string& word2) {
        int m = word1.size();
        int n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; ++i) {
            dp[i][0] = i;
        }

        for (int j = 1; j <= n; ++j) {
            dp[0][j] = j;
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] });
                }
            }
        }

        return dp[m][n];
    }

public:
    // Constructor: Load dictionary from file
    SpellChecker(const string& dictionaryFile) {
        initialState = createState(false);
        loadDictionary(dictionaryFile);
    }

    // Check if a word is in the dictionary
    bool checkWord(const string& word) {
        State* currentState = initialState;
        for (char c : word) {
            if (currentState->transitions.find(c) == currentState->transitions.end()) {
                return false; // Not in dictionary
            }
            currentState = currentState->transitions[c];
        }
        return currentState->isFinal; // Is a complete word in dictionary
    }

    // Suggest corrections for misspelled word
    void suggestCorrections(const string& word) {
        cout << "Suggestions for \"" << word << "\":" << endl;
        vector<pair<string, int>> suggestions;

        for (const string& w : dictionary) {
            if (w.substr(0, 1) == word.substr(0, 1)) {
                int distance = levenshteinDistance(word, w);
                suggestions.push_back(make_pair(w, distance));
            }
        }

        // Sort suggestions based on distance
        sort(suggestions.begin(), suggestions.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second < b.second;
        });

        // Print suggestions
        for (const auto& suggestion : suggestions) {
            cout << "- " << suggestion.first << " (Distance: " << suggestion.second << ")" << endl;
        }
    }

    // Add a new word to the dictionary
    void addNewWord(const string& word) {
        if (!dictionary.count(word)) {
            dictionary.insert(word);
            addWord(word);
            cout << "Word \"" << word << "\" added to dictionary." << endl;
        } else {
            cout << "Word \"" << word << "\" already exists in dictionary." << endl;
        }
    }

    // Remove a word from the dictionary
    void removeWord(const string& word) {
        if (dictionary.erase(word)) {
            // Rebuild DFA after removal
            initialState = createState(false);
            for (const string& w : dictionary) {
                addWord(w);
            }
            cout << "Word \"" << word << "\" removed from dictionary." << endl;
        } else {
            cout << "Word \"" << word << "\" not found in dictionary." << endl;
        }
    }

    // Display all words in the dictionary
    void displayDictionary() {
        cout << "Dictionary:" << endl;
        for (const string& word : dictionary) {
            cout << "- " << word << endl;
        }
    }

    // Save dictionary to file
    void saveDictionary(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file to save dictionary." << endl;
            return;
        }
        for (const string& word : dictionary) {
            file << word << endl;
        }
        file.close();
        cout << "Dictionary saved to file \"" << filename << "\"." << endl;
    }

    // Batch spelling check for a file
    void batchSpellingCheck(const string& inputFile, const string& outputFile) {
        ifstream inFile(inputFile);
        if (!inFile.is_open()) {
            cerr << "Error opening input file for batch spelling check." << endl;
            return;
        }
        ofstream outFile(outputFile);
        if (!outFile.is_open()) {
            cerr << "Error opening output file for batch spelling check." << endl;
            inFile.close();
            return;
        }
        string word;
        while (inFile >> word) {
            if (checkWord(word)) {
                outFile << word << " - Correct" << endl;
            } else {
                outFile << word << " - Incorrect" << endl;
            }
        }
        inFile.close();
        outFile.close();
        cout << "Batch spelling check completed. Results saved to file \"" << outputFile << "\"." << endl;
    }
};

// Simple console-based GUI for user interaction
void showMenu() {
    cout << "=======================" << endl;
    cout << "1. Check spelling" << endl;
    cout << "2. Add new word" << endl;
    cout << "3. Remove word" << endl;
    cout << "4. Display dictionary" << endl;
    cout << "5. Save dictionary to file" << endl;
    cout << "6. Batch spelling check" << endl;
    cout << "7. Exit" << endl;
    cout << "=======================" << endl;
}

// Validate user input for menu choice
int getChoice() {
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    if (cin.fail() || choice < 1 || choice > 7) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1; // Invalid choice
    }
    return choice;
}

int main() {
    // Initialize spell checker with dictionary
    SpellChecker spellChecker("./dictionary/dictionary.txt");

    int choice;
    string word;

    do {
        system("clear"); // Clear screen
        showMenu();
        choice = getChoice();

        switch (choice) {
            case 1:
                cout << "Enter word to spell check: ";
                cin >> word;
                if (spellChecker.checkWord(word)) {
                    cout << "Spelling is correct!" << endl;
                } else {
                    cout << "Spelling is incorrect!" << endl;
                    spellChecker.suggestCorrections(word);
                }
                break;
            case 2:
                cout << "Enter new word to add: ";
                cin >> word;
                spellChecker.addNewWord(word);
                break;
            case 3:
                cout << "Enter word to remove: ";
                cin >> word;
                spellChecker.removeWord(word);
                break;
            case 4:
                spellChecker.displayDictionary();
                break;
            case 5:
                spellChecker.saveDictionary("dictionary.txt");
                break;
            case 6:
                cout << "Enter input file name for batch spelling check: ";
                cin >> word;
                word = "batch_input/" + word;
                spellChecker.batchSpellingCheck(word, "batch_results/batch_results.txt");
                break;
            case 7:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        if (choice != 7) {
            cout << "Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get(); // Wait for Enter key
        }

    } while (choice != 7);

    return 0;
}


