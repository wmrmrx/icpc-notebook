/**
 * Author: chilli
 * License: CC0
 * Description: z[i] computes the length of the longest common prefix of s[i:] and s,
 * except z[0] = 0. (abacaba -> 0010301)
 * Time: O(n)
 * Status: stress-tested
 */
vector<int> Z(const string& S) {
	int n = S.size();
	vector<int> z(n);
	int l = -1, r = -1;
	for(int i = 1; i < n; i++){
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < n && S[i + z[i]] == S[z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
	return z;
}
