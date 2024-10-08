// Binary Indexed Tree
// !! zero indexed !!
template<typename T> struct Bit {
	vector<T> bit;
	Bit(int n): bit(n) {}
	void update(int id, T val) { for(id+=1; id<=int(bit.size()); id+=id&-id) bit[id-1] += val; }
	T query(int id) { T sum = T(); for(id+=1; id>0; id-=id&-id) sum += bit[id-1]; return sum; }
	// returns the first prefix for which sum of 0..=pos >= val; bit.size() if such prefix doesnt exists
	// assuems v[i] >= 0 for all i for monotonicity
	int lower_bound(T val) {
		T sum = T();
		int pos = 0, logn = 31 - __builtin_clz(bit.size());
		for(int l=logn;l>=0;l--) {
			int nxt = pos + (1<<l);
			if(nxt <= int(bit.size()) && sum + bit[nxt - 1] < val)
				sum += bit[nxt - 1], pos = nxt;
		}
		return pos;
	}
};
