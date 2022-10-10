// 4d58fb
struct LCA {
	vector<int> t; // preorder traversal
	RMQ<pair<int,int>> rmq;

	LCA() {}
	LCA(int sz, vector<int> g[], int root): t(sz) {
		vector<pair<int,int>> tour; tour.reserve(2*sz-1);
		vector<int> prof(sz); 
		auto dfs = [&](int v, int dad, auto& self) -> void {
			t[v] = tour.size();
			tour.push_back({prof[v],v});
			for(int p: g[v]) if(p != dad) {
				prof[p] = prof[v]+1;
				self(p,v,self);
				tour.push_back({prof[v],v});
			}
		};
		dfs(root, root, dfs);
		rmq = RMQ<pair<int,int>>(tour);
	}

	int query(int a, int b) {
		if(t[a] > t[b]) swap(a,b);
		return rmq.query(t[a],t[b]).second;
	}
};
