#include <iostream>
#include <vector>
#include <string>
using namespace std;

int mod26(int x) {
    x %= 26;
    return (x < 0) ? x + 26 : x;
}

vector<vector<int>> multiply(vector<vector<int>> &a, vector<vector<int>> &b) {
    int n = a.size();
    vector<vector<int>> result(n, vector<int>(1, 0));
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            result[i][0] += a[i][j] * b[j][0];
    for(int i=0;i<n;i++)
        result[i][0] = mod26(result[i][0]);
    return result;
}

int modInverse(int a, int m) {
    a %= m;
    for(int x=1; x<m; x++)
        if((a*x)%m == 1) return x;
    return -1;
}

vector<vector<int>> inverseMatrix(vector<vector<int>> &key) {
    int n = key.size();
    int det = key[0][0]*key[1][1] - key[0][1]*key[1][0];
    det = mod26(det);
    int invDet = modInverse(det,26);
    vector<vector<int>> inv(2, vector<int>(2));
    inv[0][0] = mod26(invDet * key[1][1]);
    inv[0][1] = mod26(invDet * -key[0][1]);
    inv[1][0] = mod26(invDet * -key[1][0]);
    inv[1][1] = mod26(invDet * key[0][0]);
    return inv;
}

vector<vector<int>> textToVector(string text) {
    vector<vector<int>> vec(2, vector<int>(1));
    for(int i=0;i<2;i++)
        vec[i][0] = toupper(text[i]) - 'A';
    return vec;
}

string vectorToText(vector<vector<int>> &vec) {
    string text = "";
    for(int i=0;i<vec.size();i++)
        text += char(vec[i][0] + 'A');
    return text;
}

string encrypt(string plaintext, vector<vector<int>> &key) {
    if(plaintext.length()%2 != 0) plaintext += "X";
    string ciphertext = "";
    for(int i=0;i<plaintext.length();i+=2) {
        auto vec = textToVector(plaintext.substr(i,2));
        auto res = multiply(key, vec);
        ciphertext += vectorToText(res);
    }
    return ciphertext;
}

string decrypt(string ciphertext, vector<vector<int>> &key) {
    auto invKey = inverseMatrix(key);
    string plaintext = "";
    for(int i=0;i<ciphertext.length();i+=2) {
        auto vec = textToVector(ciphertext.substr(i,2));
        auto res = multiply(invKey, vec);
        plaintext += vectorToText(res);
    }
    return plaintext;
}

int main() {
    vector<vector<int>> key(2, vector<int>(2));
    string text;

    cout << "Enter 2x2 Key Matrix:" << endl;
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            cin >> key[i][j];

    cout << "Enter text: ";
    cin >> text;

    string encrypted = encrypt(text, key);
    cout << "Encrypted Text: " << encrypted << endl;

    string decrypted = decrypt(encrypted, key);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}