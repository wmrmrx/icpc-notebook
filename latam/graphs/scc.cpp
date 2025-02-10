// Tarjan for undirected graphs
// Builds forest of strongly connected components for an UNDIRECTED graph
// Constructor: SCC(|V|, |E|, [[v, e]; |V|])
//
// Complexity: O(N+M)

struct SCC {
	vector<bool> bridge; // bridge[e]: true if edge e is a bridge
	vector<int> comp; // comp[v]: component of vertex v

	int ncomp; // number of components
	vector<int> sz; // sz[c]: size of component i (number of vertexes)
	vector<vector<pair<int, int>>> gc; // gc[i]: list of adjacent components
				
	// assumes auto [neighbor_vertex, edge_id] = g[current_vertex][i]
	SCC(int n, int m, vector<pair<int, int>> g[]): bridge(m), comp(n, -1), ncomp(0) {
		vector<bool> vis(n);
		vector<int> low(n), prof(n);

		function<void(int,int)> dfs = [&](int v, int dad) {
			vis[v] = 1;
			for(auto [p, e]: g[v]) if(e != dad) {
				if(!vis[p]) {
					low[p] = prof[p] = prof[v] + 1;
					dfs(p, e);
					low[v] = min(low[v], low[p]);
				} else low[v] = min(low[v], prof[p]);
			}
			if(low[v] == prof[v]) ncomp++;
		};
		for(int i=0;i<n;i++) if(!vis[i]) dfs(i, -1);

		sz.resize(ncomp); gc.resize(ncomp);

		int cnt = 0;
		function<void(int,int)> build = [&](int v, int c) {
			if(low[v] == prof[v]) c = cnt++;
			comp[v] = c;
			sz[c]++;
			for(auto [p, e]: g[v]) if(comp[p] == -1) {
				build(p, c);
				int pc = comp[p];
				if(c != pc) {
					bridge[e] = true;
					gc[c].emplace_back(pc, e);
					gc[pc].emplace_back(c, e);
				}
			}
		};
		for(int i=0;i<n;i++) if(comp[i] == -1) build(i, -1);
	}
};
