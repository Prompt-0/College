#include <iostream>
#include <string>
using namespace std;

int bruteForceMatch(const string& text, const string& pattern, int& comps) {
    int n = text.size();
    int m = pattern.size();

    if (m == 0) return 0;

    for (int i = 0; i <= n - m; ++i) {

        int j = 0;
        while (j < m && (++comps && text[i + j] == pattern[j])) {
            j++;
        }

        if (j == m) {
            return i;
        }
    }

    return -1;
}

int main() {
    string text, pattern;

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the pattern to search: ";
    getline(cin, pattern);

    int comps = 0;
    int index = bruteForceMatch(text, pattern, comps);

    if (index != -1) {
        cout << "Pattern found at index: " << index << endl;
    } else {
        cout << "Pattern not found." << endl;
    }

    cout << "Total comparisons: " << comps << endl;

    return 0;
}

