// Binary Indexed Tree 2D

// 0-indexed
// update(x, y, val): m[row][col] += val
// query(x, y): returns sum m[0..=x][0..=y]
template <typename T> struct Bit2D {
	int n, m;
	vector<T> bit;
	Bit2D(int _n, int _m): n(_n), m(_m), bit(n*m) {}

	T query(int x, int y) {
		T res = 0;
		for(x+=1;x>0;x-=x&-x)
			for(int z=y+1;z>0;z-=z&-z)
				res += bit[(x-1)*m+z-1];
		return res;
	}

	void update(int x, int y, T val) {
		for(x+=1;x<=n;x+=x&-x)
			for(int z=y+1;z<=m;z+=z&-z)
				bit[(x-1)*m+z-1] += val;
	}
};
