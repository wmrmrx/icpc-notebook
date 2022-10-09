/*
	Title: Fast Walsh-Hadamard trasform
	Description: Multiply two polynomials such that x^a * x^b = x^(op(a, b))
		- op(a, b) = a "xor" b, a "or" b, a "and" b
	Complexity: O(n log n)
	Credits: https://github.com/mochow13/competitive-programming-library/tree/master/Math
*/
const ll N = 1<<20;

template <typename T>
struct FWHT {
	void fwht(T io[], ll n) {
		for (ll d = 1; d < n; d <<= 1) {
			for (ll i = 0, m = d<<1; i < n; i += m) {
				for (ll j = 0; j < d; j++) { /// Don't forget modulo if required
					T x = io[i+j], y = io[i+j+d];
					io[i+j] = (x+y), io[i+j+d] = (x-y);	// xor
					// io[i+j] = x+y; // and
					// io[i+j+d] = x+y; // or
				}
			}
		}
	}
	void ufwht(T io[], ll n) {
		for (ll d = 1; d < n; d <<= 1) {
			for (ll i = 0, m = d<<1; i < n; i += m) {
				for (ll j = 0; j < d; j++) { /// Don't forget modulo if required
					T x = io[i+j], y = io[i+j+d];
					 /// Modular inverse if required here
					io[i+j] = (x+y)>>1, io[i+j+d] = (x-y)>>1; // xor
					// io[i+j] = x-y; // and
					// io[i+j+d] = y-x; // or
				}
			}
		}
	}
	// a, b are two polynomials and n is size which is power of two
	void convolution(T a[], T b[], ll n) {
		fwht(a, n), fwht(b, n);
		for (ll i = 0; i < n; i++)
			a[i] = a[i]*b[i];
		ufwht(a, n);
	}
	// for a*a	
	void self_convolution(T a[], ll n) {
		fwht(a, n);
		for (ll i = 0; i < n; i++)
			a[i] = a[i]*a[i];
		ufwht(a, n);
	}
};
FWHT<ll> fwht;
