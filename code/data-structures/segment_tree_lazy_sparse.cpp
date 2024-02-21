// Sparse Lazy Segment Tree
// 
// Build:
// 	SegLazySparse<Info> seg(max_coord, max_capacity)
//
// max_capacity should be at least (number of operations) * (log max_coord)
//
// Operations:
//      seg.query(int l, int r)
//      seg.update(int l, int r, T val)

template <typename Info, typename T = typename Info::T, typename Tag = typename Info::Tag>
struct SegLazySparse {
	int n, cap;
	vector<Info> info;
	vector<Tag> tag;
	vector<int> x, y; // left and right childs

	SegLazySparse(int _n, int mx): n(_n), cap(1), info(mx), tag(mx), x(mx, -1), y(mx, -1) {}

	void create(int &nid) {
		if(nid == -1) {
			// assert(cap < info.size());
			nid = cap++;
		}
	}

	void push(int nid, int l, int r) {
		create(x[nid]); create(y[nid]);
		tag[nid].apply(info[nid], l, r);
		for(int c: {x[nid], y[nid]})
			tag[c] += tag[nid];
		tag[nid] = Tag();
	}

	Info qry(int nid, int l, int r, int ql, int qr) {
		push(nid, l, r);
		if(qr < l || r < ql) return Info();
		if(ql <= l && r <= qr) return info[nid];
		int m = (l + r) / 2;
		return qry(x[nid], l, m, ql, qr) + qry(y[nid], m + 1, r, ql, qr);
	}

	void upd(int nid, int l, int r, int ql, int qr, T val) {
		push(nid, l, r);
		if(qr < l || r < ql) return;
		if(ql <= l && r <= qr) {
			tag[nid] += Tag(val);
			push(nid, l, r);
			return;
		}
		int m = (l + r) / 2;
		upd(x[nid], l, m, ql, qr, val);
		upd(y[nid], m + 1, r, ql, qr, val);
		info[nid] = info[x[nid]] + info[y[nid]];
	}

	Info query(int ql, int qr) {
		// assert(0 <= ql && ql <= qr && qr < n);
		return qry(0, 0, n-1, ql, qr);
	}

	void update(const int ql, const int qr, T val) {
		// assert(0 <= ql && ql <= qr && qr < n);
		upd(0, 0, n-1, ql, qr, val);
	}
};

// Info implements range sum and range query
// 	using SegSum = SegLazySparse<Info>
// 	SegSum seg(1e9, 1e7)
// 	seg.update(0, 1e9 - 1, 1)
// 	assert(seg.query(0, 1e9 - 1).sum == 1e9)
struct Info {
	using T = int;
	int sum;
	Info(): sum(0) {}
	friend Info operator+(Info lhs, Info rhs) {
		Info res;
		res.sum = lhs.sum + rhs.sum;
		return res;
	}
	struct Tag {
		int sum;
		Tag(): sum(0) {}
		Tag(T val): sum(val) {}
		void operator+=(Tag rhs) {
			sum += rhs.sum;
		}
		void apply(Info& info, int l, int r) {
			info.sum += sum * (r - l + 1);
		}
	};
};
