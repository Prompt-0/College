#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// Using 26 characters for the English alphabet ('a'-'z')
const int ALPHABET_SIZE = 26;


struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];

    TrieNode() {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
    }

    ~TrieNode() {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (children[i] != nullptr) {
                delete children[i];
            }
        }
    }
};

class SuffixTrie {
private:
    TrieNode* root;
    string text;

    void buildTrie() {
        // "for i = |T|-1 downto 0"
        for (int i = text.length() - 1; i >= 0; i--) {
            // "node = root; j = i;"
            TrieNode* node = root;
            int j = i;

            // "while Tj-edge from node exists"
            while (j < text.length()) {
                char ch = text[j];
                int index = ch - 'a'; // Map 'a'-'z' to 0-25

                if (index < 0 || index >= ALPHABET_SIZE) {
                     throw out_of_range("Text contains non-lowercase alphabet characters.");
                }

                if (node->children[index] != nullptr) {
                    // "node = the node accessible through Tj-edge from node; j++;"
                    node = node->children[index];
                    j++;
                } else {
                    break;
                }
            }

            // "for k = j to |T|-1"
            for (int k = j; k < text.length(); k++) {
                char ch = text[k];
                int index = ch - 'a';

                if (index < 0 || index >= ALPHABET_SIZE) {
                     throw out_of_range("Text contains non-lowercase alphabet characters.");
                }

                // "create newNode;"
                TrieNode* newNode = new TrieNode();
                // "create edge(node,newNode,Tk);"
                node->children[index] = newNode;
                // "node = newNode;"
                node = newNode;
            }
        }
    }

public:
    SuffixTrie(const string& t) : text(t) {
        if (t.empty()) {
            throw invalid_argument("Text cannot be empty.");
        }
        root = new TrieNode();
        buildTrie();
    }

    ~SuffixTrie() {
        delete root;
    }

    bool searchPattern(const string& pattern) {
        TrieNode* node = root;
        for (char ch : pattern) {
            int index = ch - 'a';

            if (index < 0 || index >= ALPHABET_SIZE) {
                // Pattern has invalid characters
                return false;
            }

            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        return true;
    }
};


int main() {

    string text = "banana";

    try {
        SuffixTrie trie(text);
        cout << "Suffix Trie built for text: '" << text << "'\n" << endl;

        // --- Test Cases ---
        string pattern1 = "ana";
        cout << "Searching for '" << pattern1 << "': "
                  << (trie.searchPattern(pattern1) ? "Found" : "Not Found")
                  << endl; // Expected: Found

        string pattern2 = "nana";
        cout << "Searching for '" << pattern2 << "': "
                  << (trie.searchPattern(pattern2) ? "Found" : "Not Found")
                  << endl; // Expected: Found

        string pattern3 = "ban";
        cout << "Searching for '" << pattern3 << "': "
                  << (trie.searchPattern(pattern3) ? "Found" : "Not Found")
                  << endl; // Expected: Found

        string pattern4 = "band";
        cout << "Searching for '" << pattern4 << "': "
                  << (trie.searchPattern(pattern4) ? "Found" : "Not Found")
                  << endl; // Expected: Not Found

        string pattern5 = "a";
        cout << "Searching for '" << pattern5 << "': "
                  << (trie.searchPattern(pattern5) ? "Found" : "Not Found")
                  << endl; // Expected: Found

        string pattern6 = "apple";
        cout << "Searching for '" << pattern6 << "': "
                  << (trie.searchPattern(pattern6) ? "Found" : "Not Found")
                  << endl; // Expected: Not Found

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
