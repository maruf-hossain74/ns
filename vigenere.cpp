#include <iostream>
#include <string>
using namespace std;

string generateKey(string text, string key) {
    string newKey = key;
    while(newKey.length() < text.length())
        newKey += key;
    return newKey.substr(0, text.length());
}

string encrypt(string text, string key) {
    string result = "";
    key = generateKey(text, key);

    for(int i = 0; i < text.length(); i++) {
        if(isalpha(text[i])) {
            char ch = text[i];
            char k = key[i];
            if(isupper(ch))
                result += char((ch - 'A' + toupper(k) - 'A') % 26 + 'A');
            else
                result += char((ch - 'a' + tolower(k) - 'a') % 26 + 'a');
        } else {
            result += text[i];
        }
    }
    return result;
}

string decrypt(string text, string key) {
    string result = "";
    key = generateKey(text, key);

    for(int i = 0; i < text.length(); i++) {
        if(isalpha(text[i])) {
            char ch = text[i];
            char k = key[i];
            if(isupper(ch))
                result += char((ch - 'A' - (toupper(k) - 'A') + 26) % 26 + 'A');
            else
                result += char((ch - 'a' - (tolower(k) - 'a') + 26) % 26 + 'a');
        } else {
            result += text[i];
        }
    }
    return result;
}

int main() {
    string text, key;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter key: ";
    cin >> key;

    string encrypted = encrypt(text, key);
    cout << "Encrypted Text: " << encrypted << endl;

    string decrypted = decrypt(encrypted, key);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}