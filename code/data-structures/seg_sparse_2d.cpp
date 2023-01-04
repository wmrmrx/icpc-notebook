/*
    Segtree 2D:
    Data structure that makes operation on a grid.
    Grid of dimensions N x M

    Operations:
	    update(x, y, val) <- update on point (x, y)
	    query(lx, rx, ly, ry) <- query on rectangle [lx..rx] x [ly..ry]

    O(logNlogM) complexity per operation
    O(N + UlogNlogM) memory, where U is the number of updates
*/

// 56f76e
namespace seg2d {
	// YOU ONLY NEED TO CHANGE THIS BLOCK
	const int N = 200'000, M = 200'000;
	using T = int32_t;
	const T zero = 0; // INF if maintaining minimum, for example
	T merge(T a, T b) {
		return a + b;
	}

	struct Node {
		T s = zero;
		int32_t l = 0, r = 0;
	};
	int root[4*N];
	vector<Node> v;

	void upd(int& no, int l, int r, int pos, T val) {
		if(not no) {
			no = v.size();
			//assert(no < v.capacity());
			v.emplace_back();
		}
		if(l == r) v[no].s = val; // !!! OR v[no].s = merge(v[no].s, val) !!!
		else {
			int m = (l+r)/2;
			auto &[s, nl, nr] = v[no];
			if(pos <= m) upd(nl, l, m, pos, val);
			else upd(nr, m+1, r, pos, val);
			s = merge(v[nl].s, v[nr].s);
		}
	}

	T qry(int no, int l, int r, int ql, int qr) {
		if(not no) return zero;
		if(qr < l || r < ql) return zero;
		auto &[s, nl, nr] = v[no];
		if(ql <= l && r <= qr) return s;
		int m = (l+r)/2;
		return merge(qry(nl, l, m, ql, qr),
				qry(nr, m+1, r, ql, qr));
	}

	void upd(int no, int l, int r, int x, int y, T val) {
		upd(root[no], 0, M-1, y, val);
		if(l == r) return;
		int m = (l+r)/2;
		if(x <= m) upd(2*no, l, m, x, y, val);
		else upd(2*no+1, m+1, r, x, y, val);
	}

	T qry(int no, int l, int r, int lx, int rx, int ly, int ry) {
		if(rx < l || r < lx) return zero;
		if(lx <= l && r <= rx) return qry(root[no], 0, N-1, ly, ry);
		int m = (l+r)/2;
		return merge( qry(2*no, l, m, lx, rx, ly, ry),
				qry(2*no+1, m+1, r, lx, rx, ly, ry) );
	}

	void build(int no, int l, int r) {
		root[no] = v.size();
		v.emplace_back();
		if(l == r) return;
		int m = (l + r) / 2;
		build(2*no, l, m);
		build(2*no+1, m+1, r);
	}

	void update(int x, int y, T val) {
		upd(1, 0, N-1, x, y, val);
	}

	int query(int lx, int rx, int ly, int ry) {
		return qry(1, 0, N-1, lx, rx, ly, ry);
	}

	// receives max number of updates
	// each update creates at most logN logM nodes
	// RTE if we reserve less than number of nodes created
	void init(int maxu) {
		v.reserve(400*maxu);
		v.emplace_back();
		build(1, 0, N-1);
	}
}
