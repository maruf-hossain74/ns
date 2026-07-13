#include <iostream>
#include <vector>
using namespace std;

// Simple round function: XOR with subkey
int F(int right, int key) {
    return right ^ key;
}

int feistelEncrypt(int plaintext, vector<int> keys) {
    int left = (plaintext >> 4) & 0xF;   // Upper 4 bits
    int right = plaintext & 0xF;         // Lower 4 bits

    for (int i = 0; i < keys.size(); i++) {
        int temp = right;
        right = left ^ F(right, keys[i]);
        left = temp;
    }

    return (left << 4) | right;
}

int feistelDecrypt(int ciphertext, vector<int> keys) {
    // Reverse the key order
    reverse(keys.begin(), keys.end());

    int left = (ciphertext >> 4) & 0xF;
    int right = ciphertext & 0xF;

    for (int i = 0; i < keys.size(); i++) {
        int temp = right;
        right = left ^ F(right, keys[i]);
        left = temp;
    }

    return (left << 4) | right;
}

int main() {
    int plaintext;
    int numRounds;
    
    cout << "Enter plaintext (0-255): ";
    cin >> plaintext;

    cout << "Enter number of rounds: ";
    cin >> numRounds;

    vector<int> keys(numRounds);
    cout << "Enter round keys:" << endl;
    for (int i = 0; i < numRounds; i++) {
        cin >> keys[i];
    }

    int ciphertext = feistelEncrypt(plaintext, keys);
    cout << "Encrypted Text: " << ciphertext << endl;

    int decrypted = feistelDecrypt(ciphertext, keys);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}