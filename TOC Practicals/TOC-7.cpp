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

    return false; // invalid character
}

bool read2(const string& str, int i, stack<char>& s) {
    if (i >= str.size()) {
        return s.size() == 0;
    }

    if (str[i] == 'b') {
        if (s.empty()) return false;
        char k = s.top();
        s.pop();
        if (k != 'a') return false;
        return read2(str, i + 1, s);
    }

    return false; // seeing 'a' after b's is invalid
}

int main() {
    string input;
    cout << "Enter the string: ";
    getline(cin, input);
    stack<char> s;
    bool result = read1(input, 0, s);
    cout << (result ? "Accepted" : "Rejected") << endl;
    return 0;
}

