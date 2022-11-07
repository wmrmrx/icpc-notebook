// 0-indexed
// update(x, y, val): m[row][col] += val
// query(x, y): returns sum m[0..=x][0..=y]
// 1695dc
template <typename T>
struct Bit2D {
	struct Bit {
		vector<T> bit;
		Bit(int sz): bit(sz) {}
		T query(int id) {
			T res = 0;
			for(id+=1;id>0;id-=id&-id) 
				res += bit[id-1];
			return res;
		}
		void update(int id, T val) {
			for(id+=1;id<=bit.size();id+=id&-id) 
				bit[id-1]+=val;
		}
	};
	vector<Bit> bit;
	Bit2D(int n, int m): bit(n, Bit(m)) {}

	T query(int x, int y) {
		T res = 0;
		for(x+=1;x>0;x-=x&-x)
			res += bit[x-1].query(y);
		return res;
	}

	void update(int x, int y, T val) {
		for(x+=1;x<=bit.size();x+=x&-x)
			bit[x-1].update(y, val);
	}
};
