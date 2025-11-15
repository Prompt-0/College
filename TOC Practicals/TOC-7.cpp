#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool read1(const string& str, int i, stack<char>& s);
bool read2(const string& str, int i, stack<char>& s);

bool read1(const string& str, int i, stack<char>& s) {
    if (i >= str.size()) return false;  // reached end too early

    if (str[i] == 'a') {
        s.push('a');
        return read1(str, i + 1, s);
    }

    if (str[i] == 'b') {
        if (s.empty()) return false;
        char k = s.top();
        s.pop();
        if (k != 'a') return false;
        return read2(str, i + 1, s);
    }

    // invalid character
    return false;
}

bool read2(const string& str, int i, stack<char>& s) {
    if (i >= str.size()) {
        // end of string: stack should be empty
        return s.size() == 0;
    }

    if (str[i] == 'b') {
        if (s.empty()) return false;
        char k = s.top();
        s.pop();
        if (k != 'a') return false;
        return read2(str, i + 1, s);
    }

    // if we see 'a' after b’s, invalid
    return false;
}

int main() {
    string input;
    getline(cin, input); // expecting a^n b^n form
    stack<char> s;
    bool result = read1(input, 0, s);
    cout << (result ? "Accepted" : "Rejected") << endl;
    return 0;

    
}
#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool read1(const string& str, int i, stack<char>& s);
bool read2(const string& str, int i, stack<char>& s);

bool read1(const string& str, int i, stack<char>& s) {
    if (i >= str.size()) return false;  // reached end too early

    if (str[i] == 'a') {
        s.push('a');
        return read1(str, i + 1, s);
    }

    if (str[i] == 'b') {
        if (s.empty()) return false;
        char k = s.top();
        s.pop();
        if (k != 'a') return false;
        return read2(str, i + 1, s);
    }

    // invalid character
    return false;
}

bool read2(const string& str, int i, stack<char>& s) {
    if (i >= str.size()) {
        // end of string: stack should be empty
        return s.size() == 0;
    }

    if (str[i] == 'b') {
        if (s.empty()) return false;
        char k = s.top();
        s.pop();
        if (k != 'a') return false;
        return read2(str, i + 1, s);
    }

    // if we see 'a' after b’s, invalid
    return false;
}

int main() {
    string input;
    getline(cin, input); // expecting a^n b^n form
    stack<char> s;
    bool result = read1(input, 0, s);
    cout << (result ? "Accepted" : "Rejected") << endl;
    return 0;

    
}
