// Builds forest of strongly connected components for an UNDIRECTED graph
// Constructor: SCC(|V|, |E|, [[v, e]; |V|])
//
// Complexity: O(N+M)
// 3abbaa
struct SCC {
	vector<bool> bridge; // bridge[e]: true if edge e is a bridge
	vector<int> comp; // comp[v]: component of vertex v

	int ncomp; // number of components
	vector<int> sz; // sz[c]: size of component i (number of vertexes)
	vector<vector<pair<int, int>>> gc; // gc[i]: list of adjacent components
				
	SCC(int n, int m, vector<pair<int, int>> g[]): bridge(m), comp(n, -1), ncomp(0) {
		vector<bool> vis(n);
		vector<int> low(n), prof(n);

		auto dfs = [&](auto& self, int v, int dad = -1) -> void {
			vis[v] = 1;
			for(auto [p, e]: g[v]) if(p != dad) {
				if(!vis[p]) {
					low[p] = prof[p] = prof[v] + 1;
					self(self, p, v);
					low[v] = min(low[v], low[p]);
				} else low[v] = min(low[v], prof[p]);
			}
			if(low[v] == prof[v]) ncomp++;
		};
		for(int i=0;i<n;i++) if(!vis[i]) dfs(dfs, i);

		sz.resize(ncomp); gc.resize(ncomp);

		int cnt = 0;
		auto build = [&](auto& self, int v, int c = -1) -> void {
			if(low[v] == prof[v]) c = cnt++;
			comp[v] = c;
			sz[c]++;
			for(auto [p, e]: g[v]) if(comp[p] == -1) {
				self(self, p, c);
				int pc = comp[p];
				if(c != pc) {
					bridge[e] = true;
					gc[c].emplace_back(pc, e);
					gc[pc].emplace_back(c, e);
				}
			}
		};
		for(int i=0;i<n;i++) if(comp[i] == -1) build(build, i);
	}
};
