// Kosaraju
// comp[u]: component of vertex u
// The graph of components is a DAG where
// there is only edges i -> j where i < j
struct Kosaraju {
	int ncomp;
	vector<int> comp;

	Kosaraju(int n, vector<int> g[]): ncomp(0), comp(n, -1) {
		vector<vector<int>> grev(n);
		for(int u=0;u<n;u++) for(int v: g[u])
			grev[v].push_back(u);
		vector<bool> vis(n);
		vector<int> ord;
		function<void(int)> dfs = [&](int u) {
			vis[u] = true;
			for(int v: g[u]) if(not vis[v])
				dfs(v);
			ord.push_back(u);
		};
		for(int u=0;u<n;u++) if(not vis[u])
			dfs(u);
		reverse(ord.begin(), ord.end());
		function<void(int, int)> paint = [&](int u, int c) {
			comp[u] = c;
			for(int v: grev[u]) if(comp[v] == -1)
				paint(v, c);
		};
		for(int u: ord) if(comp[u] == -1)
			dfs(u, ncomp++);
	}
};
