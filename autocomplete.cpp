#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
};

struct TrieNode* getNode() {
    struct TrieNode* pNode = new TrieNode;
    pNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pNode->children[i] = nullptr;
    }
    return pNode;
}

void insert(struct TrieNode* root, string key) {
    struct TrieNode* pCrawl = root;
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index]) {
            pCrawl->children[index] = getNode();
        }
        pCrawl = pCrawl->children[index];
    }
    pCrawl->isEndOfWord = true;
}

void findSuggestions(struct TrieNode* node, string prefixSoFar, vector<string>& suggestions, string prefix) {
    if (node->isEndOfWord) {
        suggestions.push_back(prefix + prefixSoFar);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            findSuggestions(node->children[i], prefixSoFar + char('a' + i), suggestions, prefix);
        }
    }
}

vector<string> suggestWords(struct TrieNode* root, string prefix) {
    vector<string> suggestions;
    struct TrieNode* pCrawl = root;
    for (int i = 0; i < prefix.length(); i++) {
        int index = prefix[i] - 'a';
        if (!pCrawl->children[index]) {
            return suggestions;
        }
        pCrawl = pCrawl->children[index];
    }

    findSuggestions(pCrawl, "", suggestions, prefix);

    return suggestions;
}

int main() {
    struct TrieNode* root = getNode();
    insert(root, "apple");
    insert(root, "banana");
    insert(root, "cherry");
    insert(root, "car");
    insert(root, "human");
    insert(root, "work");
    insert(root, "name");

    string input;
    do {
        cout << "Enter a prefix or enter 'exit' to quit: ";
        cin >> input;

        if (input != "exit") {
            vector<string> suggestions = suggestWords(root, input);

            cout << "Suggestions for words starting with '" << input << "':" << endl;
            for (const string& word : suggestions) {
                cout << word << endl;
            }
        }
    } while (input != "exit");

    return 0;
}