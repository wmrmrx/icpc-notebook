//  NTT - Number Theoretic Transform
//  Description: Multiply two polinomials in Z_p, for p prime
//  Complexity: O(N logN)

//  Functions:
//      multiply(a, b)

//  Details:
//      Not all primes can be used and p = 998244353 is the most used prime. 
//      To multiply it for a general modulus, use 3 different possible primes 
//      and use Chinese Remainder Theorem to get the answear.

//  Possibilities
//  { 7340033, 5, 4404020, 1 << 20 },
//  { 415236097, 73362476, 247718523, 1 << 22 },
//  { 463470593, 428228038, 182429, 1 << 21},
//  { 998244353, 15311432, 469870224, 1 << 23 },
//  { 918552577, 86995699, 324602258, 1 << 22 }

namespace NTT {
    using Z = mint<998244353>;
    const Z root(15311432), root_1(469870224);
    int root_pw = 1<<23;

    void fft(vector<Z> & a, bool invert) {
	int n = a.size();

        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            Z wlen = invert ? root_1 : root;
            for (int i = len; i < root_pw; i <<= 1)
                wlen *= wlen;

            for (int i = 0; i < n; i += len) {
                Z w(1);
                for (int j = 0; j < len / 2; j++) {
                    Z u = a[i+j], v = a[i+j+len/2] * w;
                    a[i+j] = u + v;
                    a[i+j+len/2] = u - v;
                    w *= wlen;
                }
            }
        }

        if (invert) {
            Z n_1 = Z(n).inv();
            for (Z & x : a) x *= n_1;
        }
    }
 
    vector<Z> multiply(vector<Z> &a, vector<Z> &b) {
        vector<Z> fa = a, fb = b;
        int sz = a.size() + b.size() - 1, n = 1;
        while (n < sz) n <<= 1;

        fa.resize(n), fb.resize(n);
        fft(fa, 0), fft(fb, 0);
        for (int i = 0; i < fa.size(); i++) fa[i] *= fb[i];

        fft(fa, 1);
        fa.resize(sz);
        return fa;
    }
};
