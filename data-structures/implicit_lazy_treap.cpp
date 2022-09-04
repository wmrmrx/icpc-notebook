mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// HASH FROM HERE:
// 9ceeb0
template <typename T>
struct Treap {
	struct no {
		array<no*, 2> c;
		T dat;
		int cnt, h;

		// reverse interval
		bool rev;

		no(T dat=T()): c({0, 0}), dat(dat), cnt(1), h(rng()), rev(0) {}

		// propagate
		void prop() {
			if(rev) {
				swap(c[0], c[1]);
				for(no* x: c) if(x) x->rev ^= !x->rev;
				rev = 0;
			}
		}

		// refresh
		no* ref() {
			cnt = 1;
			for(no* x: c) if(x) {
				x->prop();
				cnt += x->cnt;
			}
			return this;
		}

		// left child size
		int l() {
			return c[0] ? c[0]->cnt : 0;
		}
	};

	using childs = array<no*, 2>;

	int sz;
	no *root;
	unique_ptr<no[]> arena;

	Treap(int mxsz): sz(0), root(0), arena(new no[mxsz]) {}

	no* new_no(T dat) {
		arena[sz] = no(dat);
		return &arena[sz++];
	}

	int cnt(no* x) { return x ? x->cnt : 0; }

	void merge(childs c, no*& res) {
		if(!c[0] || !c[1]) {
			res = c[0] ? c[0] : c[1];
			return;
		}
		for(int i: {0, 1}) c[i]->prop();
		int i = c[0]->h < c[1]->h;
		no *l = c[i]->c[!i], *r = c[!i];
		if(i) swap(l, r);
		merge({l, r}, c[i]->c[!i]);
		res = c[i]->ref();
	}

	// left treap has size pos
	void split(no* x, int pos, childs& res, int ra = 0) {
		if(!x) {
			res.fill(0);
			return;
		}
		x->prop();
		ra += x->l();
		int i = pos > ra;
		split(x->c[i], pos, res, ra+(i?1:-x->l()));
		x->c[i] = res[!i];
		res[!i] = x->ref();
	}

	void insert(T dat, int idx) {
		childs s;
		split(root, idx, s);
		merge({s[0], new_no(dat)}, root);
		merge({root, s[1]}, root);
	}

	void erase(int idx) {
		childs sl, sr;
		split(root, idx, sl);
		split(sl[1], 1, sr);
		merge({sl[0], sr[1]}, root);
	}

	T operator[](int idx) {
		no* x = root;
		x->prop();
		for(int ra = x->l(); ra != idx; ra += x->l()) {
			if(ra < idx) ra++, x = x->c[1];
			else ra -= x->l(), x = x->c[0];
			x->prop();
		}
		return x->dat;
	}

	void reverse(int l, int r) {
		array<no*, 2> sl, sr;
		split(root, l, sl);
		split(sl[1], r-l+1, sr);
		sr[0]->rev = !sr[0]->rev;
		merge({sl[0], sr[0]}, root);
		merge({root, sr[1]}, root);
	}
};
