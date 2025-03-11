//finds min k s.t. L <= (k * A) % M <= R (or -1 if it does not exist
ll solve4(ll A, ll M, ll L, ll R) {
	if (L == 0) return 0;
	A %= M;
	ll ans = 0;	ll s1 = 1, s2 = 0;
	while(A > 0) {
		if (2 * A > M) {
			A = M - A; L = M - L;
			R = M - R; swap(L, R);
			ans += s2; s1 -= s2;
			s2 *= -1;
		}
		ll ff = (L + A - 1) / A;
		if (A * ff <= R) return ans + ff * s1;
		ans += (ff - 1) * s1;
		ff = (ff - 1) * A;
		L -= ff; R -= ff;
		ll z = (M + A - 1) / A;
		s2 = s1 * z - s2;
		swap(s1, s2); M = z * A - M; swap(A, M);
	}
	return -1;
}
