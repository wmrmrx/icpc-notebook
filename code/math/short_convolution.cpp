// fft::convolution(a, b): returns convolution between polynomials a and b
// approx 50% slower, but faster to code
// 026f0b
namespace fft {
	using cd = complex<double>;
	const double PI = acosl(-1);

	// a.size() == 2^n
	template <bool INVERT>
	void fft(vector<cd>& a) {
		int n = a.size();
		for (int i=1, j=0; i<n; i++) {
			int bit = n/2;
			for (; j & bit; bit /= 2)
				j ^= bit;
			j ^= bit;
			if(i < j) swap(a[i], a[j]);
		}
		for(int sz=2; sz<=n; sz*=2) {
			vector<cd> w(sz/2);
			for(int j=0;j<sz/2;j++) 
				w[j] = polar(1.0, 2*PI*j/sz*(INVERT?-1:1));
			for(int i=0; i<n; i+=sz) for(int j=0; j<sz/2; j++) {
				cd u = a[i+j], v = a[i+j+sz/2] * w[j];
				a[i+j] = u + v;
				a[i+j+sz/2] = u - v;
			}
		}
		if(INVERT) for(cd& x: a) x /= n;
	}

	// a and b must NOT be empty
	vector<int> convolution(vector<int> &a, vector<int> &b) {
		int rsz = a.size() + b.size() - 1, sz = 1;
		while(rsz > sz) sz *= 2;
		vector<cd> ca(all(a)), cb(all(b));
		ca.resize(sz); cb.resize(sz);
		fft<false>(ca); fft<false>(cb);
		for(int i=0;i<sz;i++)
			ca[i] *= cb[i];
		fft<true>(ca);
		vector<int> res(rsz);
		for(int i=0;i<rsz;i++) res[i] = round(ca[i].real());
		return res;
	}
}
