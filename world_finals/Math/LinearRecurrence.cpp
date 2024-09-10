/**
 * Description: Generates the $k$'th term of an $n$-order
 * linear recurrence $S[i] = \sum_j S[i-j-1]tr[j]$,
 * given $S[0 \ldots \ge n-1]$ and $tr[0 \ldots n-1]$.
 * Faster than matrix multiplication.
 * Useful together with Berlekamp--Massey.
 * Usage: linearRec({0, 1}, {1, 1}, k) // k'th Fibonacci number
 * Time: O(n^2 \log k)
 * Status: bruteforce-tested mod 5 for n <= 5
 */
template<typename T>
T linearRec(vector<T> S, vector<T> tr, ll k) {
	int n = tr.size();

	auto combine = [&](vector<T> a, vector<T> b) {
		vector<T> res(n * 2 + 1);
		for(int i = 0; i < n+1; i++){
			for(int j = 0; j < n+1; j++){
				res[i+j] = res[i+j] + a[i]*b[j];
			}
		}
		for (int i = 2 * n; i > n; --i){ 
			for(int j = 0; j < n; j++){
				res[i-1-j] = res[i-1-j] + res[i]*tr[j];
			}
		}
		res.resize(n + 1);
		return res;
	};
	vector<T> pol(n + 1), e(pol);
	pol[0] = e[1] = 1;
	for (++k; k; k /= 2) {
		if (k % 2) pol = combine(pol, e);
		e = combine(e, e);
	}
	T res = 0;
	for(int i = 0; i < n; i++){
		res = res + pol[i+1]*S[i];
	}
	return res;
}
//S is the first k terms and C is the coeficients
// 4.5 seg for 10^5, pretty heavy in practice
template <typename T>
T LinearRecurrence(vector<T>& S, vector<T> &C, long long n) {
	if (C.empty()) return 0;
	int k = (int)C.size();
	assert((int)S.size() == k);
	if (n < k) return S[n];
	auto Q = C;
	for (auto &x: Q) x *= T(-1);
	Q.insert(Q.begin(), 1);
	auto P = multiply(S, Q); //poly multiplication
	P.resize(k);
	while(n) {
		auto Qminus = Q;
		for(int i = 1; i < (int)Qminus.size(); i += 2) Qminus[i] *= T(-1);
		auto Si = multiply(P, Qminus); //poly multiplication
		auto Ti = multiply(Q, Qminus); //poly multiplication
		if(n & 1) {
			for(int i = 1 ; i < (int)Si.size() ; i += 2) P[i>>1] = Si[i];
			for(int i = 0 ; i < (int)Ti.size() ; i += 2) Q[i>>1] = Ti[i];
		} else {
			for(int i = 0 ; i < (int)Si.size() ; i += 2) P[i>>1] = Si[i];
			for(int i = 0 ; i < (int)Ti.size() ; i += 2) Q[i>>1] = Ti[i];
		}
		n >>= 1;
	}
	return P[0];
}