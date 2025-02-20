// Link/cut tree
// Description: manages dynamic connectivity and handles
// path sum queries and subtree sum queries
// Details: is 1-indexed.
// Complexity: O(lgn) amortized

template <class T>
struct SplayTree {
	struct Node {
		int child[2] = {0, 0}, p = 0;
		T sub = 0, vir = 0;	// sum of values in subtree, sum of values in virtual subtrees
		T path = 0, value = 0; // sum of path, node value
		bool rev = false;
	};

	vector<Node> t;

	SplayTree(int sz) : t(sz+1) {}

	void push(int u) {
		if (!u || !t[u].rev) return;
		int l = t[u].child[0], r = t[u].child[1];
		swap(t[u].child[0], t[u].child[1]);
		t[l].rev ^= 1, t[r].rev ^= 1;
		t[u].rev = 0;
	}

	void pull(int u) {
		int l = t[u].child[0], r = t[u].child[1];
		push(l); push(r);
		t[u].path = t[l].path + t[u].value + t[r].path;
		t[u].sub = t[l].sub + t[u].vir + t[u].value + t[r].sub;
	}

	// attaches u to v
	void attach(int u, int v, bool d) {
		t[u].child[d] = v; t[v].p = u; pull(u);
	}

	// -1 -> has no parent, 0 -> left child, 1 -> right child
	int dir(int u) {
		int p = t[u].p;
		if (!p) return -1;
		if (t[p].child[0] == u) return 0;
		return (t[p].child[1] == u? 1: -1);
	}

	void rotate(int u) {
		int p = t[u].p, pp = t[p].p,
			du = dir(u), dp = dir(p);
		attach(p, t[u].child[!du], du);
		attach(u, p, !du);
		if (~dp) attach(pp, u, dp);
		t[u].p = pp;
	}

	void splay(int u) {
		push(u);
		while (~dir(u)) {
			int p = t[u].p;
			assert(u != p);
			push(t[p].p); push(p); push(u); 
			int du = dir(u), dp = dir(p);
			if (~dp) rotate(du == dp? p: u);
			rotate(u);
		}
	}
};

struct LinkCut : SplayTree<ll> {
	using T = ll;

	LinkCut(int size) : SplayTree<T>(size) {}

	int access(int u) {
		int v = u, last = 0;
		for (; v; last = v, v = t[v].p) {
			splay(v); 
			// removing right child
			int &r = t[v].child[1];
			t[v].vir += t[r].sub;
			t[v].vir -= t[last].sub;
			r = last; pull(v);
		}
		return splay(u), last;
	}

	void make_root(int u) {
		access(u); t[u].rev ^= 1; 
	}

	void link(int u, int v) {
		make_root(u); access(v);
		t[v].vir += t[u].sub;
		t[u].p = v; pull(v);
	}

	void cut(int u, int v) {
		make_root(u); access(v);
		t[u].p = 0, t[v].child[0] = 0;
		pull(v);
	}

	int find_root(int u) {
		access(u); push(u);
		while (t[u].child[0]) {
			u = t[u].child[0]; push(u);
		}
		return u;
	}

	int lca(int u, int v) {
		if (u == v) return u;
		access(u); 
		int ret = access(v);
		return (t[u].p? ret: 0);
	}

	bool same(int u, int v) {
		return lca(u, v);
	}

	// sum of vertices in u's subtree when
	// v is a root
	T subtree(int u, int v) {
		make_root(v); access(u); return t[u].value + t[u].vir;
	}

	// sum of values in path [u...v]
	T path(int u, int v) {
		make_root(u); access(v); return t[v].path;
	}

	void update(int u, int x) {
		access(u); t[u].value = x; pull(u);
	}

	// jumps k vertices in path [u...v]
	// t[x].sub MUST be x's subtree size
	int jump(int u, int v, int k) {
		make_root(u); access(v); 
		if (k > t[u].sub) return 0;
		while (true) {
			push(v); pull(v);
			int rsz = 0;
			if (t[v].child[1]) rsz = t[t[v].child[1]].sub;

			if (k < rsz) {
				v = t[v].child[1];
				continue;
			}

			if (k == rsz) {
				break;
			}

			k -= rsz+1;
			v = t[v].child[0];
		}
		return splay(v), v;
	}
};
