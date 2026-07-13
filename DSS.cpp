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

long long modInverse(long long a, long long m) {
    for(long long i = 1; i < m; i++) {
        if((a * i) % m == 1)
            return i;
    }
    return -1;
}

int main() {

    long long p = 23;
    long long q = 11;
    long long g = 4;

    long long privateKey;
    cout << "Enter private key: ";
    cin >> privateKey;

    long long publicKey = powerMod(g, privateKey, p);

    cout << "Public Key: " << publicKey << endl;

    long long message;
    cout << "Enter message value: ";
    cin >> message;

    long long hash = message % q;

    long long k;
    cout << "Enter random value k: ";
    cin >> k;

    long long r = powerMod(g, k, p) % q;

    long long kInverse = modInverse(k, q);

    long long s = (kInverse * (hash + privateKey * r)) % q;

    cout << "Digital Signature: (" << r << ", " << s << ")" << endl;

    long long w = modInverse(s, q);

    long long u1 = (hash * w) % q;
    long long u2 = (r * w) % q;

    long long v = ((powerMod(g, u1, p) * 
                    powerMod(publicKey, u2, p)) % p) % q;

    if(v == r)
        cout << "Signature Verified Successfully" << endl;
    else
        cout << "Signature Verification Failed" << endl;

    return 0;
}