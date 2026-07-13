#include <iostream>
#include <vector>
using namespace std;

int main() {

    vector<int> privateKey = {2, 3, 7, 14, 30};
    int modulus = 61;
    int multiplier = 17;

    vector<int> publicKey;

    // Generate public key
    for(int i = 0; i < privateKey.size(); i++) {
        publicKey.push_back((privateKey[i] * multiplier) % modulus);
    }

    cout << "Public Key: ";
    for(int x : publicKey)
        cout << x << " ";

    cout << endl;

    int message[5];

    cout << "Enter 5-bit message: ";
    for(int i = 0; i < 5; i++)
        cin >> message[i];

    // Encryption
    int cipher = 0;

    for(int i = 0; i < 5; i++) {
        if(message[i] == 1)
            cipher += publicKey[i];
    }

    cout << "Encrypted Message: " << cipher << endl;


    // Decryption
    int inverse = 18; // inverse of multiplier modulo modulus
    int value = (cipher * inverse) % modulus;

    vector<int> decrypted(5,0);

    for(int i = 4; i >= 0; i--) {
        if(privateKey[i] <= value) {
            decrypted[i] = 1;
            value -= privateKey[i];
        }
    }

    cout << "Decrypted Message: ";

    for(int i = 0; i < 5; i++)
        cout << decrypted[i];

    cout << endl;

    return 0;
}