// Implicit Lazy Treap

// All operations are O(log N)
// If changes need to be made in lazy propagation,
// See Node::push()
// To extend behavior of Treap, use inheritance
//
// Important functions:
// Treap::insert(int ind, T info)
// Treap::erase(int ind)
// Treap::reverse(int l, int r)
// Treap::operator[](int ind)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename ND, typename T = typename ND::T> 
struct Treap {
	ND *root;
	vector<ND> v;
	// max: maximum number of NDs created
	Treap(int max): root(0) {
		v.reserve(max);
	}
	ND* new_node(T info) {
		// assert(v.size() != v.capacity());
		v.emplace_back(info);
		return &v.back();
	}
	int getl(ND& nd) {
		return nd.l ? nd.l->sz : 0;
	}
	void merge(ND* l, ND* r, ND*& res) {
		if(!l || !r) {
			res = l ? l : r;
			return;
		}
		l->push(); r->push();
		if(l->h > r->h) {
			res = l;
			merge(l->r, r, l->r);
		} else {
			res = r;
			merge(l, r->l, r->l);
		}
		res->pull();
	}
	// left treap has size pos
	void split(ND* x, ND*& l, ND*& r, int pos, int ra = 0) {
		if(!x) {
			l = r = 0;
			return;
		}
		x->push();
		int nra = ra + getl(*x) + 1;
		if(pos < nra) {
			split(x->l, l, r, pos, ra);
			x->l = r;
			r = x;
		} else {
			split(x->r, l, r, pos, nra);
			x->r = l;
			l = x;
		}
		x->pull();
	}
	// Merges all s and makes them root
	template <int SZ>
	void merge(array<ND*, SZ> s) {
		root = 0;
		for(ND* nd: s)
			merge(root, nd, root);
	}
	// Splits root into SZ EXCLUSIVE intervals
	// [0..s[0]), [s[0]..s[1]), [s[1]..s[2])... [s[SZ-1]..end)
	// Example: split<3>({l, r}) gets the exclusive interval [l, r)
	template <int SZ> 
	array<ND*, SZ> split(array<int, SZ-1> s) {
		assert(s.back() <= (root ? root->sz : 0));
		array<ND*, SZ> res;
		split(root, res[0], res[1], s[0]);
		for(int i=1;i<SZ-1;i++)
			split(res[i], res[i], res[i+1], s[i]-s[i-1]);
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
	T operator[](int ind) {
		assert(0 <= ind && ind < root->sz);
		ND* x = root;
		x->push();
		for(int ra = 0, nra = getl(*x); nra != ind; nra = ra + getl(*x)) {
			if(nra < ind) ra = nra + 1, x = x->r;
			else x = x->l;
			x->push();
		}
		return x->info;
	}
};

struct Node {
	using T = int;
	T info;
	Node *l, *r;
	int sz;
	uint64_t h;
	// more fields here - example: reverse interval
	bool rev;
	Node(T i): info(i), l(0), r(0), sz(1), h(rng()), rev(false) {}
	void push() {
		// example: reverse interval
		if(rev) {
			swap(l, r);
			for(auto c: {l, r})
				if(c) c->rev = !c->rev;
			rev = false;
		}
	}
	void pull() {
		sz = 1;
		for(auto c: {l, r}) 
			if(c) sz += c->sz;
	}
};

struct MyTreap : Treap<Node> {
	MyTreap(int max): Treap<Node>(max) {}
	// new methods here - example: reverse interval
	void reverse(int l, int r) {
		auto s = split<3>({l, r+1});
		s[1]->rev = !s[1]->rev;
		merge<3>(s):
	}
};
