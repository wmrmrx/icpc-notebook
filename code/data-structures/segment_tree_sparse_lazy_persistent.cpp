// Sparse Lazy Persistent Segment Tree 
// op = 0 is the initial state
// op = 1 is the state after 1 update call, and so on

template <typename Info, typename T = typename Info::T, typename U = typename Info::U, typename Tag = typename Info::Tag> 
class SegLazy {
private: 
	int n, ptr, cap;
	vector<Info> info;
	vector<Tag> tag;
	vector<array<int, 2>> ch;
	vector<int> root;

	void copy(int& dst) {
		int src = dst;
		assert(ptr < cap);
		if(src == -1) {
			dst = ptr++;
			info[dst] = Info();
			tag[dst] = Tag();
			ch[dst] = {-1, -1};
		} else {
			dst = ptr++;
			info[dst] = info[src];
			tag[dst] = tag[src];
			ch[dst] = ch[src];
		}
	}

	void build(int& nid, int l, int r, vector<T>& v) {
		copy(nid);
		if(l == r) return void(info[nid] = Info(v[l]));
		int m = (l + r) / 2;
		auto &[x, y] = ch[nid];
		build(x, l, m, v);
		build(y, m+1, r, v);
		info[nid] = info[x] + info[y];
	}

	void push(int nid, int l, int r) {
		// optimization: return if tag[nid] is null
		info[nid] = tag[nid].apply(info[nid], l, r);
		if(l != r) for(int &c: ch[nid]) {
			copy(c);
			tag[c] += tag[nid];
		}
		tag[nid] = Tag();
	}

	Info query(int& nid, int l, int r, int ql, int qr) {
		if(nid == -1 || qr < l || r < ql) return Info();
		if(ql <= l && r <= qr) return tag[nid].apply(info[nid], l, r);
		push(nid, l, r);
		int m = (l + r) / 2;
		auto &[x, y] = ch[nid];
		return query(x, l, m, ql, qr) + query(y, m+1, r, ql, qr);
	}

	Info update(int nid, int l, int r, int ql, int qr, U val) {
		if(qr < l || r < ql) return tag[nid].apply(info[nid], l, r);
		if(ql <= l && r <= qr) { 
			tag[nid] += Tag(val);
			return tag[nid].apply(info[nid], l, r);
		}
		push(nid, l, r);
		int m = (l + r)/2;
		auto &[x, y] = ch[nid];
		return info[nid] = update(x, l, m, ql, qr, val) + update(y, m+1, r, ql, qr, val);
	}
public:
	SegLazy(vector<T>& v, int cap_): n(v.size()), cap(cap_), info(cap), tag(cap), ch(cap) {
		root.reserve(cap_);
		root.pb(-1);
		build(root[0], 0, n-1, v);
	}

	SegLazy(int n_, int cap_): n(n_), cap(cap_), info(cap), tag(cap), ch(cap) {
		root.reserve(cap_);
		root.pb(-1);
	}

	Info query(int ql, int qr, int op = -1) {
		if(op == -1) op = root.size() - 1;
		return query(root[op], 0, n-1, ql, qr);
	}

	int update(int ql, int qr, U val, int op = -1) {
		if(op == -1) op = root.size() - 1;
		root.pb(root[op]);
		copy(root.back());
		update(root.back(), 0, n-1, ql, qr, val);
		return root.size() - 1;
	}
};

// CHANGE HERE
struct Info {
	using T = int;
	int mn;
	Info(): mn(numeric_limits<T>::max()) {}
	Info(T val): mn(val) {}
	friend Info operator+(Info lhs, Info rhs) {
		Info res(min(lhs.mn, rhs.mn));
		return res;
	}

	using U = int;
	struct Tag {
		int tag;
		Tag(): tag(0) {}
		Tag(U val): tag(val) {}
		void operator+=(Tag rhs) {
			tag += rhs.tag;
		}
		Info apply(Info info, int l, int r) {
			info.mn += tag;
			return info;
		}
	};
};