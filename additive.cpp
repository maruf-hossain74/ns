#include<bits/stdc++.h>
using namespace std;

string encrypt(string text, int key) {
    string result = "";
    for(int i = 0; i < text.length(); i++) {
        char ch = text[i];
        if(isupper(ch)) result += char((ch - 'A' + key) % 26 + 'A');
        else if(islower(ch)) result += char((ch - 'a' + key) % 26 + 'a');
        else result += char((ch - '0' + key) % 26 + '0');;
    }
    return result;
}
string decrypt(string text, int key) {
    string result = "";
    for(int i = 0; i < text.length(); i++) {
        char ch = text[i];
        if(isupper(ch)) result += char((ch - 'A' - key + 26) % 26 + 'A');
        else if(islower(ch)) result += char((ch - 'a' - key + 26) % 26 + 'a');
        else result += char((ch - '0' - key + 26) % 26 + '0');
    }
    return result;
}

int main() {
    string text;
    int key;
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
