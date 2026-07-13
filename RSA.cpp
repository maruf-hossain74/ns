#include <iostream>
using namespace std;

long long gcd(long long a, long long b) {
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

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

long long modInverse(long long e, long long phi) {
    for(long long d = 1; d < phi; d++) {
        if((e * d) % phi == 1)
            return d;
    }
    return -1;
}

int main() {
    long long p, q;

    cout << "Enter two prime numbers: ";
    cin >> p >> q;

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    long long e;

    cout << "Enter public key value e: ";
    cin >> e;

    while(gcd(e, phi) != 1) {
        cout << "Invalid e. Enter another value: ";
        cin >> e;
    }

    long long d = modInverse(e, phi);

    cout << "Public Key: (" << e << ", " << n << ")" << endl;
    cout << "Private Key: (" << d << ", " << n << ")" << endl;

    long long message;

    cout << "Enter message value: ";
    cin >> message;

    long long encrypted = powerMod(message, e, n);
    cout << "Encrypted Message: " << encrypted << endl;

    long long decrypted = powerMod(encrypted, d, n);
    cout << "Decrypted Message: " << decrypted << endl;

    return 0;
}