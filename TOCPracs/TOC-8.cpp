#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool state2(const string& str, int i, stack<char> s);

bool state1(const string& str, int i, stack<char> s) {
    if (i == str.size()) {
        return false;  // cannot go to state2 at end
    }

    // Guess transition: switch to state2 WITHOUT consuming input
    if (state2(str, i, s)) return true;

    char c = str[i];
    if (c != 'a' && c != 'b') return false;

    s.push(c);

    return state1(str, i + 1, s);
}

bool state2(const string& str, int i, stack<char> s) {
    if (i == str.size()) {
        return s.empty();
    }

    char c = str[i];
    if (c != 'a' && c != 'b') return false;

    if (s.empty()) return false;
    char top = s.top();
    s.pop();

    if (c != top) return false;

    return state2(str, i + 1, s);
}

int main() {
    string input;
    getline(cin, input);

    stack<char> s;

    bool result = state1(input, 0, s);
    cout << (result ? "Accepted" : "Rejected") << endl;

    return 0;
}

