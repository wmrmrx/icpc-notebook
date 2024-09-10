// Description: Recovers any n-order linear recurrence relation from the first
// 2n terms of the recurrence.
// Useful for guessing linear recurrences after brute-forcing the first terms.
// Should work on any field, but numerical stability for floats is not guaranteed.
// Output will have size < n.
// Usage: berlekampMassey({0, 1, 1, 3, 5, 11}) // {1, 2}
// Time: O(N^2)
// Status: bruteforce-tested mod 5 for n <= 5 and all s
template<typename T>
vector<T> berlekampMassey(vector<T> s) {
	int n = s.size(), L = 0, m = 0;
	vector<T> C(n), B(n), V;
	C[0] = B[0] = T(1);
	T b = 1;
	for(int i = 0; i < n; i++) {
		++m;
		T d = s[i];
		for(int j = 1; j < L+1; j++)
			d = (d + C[j] * s[i - j]);
		if (d == T(0)) continue;
		V = C; T coef = d / b;
		for(int j = m; j < n; j++)
			C[j] = C[j] - coef*B[j-m];
		if (2 * L > i) continue;
		L = i + 1 - L; B = V; b = d; m = 0;
	}
	C.resize(L + 1); C.erase(C.begin());
	for(auto &x : C) x *= T(-1);
	return C;
}