int mul(int a, int b, int mod){
	return ( __int128(a)*b)%mod;
}

int pw(int a, int n, int mod){
	int ret = 1;
	while(n > 0){
		if(n&1) ret = mul(ret,a,mod);
		a = mul(a,a,mod);
		n /= 2;
	}
	return ret;
}

bool isPrime(int n){
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	int A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	int s = __builtin_ctzll(n-1), d = n >> s;
	for(int a : A){
		int p = pw(a%n,d,n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = mul(p, p, n);
		if (p != n-1 && i != s) return false;
	}
	return true;
}

int pollard(int n){
	int x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	auto f = [&](int z) { return mul(z, z, n) + i; };
	while (t++ % 40 || __gcd(prd, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if ((q = mul(prd, max(x,y) - min(x,y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}

vector<int> factor(int n){
	if (n == 1) return {};
	if (isPrime(n)) return {n};
	int x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), all(r));
	return l;
}
//O(log^2) on worst, O(log) on average
int sqrt(int a, int p){
	a %= p; if (a < 0) a += p;
	if (a == 0) return 0;
	if(pw(a, (p-1)/2, p) != 1) return -1; //no solution
	if (p % 4 == 3) return pw(a, (p+1)/4, p);
	int s = p - 1, n = 2;
	int r = 0, m;
	while (s % 2 == 0)
		++r, s /= 2;
	while (pw(n, (p - 1) / 2, p) != p - 1) ++n;
	int x = pw(a, (s + 1) / 2, p);
	int b = pw(a, s, p), g = pw(n, s, p);
	for (;; r = m) {
		int t = b;
		for (m = 0; m < r && t != 1; ++m)
			t = t * t % p;
		if (m == 0) return x;
		int gs = pw(g, 1LL << (r - m - 1), p);
		g = gs * gs % p;
		x = x * gs % p;
		b = b * g % p;
	}
	assert(0);
	return -1;
}
