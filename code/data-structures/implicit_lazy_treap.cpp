// All operations are O(log N)
// If changes need to be made in lazy propagation,
// see Treap::reverse() and change Treap::no::prop()
//
// Important functions:
// Treap::insert(T val, int idx)
// Treap::erase(int idx)
// Treap::reverse(int l, int r)
// Treap::operator[](int idx)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// HASH FROM HERE:
// c018fe
template <typename T>
struct Treap {
	struct no {
		array<no*, 2> c;
		T dat;
		int cnt, h;

		// Example: reverse interval
		bool rev;

		no(T dat=T()): c({0, 0}), dat(dat), cnt(1), h(rng()), rev(0) {}

		// propagate
		void prop() {
			if(rev) {
				swap(c[0], c[1]);
				for(no* x: c) if(x) x->rev = !x->rev;
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

	int sz;
	no *root;
	unique_ptr<no[]> arena;

	// prealloc: number of new_no() calls that will be made in total
	Treap(int prealloc): sz(0), root(0), arena(new no[prealloc]) {}

	no* new_no(T dat) {
		arena[sz] = no(dat);
		return &arena[sz++];
	}

	int cnt(no* x) { return x ? x->cnt : 0; }

	void merge(array<no*, 2> c, no*& res) {
		if(!c[0] || !c[1]) {
			res = c[0] ? c[0] : c[1];
			return;
		}
		for(no* x: c) x->prop();
		int i = c[0]->h < c[1]->h;
		no *l = c[i]->c[!i], *r = c[!i];
		if(i) swap(l, r);
		merge({l, r}, c[i]->c[!i]);
		res = c[i]->ref();
	}

	// left treap has size pos
	void split(no* x, int pos, array<no*, 2>& res, int ra = 0) {
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

	// Merges all s and makes them root
	template <int SZ>
	void merge(array<no*, SZ> s) {
		root = s[0];
		for(int i=1;i<SZ;i++)
			merge({root, s[i]}, root);
	}

	// Splits root into SZ EXCLUSIVE intervals
	// [0..s[0]), [s[0]..s[1]), [s[1]..s[2])... [s[SZ-1]..end)
	// Example: split<2>({l, r}) gets the exclusive interval [l, r)
	template <int SZ>
	array<no*, SZ> split(array<int, SZ-1> s) {
		array<no*, SZ> res;
		array<no*, 2> aux;
		split(root, s[0], aux);
		res[0] = aux[0]; res[1] = aux[1];
		for(int i=1;i<SZ-1;i++) {
			split(res[i], s[i]-s[i-1], aux);
			res[i] = aux[0]; res[i+1] = aux[1];
		}
		root = nullptr;
		return res;
	}

	void insert(T val, int idx) {
		auto s = split<2>({idx});
		merge<3>({s[0], new_no(val), s[1]});
	}
	
	void erase(int idx) {
		auto s = split<3>({idx, idx+1});
		merge<2>({s[0], s[2]});
	}

	// Inclusive
	void reverse(int l, int r) {
		auto s = split<3>({l, r+1});
		s[1]->rev = !s[1]->rev;
		merge<3>(s);
	}

	T operator[](int idx) {
		no* x = root;
		//assert(0 <= idx && idx < x->cnt);
		x->prop();
		for(int ra = x->l(); ra != idx; ra += x->l()) {
			if(ra < idx) ra++, x = x->c[1];
			else ra -= x->l(), x = x->c[0];
			x->prop();
		}
		return x->dat;
	}
};
