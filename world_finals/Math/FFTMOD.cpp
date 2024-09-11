// Description: Higher precision FFT, can be used for convolutions modulo arbitrary integers
// as long as $N\log_2N\cdot \text{mod} < 8.6 \cdot 10^{14}$ (in practice $10^{16}$ or higher).
// Inputs must be in $[0, \text{mod})$.
template<int M> vector<ll> convMod(const vector<ll> &a, const vector<ll> &b) {
	if (a.empty() || b.empty()) return {};
	int sza = a.size();
	int szb = b.size();
	vector<ll> res(sza+szb-1);
	int B=32-__builtin_clz(sza+szb-1), n=1<<B, cut=int32_t(sqrt(M));
	vector<C> L(n), R(n), outs(n), outl(n);
	for(int i = 0; i < sza; i++){
		L[i] = C((int32_t)a[i] / cut, (int32_t)a[i] % cut);
	}
	for(int i = 0; i < szb; i++){
		R[i] = C((int32_t)b[i] / cut, (int32_t)b[i] % cut);
	}
	fft(L), fft(R);
	for(int i = 0; i < n; i++){
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl), fft(outs);
	for(int i = 0; i < sza+szb-1; i++){
		ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
		ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);
		res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
	}
	return res;
}
