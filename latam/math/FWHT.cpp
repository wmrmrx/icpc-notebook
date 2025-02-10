// Fast Walsh-Hadamard trasform
// Description: Multiply two polynomials such that x^a * x^b = x^(op(a, b))
// 	- op(a, b) = a "xor" b, a "or" b, a "and" b
// Complexity: O(n log n)

namespace FWHT {
    template <typename T>
    void fwht(vector<T> &io, ll n) {
        for (ll d = 1; d < n; d <<= 1) {
            for (ll i = 0, m = d<<1; i < n; i += m) {
                for (ll j = 0; j < d; j++) { /// Don't forget modulo if required
                    T x = io[i+j], y = io[i+j+d];
                    io[i+j] = (x+y), io[i+j+d] = (x-y); // xor
                    // io[i+j] = x+y; // and
                    // io[i+j+d] = x+y; // or
                }
            }
        }
    }
    template <typename T>
    void ufwht(vector<T> &io, ll n) {
        for (ll d = 1; d < n; d <<= 1) {
            for (ll i = 0, m = d<<1; i < n; i += m) {
                for (ll j = 0; j < d; j++) { /// Don't forget modulo if required
                    T x = io[i+j], y = io[i+j+d];
                    io[i+j] = (x+y) / 2, io[i+j+d] = (x-y) / 2; // xor
                    // io[i+j] = x-y; // and
                    // io[i+j+d] = y-x; // or
                }
            }
        }
    }
    // a, b are two polynomials and n is size which is power of two
    template <typename T>
    vector<Z> convolution(vector<T> &a, vector<T> &b, ll n) {
        fwht<T>(a, n), fwht<T>(b, n);
        for (ll i = 0; i < n; i++)
            a[i] = a[i]*b[i];
        ufwht<T>(a, n);
        return a;
    }
    // for a*a  
    template <typename T>
    vector<T> self_convolution(vector<T> a, ll n) {
        fwht<T>(a, n);
        for (ll i = 0; i < n; i++)
            a[i] = a[i]*a[i];
        ufwht<T>(a, n);
        return a;
    }
};

