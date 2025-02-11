// Manacher
// Given a string s, computes p := manacher(s.data(), s.size()), where
// - p[0][i] = half length of even lenght palindrome centered around s[i], s[i+1]
// - p[1][i] = half length of odd lenght palindrome centered around s[i]
// Source: http://codeforces.com/blog/entry/12143
// Time: O(N)
template<typename T>
array<vector<int>, 2> manacher(const T s[], int n) {
	using vi = vector<int>;
	array<vi, 2> p = {vi(n+1), vi(n)};
	for(int z: {0, 1}) for(int i=0,l=0,r=0; i < n; i++) {
		int t = r - i + !z;
		if(i < r)
			p[z][i] = min(t, p[z][l+t]);
		int pl = i - p[z][i], 
		    pr = i + p[z][i] - !z;
		while(pl > 0 && pr + 1 < n && s[pl-1] == s[pr+1])
			p[z][i]++, pl--, pr++;
		if(pr>r) 
			l = pl, r = pr;
	}
	p[0].erase(p[0].begin());
	p[0].pop_back();
	return p;
}
