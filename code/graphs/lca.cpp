// LCA

struct LCA {
	vector<int> pre, dep; // preorder traversal and depth
	RMQ<pair<int,int>> rmq;

	LCA() {}
	LCA(int sz, vector<int> g[], int root): pre(sz), dep(sz) {
		vector<pair<int,int>> tour; tour.reserve(2*sz-1);
		auto dfs = [&](int v, int dad, auto& self) -> void {
			pre[v] = tour.size();
			tour.push_back({dep[v],v});
			for(int p: g[v]) if(p != dad) {
				dep[p] = dep[v]+1;
				self(p,v,self);
				tour.push_back({dep[v],v});
			}
		};
		dfs(root, root, dfs);
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
