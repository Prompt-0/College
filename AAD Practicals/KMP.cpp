#include <string>
#include <vector>

std::vector<int> computeFailFunction(const std::string& pattern) {
    int m = pattern.size();
    std::vector<int> fail(m, 0);

    int j = 0;      // length of current matched prefix
    for (int i = 1; i < m; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = fail[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        fail[i] = j;
    }

    return fail;
}

int KMPmatch(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();

    if (m == 0) return 0;  // trivial empty pattern case

    std::vector<int> fail = computeFailFunction(pattern);

    int j = 0; // index in pattern
    for (int i = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = fail[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
        }
        if (j == m) {
            return i - m + 1; // match found
        }
    }

    return -1; // no match found
}
