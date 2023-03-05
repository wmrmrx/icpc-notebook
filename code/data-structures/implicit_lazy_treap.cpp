// Implicit Lazy Treap

// All operations are O(log N)
// If changes need to be made in lazy propagation,
// see Treap::push() and Treap::pull()
//
// Important functions:
// Treap::insert(int ind, T info)
// Treap::erase(int ind)
// Treap::reverse(int l, int r)
// Treap::operator[](int ind)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename T> struct Treap {
	struct node {
		T info;
		int l, r, sz;
		uint64_t h;
		bool rev;
		node() {}
		node(T _info): info(_info), l(0), r(0), sz(1), h(rng()), rev(0) {}
	};

	int root, ptr;
	unique_ptr<node[]> v;
	// max: maximum number of insertions
	Treap(int max): root(0), ptr(0), v(new node[max+1]) {
		// v[0] is a placeholder node such that v[0].sz = 0
		v[0].sz = 0;
	}

	void push(int nd) {
		node &x = v[nd];
		if(x.rev) {
			swap(x.l, x.r);
			v[x.l].rev ^= 1;
			v[x.r].rev ^= 1;
			x.rev = 0;
		}
	}
	void pull(int nd) {
		node& x = v[nd];
		x.sz = v[x.l].sz + v[x.r].sz + 1;
	}
	int new_node(T info) {
		v[++ptr] = node(info);
		return ptr;
	}
	int getl(int nd) {
		return v[v[nd].l].sz;
	}

	void merge(int l, int r, int& res) {
		if(!l || !r) {
			res = l + r;
			return;
		}
		push(l); push(r);
		if(v[l].h > v[r].h) {
			res = l;
			merge(v[l].r, r, v[l].r);
		} else {
			res = r;
			merge(l, v[r].l, v[r].l);
		}
		pull(res);
	}
	// left treap has size pos
	void split(int nd, int &l, int &r, int pos, int ra = 0) {
		if(!nd) {
			l = r = 0;
			return;
		}
		push(nd);
		if(pos <= ra + getl(nd)) {
			split(v[nd].l, l, r, pos, ra);
			v[nd].l = r;
			r = nd;
		} else {
			split(v[nd].r, l, r, pos, ra + getl(nd) + 1);
			v[nd].r = l;
			l = nd;
		}
		pull(nd);
	}

	// Merges all s and makes them root
	template <int SZ> void merge(array<int, SZ> s) {
		root = s[0];
		for(int i=1;i<SZ;i++)
			merge(root, s[i], root);
	}

	// Splits root into SZ EXCLUSIVE intervals
	// [0..s[0]), [s[0]..s[1]), [s[1]..s[2])... [s[SZ-1]..end)
	// Example: split<2>({l, r}) gets the exclusive interval [l, r)
	template <int SZ> array<int, SZ> split(array<int, SZ-1> s) {
		array<int, SZ> res;
		split(root, res[0], res[1], s[0]);
		for(int i=1;i<SZ-1;i++) {
			split(res[i], res[i], res[i+1], s[i]-s[i-1]);
		}
		root = 0;
		return res;
	}

	void insert(int ind, T info) {
		auto s = split<2>({ind});
		merge<3>({s[0], new_node(info), s[1]});
	}
	void erase(int ind) {
		auto s = split<3>({ind, ind+1});
		merge<2>({s[0], s[2]});
	}
	// Inclusive
	void reverse(int l, int r) {
		auto s = split<3>({l, r+1});
		v[s[1]].rev ^= 1;
		merge<3>(s);
	}
	T operator[](int ind) {
		int nd = root;
		//assert(0 <= ind && ind < x->sz);
		push(nd);
		for(int ra=0, nra=getl(nd); nra != ind; nra = ra + getl(nd)) {
			if(nra < ind) ra = nra + 1, nd = v[nd].r;
			else nd = v[nd].l;
			push(nd);
		}
		return v[nd].info;
	}
};
