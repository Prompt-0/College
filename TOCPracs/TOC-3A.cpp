// Program 3: Accepts strings of length >= 4 over {a,b} where the first two
// characters match the last two.
#include <iostream>
#include <string>

// Forward declarations for all 19 states
void q_start(const std::string& w, int i);
void q_a(const std::string& w, int i);
void q_b(const std::string& w, int i);
// Prefix states
void q_aa(const std::string& w, int i);
void q_ab(const std::string& w, int i);
void q_ba(const std::string& w, int i);
void q_bb(const std::string& w, int i);
// States for prefix "aa"
void q_aa_a(const std::string& w, int i);
void q_aa_b(const std::string& w, int i);
void q_aa_aa(const std::string& w, int i);
// States for prefix "ab"
void q_ab_a(const std::string& w, int i);
void q_ab_b(const std::string& w, int i);
void q_ab_ab(const std::string& w, int i);
// States for prefix "ba"
void q_ba_a(const std::string& w, int i);
void q_ba_b(const std::string& w, int i);
void q_ba_ba(const std::string& w, int i);
// States for prefix "bb"
void q_bb_a(const std::string& w, int i);
void q_bb_b(const std::string& w, int i);
void q_bb_bb(const std::string& w, int i);

// Helper for rejection message
void reject(const std::string& w) {
    std::cout << "\nString Rejected: Does not meet criteria." << std::endl;
}

// State implementations
void q_start(const std::string& w, int i) {
    if (i == w.length()) { reject(w); return; }
    if (w[i] == 'a') q_a(w, i + 1);
    else if (w[i] == 'b') q_b(w, i + 1);
}

void q_a(const std::string& w, int i) {
    if (i == w.length()) { reject(w); return; }
    if (w[i] == 'a') q_aa(w, i + 1);
    else if (w[i] == 'b') q_ab(w, i + 1);
}

void q_b(const std::string& w, int i) {
    if (i == w.length()) { reject(w); return; }
    if (w[i] == 'a') q_ba(w, i + 1);
    else if (w[i] == 'b') q_bb(w, i + 1);
}

// --- Prefix established states ---
void q_aa(const std::string& w, int i) {
    if (i == w.length()) { reject(w); return; }
    if (w[i] == 'a') q_aa_a(w, i + 1);
    else if (w[i] == 'b') q_aa_b(w, i + 1);
}

void q_ab(const std::string& w, int i) {
    if (i == w.length()) { reject(w); return; }
    if (w[i] == 'a') q_ab_a(w, i + 1);
    else if (w[i] == 'b') q_ab_b(w, i + 1);
}

void q_ba(const std::string& w, int i) {
    if (i == w.length()) { reject(w); return; }
    if (w[i] == 'a') q_ba_a(w, i + 1);
    else if (w[i] == 'b') q_ba_b(w, i + 1);
}

void q_bb(const std::string& w, int i) {
    if (i == w.length()) { reject(w); return; }
    if (w[i] == 'a') q_bb_a(w, i + 1);
    else if (w[i] == 'b') q_bb_b(w, i + 1);
}

// --- Tracking states for prefix "aa" ---
void q_aa_a(const std::string& w, int i) {
    if (i == w.length()) { reject(w); return; }
    if (w[i] == 'a') q_aa_aa(w, i + 1);
    else if (w[i] == 'b') q_aa_b(w, i + 1);
}

void q_aa_b(const std::string& w, int i) {
    if (i == w.length()) { reject(w); return; }
    if (w[i] == 'a') q_aa_a(w, i + 1);
    else if (w[i] == 'b') q_aa_b(w, i + 1);
}

void q_aa_aa(const std::string& w, int i) { // FINAL STATE
    if (i == w.length()) { std::cout << "\nString Accepted!" << std::endl; return; }
    if (w[i] == 'a') q_aa_aa(w, i + 1);
    else if (w[i] == 'b') q_aa_b(w, i + 1);
}

// --- Tracking states for prefix "ab" ---
void q_ab_a(const std::string& w, int i) {
    if (i == w.length()) { reject(w); return; }
    if (w[i] == 'a') q_ab_a(w, i + 1);
    else if (w[i] == 'b') q_ab_ab(w, i + 1);
}

void q_ab_b(const std::string& w, int i) {
    if (i == w.length()) { reject(w); return; }
    if (w[i] == 'a') q_ab_a(w, i + 1);
    else if (w[i] == 'b') q_ab_b(w, i + 1);
}

void q_ab_ab(const std::string& w, int i) { // FINAL STATE
    if (i == w.length()) { std::cout << "\nString Accepted!" << std::endl; return; }
    if (w[i] == 'a') q_ab_a(w, i + 1);
    else if (w[i] == 'b') q_ab_b(w, i + 1);
}

// --- Tracking states for prefix "ba" ---
void q_ba_a(const std::string& w, int i) {
    if (i == w.length()) { reject(w); return; }
    if (w[i] == 'a') q_ba_a(w, i + 1);
    else if (w[i] == 'b') q_ba_b(w, i + 1);
}

void q_ba_b(const std::string& w, int i) {
    if (i == w.length()) { reject(w); return; }
    if (w[i] == 'a') q_ba_ba(w, i + 1);
    else if (w[i] == 'b') q_ba_b(w, i + 1);
}

void q_ba_ba(const std::string& w, int i) { // FINAL STATE
    if (i == w.length()) { std::cout << "\nString Accepted!" << std::endl; return; }
    if (w[i] == 'a') q_ba_a(w, i + 1);
    else if (w[i] == 'b') q_ba_b(w, i + 1);
}

// --- Tracking states for prefix "bb" ---
void q_bb_a(const std::string& w, int i) {
    if (i == w.length()) { reject(w); return; }
    if (w[i] == 'a') q_bb_a(w, i + 1);
    else if (w[i] == 'b') q_bb_b(w, i + 1);
}

void q_bb_b(const std::string& w, int i) {
    if (i == w.length()) { reject(w); return; }
    if (w[i] == 'a') q_bb_a(w, i + 1);
    else if (w[i] == 'b') q_bb_bb(w, i + 1);
}

void q_bb_bb(const std::string& w, int i) { // FINAL STATE
    if (i == w.length()) { std::cout << "\nString Accepted!" << std::endl; return; }
    if (w[i] == 'a') q_bb_a(w, i + 1);
    else if (w[i] == 'b') q_bb_bb(w, i + 1);
}

int main() {
    std::string input_string;
    std::cout << "Enter a string over {a, b} of length 4 or more: ";
    std::cin >> input_string;

    if (input_string.length() < 4) {
        std::cout << "String Rejected: Length must be 4 or more." << std::endl;
        return 0;
    }

    q_start(input_string, 0);

    return 0;
}

