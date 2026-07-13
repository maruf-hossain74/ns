#include <iostream>
#include <iomanip>
using namespace std;

string xorCipher(string text, string key) {
    string result = "";

    for (int i = 0; i < text.length(); i++) {
        char k = key[i % key.length()];
        result += text[i] ^ k;
    }

    return result;
}

// print hex
void printHex(string text) {
    for (char c : text) {
        cout << hex << setw(2) << setfill('0') << (int)(unsigned char)c << " ";
    }
    cout << endl;
}

int main() {
    string text, key;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter key: ";
    getline(cin, key);

    string encrypted = xorCipher(text, key);

    cout << "\nEncrypted (hex): ";
    printHex(encrypted);

    string decrypted = xorCipher(encrypted, key);
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}