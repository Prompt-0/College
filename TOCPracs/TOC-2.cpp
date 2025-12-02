#include <iostream>
#include <string>

using namespace std;

bool state0(const string& w, int i);
bool state1(const string& w, int i);
bool state2(const string& w, int i);
bool state3(const string& w, int i);
bool state4(const string& w, int i);

bool state0(const string& w, int i) {
    cout << " -> S0";
    if (i == w.length()) {
        return false;
    }
    if (w[i] == '0') return state0(w, i + 1);
    else if (w[i] == '1') return state1(w, i + 1);
    return false;
}

bool state1(const string& w, int i) {
    cout << " -> S1";
    if (i == w.length()) {
        return false;
    }
    if (w[i] == '0') return state1(w, i + 1);
    else if (w[i] == '1') return state2(w, i + 1);
    return false;
}

bool state2(const string& w, int i) {
    cout << " -> S2";
    if (i == w.length()) {
        return true;
    }
    if (w[i] == '0') return state2(w, i + 1);
    else if (w[i] == '1') return state3(w, i + 1);
    return false;
}

bool state3(const string& w, int i) {
    cout << " -> S3";
    if (i == w.length()) {
        return true;
    }
    if (w[i] == '0') return state3(w, i + 1);
    else if (w[i] == '1') return state4(w, i + 1);
    return false;
}

bool state4(const string& w, int i) {
    cout << " -> S4";
    if (i == w.length()) {
        return false;
    }
    if (w[i] == '0' || w[i] == '1') {
        return state4(w, i + 1);
    }
    return false;
}

int main() {
    string input_string;
    cout << "Enter a string over {0, 1}: ";
    getline(cin,input_string);

    cout << "State transitions: Start";
    bool accepted = state0(input_string, 0);

    if (accepted) cout << "\nString Accepted" << endl;
    else cout << "\nString Rejected" << endl;

    return 0;
}
