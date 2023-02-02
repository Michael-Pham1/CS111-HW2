#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

/*
TODO
Large modulo calculator
Parse encrypted message
decrypt each message
Print out message
Word bank

*/

/* Values
p,q = 61, 73
e = 7
n = 4453
Totient(n) = (p-1)(q-1) = 60 * 72 = 4320
d = e^-1 mod (totient) = 7^-1 mod 4320 = 3703
*/
bool isPrime(int p);
int findDivisor(int n);
int eulersTotient(int p, int q);
int invMod(int e, int totient);
int GCD(int a, int b);
int moduloCalculator(int base, int exp, int mod);

int main(){
    int e, n, m, p, q, totient, d;
    string message, temp;

    cout << "Enter a value for e: ";
    getline(cin, temp);
    e = stoi(temp);

    cout << "Enter a value for n: ";
    getline(cin, temp);
    n = stoi(temp);

    cout << "Enter a value for m : ";
    getline(cin, temp);
    m = stoi(temp);

    cout << "Enter the message: ";
    getline(cin, message);
    //cout << e << n << m;
    //cout << isPrime(71);
    //cout << findDivisor(n);
    p = findDivisor(n);
    cout << "p: " << p << endl;
    q = n / p;
    cout << "q: " << q << endl;
    totient = eulersTotient(p, q);
    cout << "totient: " << totient << endl;
    d = invMod(e, totient);
    cout << "d: " << d << endl;
    cout << "Gcd: " << GCD(8, 7) << endl;
    cout << "5^99 mod 23: " << moduloCalculator(5, 99, 23);
    return 0;
}

//Checks if number is prime
bool isPrime(int p){
    for(int i = 2; i < p; i++){
        if(p % i == 0){
            return false;
        }
    }
    return true;
}

//Finds divisor
int findDivisor(int n){
    for(int i = 2; i < ceil(n / 2); i++){
        if(isPrime(i)){
            if(n % i == 0){
                return i;
            }
        }
    }
    return -1;
}

int eulersTotient(int p, int q){
    return((p-1) * (q-1)); 
}

int invMod(int e, int totient){
    int res = 0;
    for (int i = 1; i < 1000; i++) {
        for (int j = 1; j < totient; j++) {
            if (totient * i == (e * j) - 1) {
                res = j;
                break;
            }
        }
    }
    return res;
}

int GCD(int a, int b){
    int r = a % b;
    while(r){
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

int moduloCalculator(int base, int exp, int mod) {
    vector<int> storage;
    int product = 1;
    while (exp != 0){
        if(exp % 2 == 1){
            exp -= 1;
            storage.push_back(base);
        }
        exp /= 2;
        base *= base;
        base = base % mod;
    }
    for (int i : storage){
        product *= i;
    }
    return product % mod;
}