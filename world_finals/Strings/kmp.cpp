template <typename T> vector<int> kmp(int sz, const T s[]) {
	vector<int> pi(sz);
	for(int i=1;i<sz;i++) {
		int &j = pi[i];
		for(j=pi[i-1];j>0 && s[i]!=s[j];j=pi[j-1]);
		if(s[i] == s[j]) j++;
	}
	return pi;
};
