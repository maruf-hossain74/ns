#include <iostream>
using namespace std;

long long powerMod(long long base, long long exp, long long mod) {
    long long result = 1;

    while(exp > 0) {
        if(exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp /= 2;
    }

    return result;
}

int main() {

    long long p, q, message;

    cout << "Enter two prime numbers: ";
    cin >> p >> q;

    long long n = p * q;

    cout << "Public Key (n): " << n << endl;
    cout << "Private Key: (" << p << ", " << q << ")" << endl;

    cout << "Enter message value: ";
    cin >> message;

    // Encryption
    long long cipher = (message * message) % n;

    cout << "Encrypted Message: " << cipher << endl;

    // Simple decryption demonstration
    long long decrypted = 0;

    for(long long i = 0; i < n; i++) {
        if((i * i) % n == cipher) {
            decrypted = i;
            break;
        }
    }

    cout << "Decrypted Message: " << decrypted << endl;

    return 0;
}