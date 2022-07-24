/*
    NTT - Number Theoretic Transform
    Description: Multiply two polinomials in Z_p, for p prime
    Complexity: O(N logN)

    Functions:
        multiply(a, b)

    Details:
        Not all primes can be used and p = 998244353 is the most used prime. 
        To multiply it for a general modulus, use 3 different possible primes 
        and use Chinese Remainder Theorem to get the answear.

    Possibilities
    { 7340033, 5, 4404020, 1 << 20 },
    { 415236097, 73362476, 247718523, 1 << 22 },
    { 463470593, 428228038, 182429, 1 << 21},
    { 998244353, 15311432, 469870224, 1 << 23 },
    { 918552577, 86995699, 324602258, 1 << 22 }

    98bcfc
*/

namespace NTT {
    const ll mod = 998244353, root = 15311432, root_1 = 469870224, root_pw = 1 << 23;

    ll fastxp(ll n, ll e){
        ll ans = 1, pwr = n;
        while(e){
            if(e%2)  ans = ans * pwr % mod;
            e /= 2;
            pwr = pwr * pwr % mod;
        }
        return ans % mod;
    }


    void fft(vector<ll> & a, bool invert) {
        ll n = a.size();

        for (ll i = 1, j = 0; i < n; i++) {
            ll bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;

            if (i < j) swap(a[i], a[j]);
        }

        for (ll len = 2; len <= n; len <<= 1) {
            ll wlen = invert ? root_1 : root;
            for (ll i = len; i < root_pw; i <<= 1)
                wlen = wlen * wlen % mod;

            for (ll i = 0; i < n; i += len) {
                ll w = 1;
                for (ll j = 0; j < len / 2; j++) {
                    ll u = a[i+j], v = a[i+j+len/2] * w % mod;
                    a[i+j] = u + v < mod ? u + v : u + v - mod;
                    a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                    w = w * wlen % mod;
                }
            }
        }

        if (invert) {
            ll n_1 = fastxp(n, mod - 2);
            for (ll & x : a) x = x * n_1 % mod;
        }
    }
 
    vector<ll> multiply(vector<ll> &a, vector<ll> &b) {
        vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        ll sz = a.size() + b.size() - 1, n = 1;
        while (n < sz) n <<= 1;

        fa.resize(n), fb.resize(n);
        fft(fa, 0), fft(fb, 0);
        for (ll i = 0; i < fa.size(); i++) fa[i] = fa[i] * fb[i] % mod;

        fft(fa, 1);
        fa.resize(sz);
        return fa;
    }
};