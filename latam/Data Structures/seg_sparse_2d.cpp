//  Sparse Segtree 2D
//  Data structure that makes operation on a grid.
//  Grid of dimensions N x M
//
//  Operations:
//          update(x, y, val) <- update on point (x, y)
//          query(lx, rx, ly, ry) <- query on rectangle [lx..rx] x [ly..ry]
//
//  O(logNlogM) complexity per operation
//  O(N + UlogNlogM) memory, where U is the number of updates
//
//  Possible changes:
//      - O(UlogNlogM) memory: Make N axis sparse too
//
// https://codeforces.com/contest/1917/submission/239091648

namespace seg2d {
	// YOU ONLY NEED TO CHANGE THIS BLOCK
	const int N = 2e5, M = N;
	using T = int32_t;
	const T zero = 0; // INF if maintaining minimum, for example
	T merge(T a, T b) {
		return a + b;
	}

	struct Node {
		T s = zero;
		int l = 0, r = 0;
	};

	int root[2*N];
	vector<Node> v;

	void upd(int& no, int l, int r, int pos, T val) {
		if(not no) {
			no = v.size();
			//assert(no < v.capacity());
			v.emplace_back();
		}
#warning maybe v[no].s = val instead
		if(l == r) v[no].s = merge(v[no].s, val);
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

	void update(int x, int y, T val) {
		for(int p = x + N; p > 0; p /= 2)
			upd(root[p], 0, M-1, y, val);
	}

	T query(int lx, int rx, int ly, int ry) {
		T res = zero;
		int l = lx, r = rx;
		r++; // to make query inclusive
		for(l += N, r += N; l < r; l /= 2, r /= 2) {
			if(l&1) res = merge(res, qry(root[l++], 0, M-1, ly, ry));
			if(r&1) res = merge(res, qry(root[--r], 0, M-1, ly, ry));
		}
		return res;
	}
	
	// receives max number of updates
	// each update creates at most logN logM nodes
	// RTE if we reserve less than number of nodes created
	void init(int maxu) {
		v.reserve(400*maxu);
		v.emplace_back();
	}
};
