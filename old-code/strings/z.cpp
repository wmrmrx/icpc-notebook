// Z
template <typename T> vector<int> z_alg(int sz, const T s[]) {
	vector<int> ret(sz);
	for(int l=0,r=0,i=1;i<sz;i++) {
		auto expand = [&]() {
			while(r<sz && s[r-l]==s[r]) r++;
			ret[i] = r-l;
		};
		if(i >= r) {
			l=r=i;
			expand();
		} else {
			if(ret[i-l] < r-i) ret[i] = ret[i-l];
			else {
				l=i;
				expand();
			}
		}
	}
	return ret;
};
