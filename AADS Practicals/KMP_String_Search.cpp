#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> computeFailFunction(const string& pattern, int& comps) {
    int m = pattern.size();
    vector<int> fail(m, 0);

    int j = 0;
    for (int i = 1; i < m; ++i) {

        while (j > 0 && (++comps && pattern[i] != pattern[j])) {
            j = fail[j - 1];
        }

        if (++comps && pattern[i] == pattern[j]) {
            j++;
        }

        fail[i] = j;
    }

    return fail;
}

int KMPmatch(const string& text, const string& pattern, int& comps) {
    int n = text.size();
    int m = pattern.size();

    if (m == 0) return 0;

    int failComps = 0;
    vector<int> fail = computeFailFunction(pattern, failComps);
    comps += failComps;

    int j = 0;
    for (int i = 0; i < n; ++i) {

        while (j > 0 && (++comps && text[i] != pattern[j])) {
            j = fail[j - 1];
        }

        if (++comps && text[i] == pattern[j]) {
            j++;
        }

        if (j == m) {
            return i - m + 1;
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
    int index = KMPmatch(text, pattern, comps);

    if (index != -1) {
        cout << "Pattern found at index: " << index << endl;
    } else {
        cout << "Pattern not found." << endl;
    }

    cout << "Total comparisons: " << comps << endl;

    return 0;
}

