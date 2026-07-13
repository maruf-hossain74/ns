#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> getKeyOrder(string key) {
    string sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
    vector<int> order;
    for(char c : key)
        order.push_back(sortedKey.find(c));
    return order;
}

string firstTransposition(string text, string key) {
    int cols = key.length();
    int rows = (text.length() + cols - 1) / cols;
    vector<vector<char>> grid(rows, vector<char>(cols, 'X'));

    int k = 0;
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            if(k<text.length()) grid[i][j] = text[k++];

    vector<int> order = getKeyOrder(key);
    string result = "";
    for(int i=0;i<cols;i++)
        for(int j=0;j<rows;j++)
            result += grid[j][order[i]];

    return result;
}

string secondTransposition(string text) {
    reverse(text.begin(), text.end());
    return text;
}

string encrypt(string text, string key) {
    string step1 = firstTransposition(text, key);
    string ciphertext = secondTransposition(step1);
    return ciphertext;
}

string decrypt(string text, string key) {
    string step1 = secondTransposition(text); // reverse the reverse
    string colsText = step1;
    int cols = key.length();
    int rows = (colsText.length() + cols - 1) / cols;
    vector<vector<char>> grid(rows, vector<char>(cols, 'X'));

    vector<int> order = getKeyOrder(key);
    int k = 0;
    for(int i=0;i<cols;i++)
        for(int j=0;j<rows;j++)
            grid[j][order[i]] = colsText[k++];

    string plaintext = "";
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            plaintext += grid[i][j];

    return plaintext;
}

int main() {
    string text, key;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter key: ";
    getline(cin, key);

    string encrypted = encrypt(text, key);
    cout << "Encrypted Text: " << encrypted << endl;

    string decrypted = decrypt(encrypted, key);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}