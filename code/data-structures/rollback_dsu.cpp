// Disjoint set union with rollback
// Operations are O(log N), rollback is O(1)
// fcb293
struct Dsu {
	vector<int> dad, sz, ops;

	Dsu(int n): dad(n), sz(n) {
		iota(all(dad), 0);
		fill(all(sz), 1);
	}

	int find(int v) {
		return v == dad[v] ? v : dad[v] = find(dad[v]);
	}

	void join(int u, int v) {
		u = find(u);
		v = find(v);
		if(u == v) {
			ops.push_back(-1);
		} else {
			if(sz[u] > sz[v]) swap(u, v);
			dad[u] = v;
			sz[v] += sz[u];
			ops.push_back(u);
		}
	}

	void rollback() {
		int u = ops.back();
		sz[dad[u]] -= sz[u];
		dad[u] = u;
		ops.pop_back();
	}
};
