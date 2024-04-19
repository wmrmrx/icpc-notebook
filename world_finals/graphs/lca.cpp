// LCA

struct LCA {
	vector<int> pre, dep; // preorder traversal and depth
	RMQ<pair<int,int>> rmq;

	LCA() {}
	LCA(int sz, vector<int> g[], int root): pre(sz), dep(sz) {
		vector<pair<int,int>> tour; tour.reserve(2*sz-1);
		function<void(int,int)> dfs = [&](int u, int dad) {
			pre[u] = tour.size();
			tour.emplace_back(dep[u], u);
			for(int v: g[u]) if(v != dad) {
				dep[v] = dep[u]+1;
				dfs(v, u);
				tour.emplace_back(dep[u], u);
			}
		};
		dfs(root, root);
		rmq = RMQ<pair<int,int>>(tour);
	}

	int query(int a, int b) {
		if(pre[a] > pre[b]) swap(a,b);
		return rmq.query(pre[a],pre[b]).second;
	}

	int dist(int a, int b) {
		int c = query(a,b);
		return dep[a] + dep[b] - 2*dep[c];
	}
};
