// Sparse Persistent Segment Tree
//
// cap: maximum number of nodes created
// if PERSISTENCE = false, cap can be 2 * n
//
// op = 0 is the initial state
// op = 1 is the state after 1 update call, and so on
// TESTED: https://codeforces.com/contest/837/submission/249394518

template <typename Info, bool PERSISTENCE = true, typename T = typename Info::T>
class Seg {
private: 
	int n, ptr, cap;
	vector<Info> info;
	vector<array<int, 2>> ch;
	vector<int> root;

	void copy(int& dst) {
		int src = dst;
		if(!src) {
			// assert(ptr + 1 < cap);
			dst = ++ptr;
			info[dst] = Info();
			ch[dst] = {0, 0};
		} else if(PERSISTENCE) {
			// assert(ptr + 1 < cap);
			dst = ++ptr;
			info[dst] = info[src];
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

	Info query(int nid, int l, int r, int ql, int qr) {
		if(!nid || qr < l || r < ql) return Info();
		if(ql <= l && r <= qr) return info[nid];
		int m = (l + r) / 2;
		auto [x, y] = ch[nid];
		return query(x, l, m, ql, qr) + query(y, m+1, r, ql, qr);
	}

	void update(int& nid, int l, int r, int pos, T val) {
		copy(nid);
		if(l == r) return void(info[nid] = Info(val));
		int m = (l + r)/2;
		auto &[x, y] = ch[nid];
		if(pos <= m) update(x, l, m, pos, val);
		else update(y, m+1, r, pos, val);
		info[nid] = info[x] + info[y];
	}
public:
	Seg(vector<T>& v, int cap_ = -1): n(v.size()), ptr(0), 
		cap(PERSISTENCE ? cap_ : 2 * n), info(cap), ch(cap), root{0} {
		build(root[0], 0, n-1, v);
	}

	Seg(int n_, int cap_ = -1): n(n_), ptr(0), 
		cap(PERSISTENCE ? cap_ : 2 * n), info(cap), ch(cap), root{0} {}

	Info query(int ql, int qr, int op = -1) {
		if(op == -1) op = root.size() - 1;
		return query(root[op], 0, n-1, ql, qr);
	}

	int update(int pos, T val, int op = -1) {
		if(op == -1) op = root.size() - 1;
		root.pb(root[op]);
		update(root.back(), 0, n-1, pos, val);
		return root.size() - 1;
	}
};

// CHANGE HERE
struct Info {
	using T = int;
	int mn;
	Info(): mn(numeric_limits<T>::max() / 2) {}
	Info(T val): mn(val) {}
	friend Info operator+(Info lhs, Info rhs) {
		Info res(min(lhs.mn, rhs.mn));
		return res;
	}
};
