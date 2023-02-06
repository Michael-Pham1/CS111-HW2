#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

/*
TODO
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
vector<int> parseMessage(string m);
int gcdExtended(int a, int b, int *x, int *y);
int modInverse(int A, int M);


int minv(int a, int b);

int main(){
    int e = 0, n = 0, m = 0, p = 0, q = 0, totient = 0, d = 0, temp1 = 0, invMod1 = 0;
    string message = "", temp = "";
    vector<int> encrypted, decrypted;
    map<int, char> dict = {{7, 'A'}, {8, 'B'}, {9, 'C'}, {10, 'D'},
                            {11, 'E'},{12, 'F'}, {13, 'G'}, {14, 'H'},
                            {15, 'I'}, {16, 'J'}, {17, 'K'},{18, 'L'},
                            {19, 'M'}, {20, 'N'},{21, 'O'}, {22, 'P'},
                            {23, 'Q'}, {24, 'R'}, {25, 'S'}, {26, 'T'},
                            {27, 'U'}, {28, 'V'},{29, 'W'},{30, 'X'},
                            {31, 'Y'}, {32, 'Z'}, {33, ' '},
                            {34, '"'}, {35, ','}, {36, '.'}, {37, '\''}
                            };

    e = 7;
    n = 4453;
    cin >> e;
    cin >> n;
    cin >> m;
    for(int i = 0; i < m; i++){
        cin >> temp1;
        encrypted.push_back(temp1);
    }
    p = findDivisor(n);
    q = n / p;
    totient = eulersTotient(p, q);
    d = modInverse(e, totient);
    // invMod1 = modInverse(e, totient);
    // cout << invMod1 << endl;
    if(GCD(e, totient) !=  1 || e >= n || !isPrime(p) || !isPrime(q)){
        cout << "Public key is not valid!";
        return 0;
    }
    cout << p << " " << q << " " << totient << " " << d << endl;
    for (int i : encrypted){
        decrypted.push_back(moduloCalculator(i, d, n));
    }
    for(int i : decrypted){
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < decrypted.size(); i++){
        cout << dict[decrypted.at(i)];
    }
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
    for (int i = 0; i < 10000; i++) {
        for (int j = 1; j < totient; j++) { 
            if (totient * i == (e * j) - 1) {
                res = j;
                break;
            }
        }
    }
    return res;
}

int minv(int e, int totient) {
    int d = 0;
    for (int i = 1; i < 10000; i++) {
        if (i*(GCD(e, totient)) == 1) {
            d = i;
            break;
        }
    }
    return d;
}

int GCD(int a, int b){
    if (b < a){
        int temp = a;
        a = b;
        b = temp;
    }
    int r = a % b;
    while(r){
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

int moduloCalculator(int base, int exp, int mod) {
    int product = 1;
    while (exp >= 1){
        while((base < mod && base != 1)){
            if(exp % 2 == 1){
                exp -= 1;
                product *= base;
                product %= mod;
            }
            exp /= 2;
            base *= base;
        }
        if(base == 1 || base == 0){
            break;
        }
        base = base % mod;
    }
    return product % mod;
}

vector<int> parseMessage(string m) {
    char delim = ' ';
    vector<int> words;

    stringstream sstream(m);
    string word;
    while (getline(sstream, word, delim)) {
        int encrypted = stoi(word);
        words.push_back(encrypted);
    }
    return words;
}

int gcdExtended(int a, int b, int *x, int *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
 
    int x1, y1; // To store results of recursive call
    int gcd = gcdExtended(b%a, a, &x1, &y1);
 
    // Update x and y using results of
    // recursive call
    *x = y1 - (b/a) * x1;
    *y = x1;
 
    return gcd;
}
int modInverse(int A, int M)
{
    int x = 0, y;
    int g = gcdExtended(A, M, &x, &y);
    int res = (x % M + M) % M;
    return res;
}
