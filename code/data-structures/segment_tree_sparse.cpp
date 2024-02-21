// Sparse Segment Tree
// 
// Build:
// 	SegSparse<Info> seg(max_coord, max_capacity)
//
// max_capacity should be at least (number of operations) * (log max_coord)
//
// Operations:
//      seg.query(int l, int r)
//      seg.update(int pos, T val)
//
// Submission: UNTESTED 
// Complexity: O(log max_coord) all operations

template <typename Info, typename T = typename Info::T>
struct SegSparse {
	int n, cap;
	vector<Info> info;
	vector<int> x, y; // left and right childs

	SegSparse(int _n, int mx): n(_n), cap(1), info(mx), x(mx, -1), y(mx, -1) {}

	void create(int &nid) {
		if(nid == -1) {
			// assert(cap < info.size());
			nid = cap++;
		}
	}

	void push(int nid, int l, int r) {
		create(x[nid]);
		create(y[nid]);
	}

	Info qry(int nid, int l, int r, int ql, int qr) {
		if(nid == -1 || qr < l || r < ql) return Info();
		if(ql <= l && r <= qr) return info[nid];
		int m = (l + r) / 2;
		return qry(x[nid], l, m, ql, qr) + qry(y[nid], m + 1, r, ql, qr);
	}

	void upd(int nid, int l, int r, int pos, T val) {
		push(nid, l, r);
		if(l == r) {
#warning Replace or sum?
			info[nid] = info[nid] + Info(val);
			return;
		}
		int m = (l + r) / 2;
		if(pos <= m)
			upd(x[nid], l, m, pos, val);
		else
			upd(y[nid], m + 1, r, pos, val);
		info[nid] = info[x[nid]] + info[y[nid]];
	}

	Info query(int ql, int qr) {
		// assert(0 <= ql && ql <= qr && qr < n);
		return qry(0, 0, n-1, ql, qr);
	}

	void update(int pos, T val) {
		// assert(0 <= ql && ql <= qr && qr < n);
		upd(0, 0, n-1, pos, val);
	}
};

// Info implements point update and range query
// 	using SegSum = SegSparse<Info>;
// 	SegSum seg(1e9, 1e7);
// 	seg.update(123, 123);
// 	assert(seg.query(0, 1e9 - 1).sum == 123);
struct Info {
	using T = int;
	int sum;
	Info(): sum(0) {}
	Info(T val): sum(val) {}
	friend Info operator+(Info lhs, Info rhs) {
		Info res;
		res.sum = lhs.sum + rhs.sum;
		return res;
	}
};
