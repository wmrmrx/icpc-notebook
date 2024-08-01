/**
   Rounding is safe if $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$
   (in practice $10^{16}$; higher for random inputs).
 */

typedef complex<double> C;
void fft(vector<C>& a) {
	int n = a.size(), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		for(int i = k; i < 2*k; i++){
			rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
		}
	}
	vector<int> rev(n);
	for(int i = 0; i < n; i++){
		rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	}
	for(int i = 0; i < n; i++){
		if (i < rev[i]) swap(a[i], a[rev[i]]);
	}
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k)
			for(int j = 0; j < k; j++){
				// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
				auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
				C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
				a[i + j + k] = a[i + j] - z;
				a[i + j] += z;

			}
}
vector<double> conv(const vector<double>& a, const vector<double>& b) {
	if (a.empty() || b.empty()) return {};
	int sza = a.size();
	int szb = b.size();
	vector<double> res(sza + szb - 1);
	int L = 32 - __builtin_clz(sza+szb-1), n = 1 << L;
	vector<C> in(n), out(n);
	copy(all(a), begin(in));
	for(int i = 0; i < szb; i++){
		in[i].imag(b[i]);
	}
	fft(in);
	for (C& x : in) x *= x;
	for(int i = 0; i < n; i++){
		out[i] = in[-i & (n - 1)] - conj(in[i]);
	}
	fft(out);
	for(int i =  0; i < sza+szb-1; i++){
		res[i] = imag(out[i]) / (4 * n);
	}
	return res;
}
