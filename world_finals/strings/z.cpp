// https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/Zfunc.h
// Description: z[i] computes the length of the longest common prefix of s[i:] and s in O(N)
vector<int> zfunc(string s) {
	int n = s.size();
	vector<int> z(n);
	for(int l = -1, r = -1, i = 1; i < n; i++) {
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while( i + z[i] < n && s[i + z[i]] == s[z[i]]i ) z[i]++;
		if( i + z[i] > r ) l = i, r = i + z[i];
	}
	return z;
}
