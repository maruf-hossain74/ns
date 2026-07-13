#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string generateKey(string text, string key) {
    int x = text.length();

    for (int i = 0; key.length() < x; i++) {
        key += text[i];
    }
    return key;
}

string encrypt(string text, string key) {
    string cipher = "";

    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char kbase = isupper(key[i]) ? 'A' : 'a';

            int p = text[i] - base;
            int k = tolower(key[i]) - 'a';

            cipher += char((p + k) % 26 + base);
        } else {
            cipher += text[i];
        }
    }
    return cipher;
}

// Decryption
string decrypt(string cipher, string key) {
    string plaintext = "";

    for (int i = 0; i < cipher.length(); i++) {
        if (isalpha(cipher[i])) {
            char base = isupper(cipher[i]) ? 'A' : 'a';

            int c = cipher[i] - base;
            int k;

            if (i < key.length()) {
                k = tolower(key[i]) - 'a';
            } else {
                k = tolower(plaintext[i - key.length()]) - 'a';
            }

            char p = char((c - k + 26) % 26 + base);
            plaintext += p;
        } else {
            plaintext += cipher[i];
        }
    }
    return plaintext;
}

int main() {
    string text, key;

    cout << "===== Auto-Key Cipher =====\n";

    cout << "Enter plaintext: ";
    getline(cin, text);

    cout << "Enter inital key: ";
    cin >> key;

    string fullKey = generateKey(text, key);

    string cipher = encrypt(text, fullKey);
    cout << "\nEncrypted: " << cipher << endl;

    string decrypted = decrypt(cipher, key);
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}