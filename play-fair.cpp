#include <iostream>
#include <vector>
#include <map>
#include <cctype>
using namespace std;

char matrix[5][5];
map<char, pair<int, int>> pos;

// Generate 5x5 matrix
void generateMatrix(string key) {
    bool used[26] = {false};

    key += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int row = 0, col = 0;

    for (char c : key) {
        c = toupper(c);

        if (c == 'J') c = 'I';

        if (!used[c - 'A']) {
            matrix[row][col] = c;
            pos[c] = {row, col};
            used[c - 'A'] = true;

            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }
}

string prepareText(string text) {
    string result = "";

    for (char c : text) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I';
            result += c;
        }
    }

    for (int i = 0; i < result.length(); i += 2) {
        if (i + 1 == result.length()) {
            result += 'X';
        } else if (result[i] == result[i + 1]) {
            result.insert(i + 1, 1, 'X');
        }
    }

    return result;
}

string encryptPair(char a, char b) {
    auto p1 = pos[a];
    auto p2 = pos[b];

    if (p1.first == p2.first) {
        return string(1, matrix[p1.first][(p1.second + 1) % 5]) +
               string(1, matrix[p2.first][(p2.second + 1) % 5]);
    } 
    else if (p1.second == p2.second) {
        return string(1, matrix[(p1.first + 1) % 5][p1.second]) +
               string(1, matrix[(p2.first + 1) % 5][p2.second]);
    } 
    else {
        return string(1, matrix[p1.first][p2.second]) +
               string(1, matrix[p2.first][p1.second]);
    }
}

string decryptPair(char a, char b) {
    auto p1 = pos[a];
    auto p2 = pos[b];

    if (p1.first == p2.first) {
        return string(1, matrix[p1.first][(p1.second + 4) % 5]) +
               string(1, matrix[p2.first][(p2.second + 4) % 5]);
    } 
    else if (p1.second == p2.second) {
        return string(1, matrix[(p1.first + 4) % 5][p1.second]) +
               string(1, matrix[(p2.first + 4) % 5][p2.second]);
    } 
    else {
        return string(1, matrix[p1.first][p2.second]) +
               string(1, matrix[p2.first][p1.second]);
    }
}

string encrypt(string text) {
    string prepared = prepareText(text);
    string result = "";

    for (int i = 0; i < prepared.length(); i += 2) {
        result += encryptPair(prepared[i], prepared[i + 1]);
    }

    return result;
}

string decrypt(string text) {
    string result = "";

    for (int i = 0; i < text.length(); i += 2) {
        result += decryptPair(text[i], text[i + 1]);
    }

    return result;
}

void printMatrix() {
    cout << "\nMatrix:\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    string key, text;

    cout << "===== Playfair Cipher =====\n";

    cout << "Enter key: ";
    getline(cin, key);

    cout << "Enter plaintext: ";
    getline(cin, text);

    generateMatrix(key);
    printMatrix();

    string encrypted = encrypt(text);
    cout << "\nEncrypted: " << encrypted << endl;

    string decrypted = decrypt(encrypted);
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}