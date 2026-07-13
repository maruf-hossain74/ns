#include <iostream>
#include <string>
#include <vector>
using namespace std;

string encrypt(string text, int cols) {
    int len = text.length();
    int rows = (len + cols - 1) / cols; // ceiling division
    vector<vector<char>> matrix(rows, vector<char>(cols, 'X'));

    // Fill row-wise
    int k = 0;
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            if(k < len) matrix[i][j] = text[k++];

    // Read column-wise
    string ciphertext = "";
    for(int j=0;j<cols;j++)
        for(int i=0;i<rows;i++)
            ciphertext += matrix[i][j];

    return ciphertext;
}

string decrypt(string text, int cols) {
    int len = text.length();
    int rows = (len + cols - 1) / cols;
    vector<vector<char>> matrix(rows, vector<char>(cols, 'X'));

    // Fill column-wise
    int k = 0;
    for(int j=0;j<cols;j++)
        for(int i=0;i<rows;i++)
            if(k < len) matrix[i][j] = text[k++];

    // Read row-wise
    string plaintext = "";
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            plaintext += matrix[i][j];

    return plaintext;
}

int main() {
    string text;
    int cols;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter number of columns: ";
    cin >> cols;

    string encrypted = encrypt(text, cols);
    cout << "Encrypted Text: " << encrypted << endl;

    string decrypted = decrypt(encrypted, cols);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}