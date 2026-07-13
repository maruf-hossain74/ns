#include<bits/stdc++.h>
using namespace std;

int modInverse(int key) {
    for (int i = 1; i < 26; i++) {
        if ((key * i) % 26 == 1)
            return i;
    }
    return -1;
}

string encrypt(string text, int key) {
    string result = "";

    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            char ch = text[i];
            if (isupper(ch))
                result += char(((ch - 'A') * key) % 26 + 'A');
            else
                result += char(((ch - 'a') * key) % 26 + 'a');
        } else {
            result += text[i];
        }
    }
    return result;
}

string decrypt(string text, int key) {
    string result = "";
    int invKey = modInverse(key);

    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            char ch = text[i];
            if (isupper(ch))
                result += char(((ch - 'A') * invKey) % 26 + 'A');
            else
                result += char(((ch - 'a') * invKey) % 26 + 'a');
        } else {
            result += text[i];
        }
    }
    return result;
}

int main() {
    string text;
    int key;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter key (relatively prime to 26): ";
    cin >> key;

    string encrypted = encrypt(text, key);
    cout << "Encrypted Text: " << encrypted << endl;

    string decrypted = decrypt(encrypted, key);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}