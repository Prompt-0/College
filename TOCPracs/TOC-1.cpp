#include <iostream>
#include <string>

using namespace std;

void state0(const string& w, int i);
void state1(const string& w, int i);
void state2(const string& w, int i);
void state3(const string& w, int i);

void state0(const string& w, int i) {
    cout << " -> S0";
    if (i == w.length()) {
        cout << "\nString Rejected" << endl;
        return;
    }

    if (w[i] == '0') {
        state0(w, i + 1);
    } else if (w[i] == '1') {
        state1(w, i + 1);
    }
}

void state1(const string& w, int i) {
    cout << " -> S1";
    if (i == w.length()) {
        cout << "\nString Rejected" << endl;
        return;
    }

    if (w[i] == '0') {
        state0(w, i + 1);
    } else if (w[i] == '1') {
        state2(w, i + 1);
    }
}

void state2(const string& w, int i) {
    cout << " -> S2";
    if (i == w.length()) {
        cout << "\nString Rejected" << endl;
        return;
    }

    if (w[i] == '0') {
        state0(w, i + 1);
    } else if (w[i] == '1') {
        state3(w, i + 1);
    }
}

void state3(const string& w, int i) {
    cout << " -> S3";
    if (i == w.length()) {
        cout << "\nString Accepted" << endl;
        return;
    }

    if (w[i] == '0' || w[i] == '1') {
        state3(w, i + 1);
    }
}

int main() {
    string input_string;
    cout << "Enter a string over {0, 1}: ";
    getline(cin,input_string);

    cout << "State transitions: Start";
    state0(input_string, 0);

    return 0;
}
