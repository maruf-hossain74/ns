#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

string encrypt(string text, int a, int b) {
    string result = "";

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += char(((a * (c - base) + b) % 26) + base);
        } else {
            result += c;
        }
    }
    return result;
}

string decrypt(string text, int a, int b) {
    string result = "";
    int a_inv = modInverse(a, 26);

    if (a_inv == -1) {
        return "Error: No modular inverse exists for given 'a'!";
    }

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += char((a_inv * ((c - base - b + 26)) % 26) + base);
        } else {
            result += c;
        }
    }
    return result;
}

int main() {
    string text;
    int a, b;

    cout << "===== Affine Cipher Program =====\n";

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter key a (must be coprime with 26): ";
    cin >> a;

    cout << "Enter key b: ";
    cin >> b;

    if (gcd(a, 26) != 1) {
        cout << "Error: 'a' must be coprime with 26!\n";
        return 0;
    }

    string encrypted = encrypt(text, a, b);
    cout << "\nEncrypted Text: " << encrypted << endl;

    string decrypted = decrypt(encrypted, a, b);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}