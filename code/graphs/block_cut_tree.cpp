// Builds forest of block cut trees for an UNDIRECTED graph
// Constructor: SCC(|V|, |E|, [[v, e]; |V|])
// Complexity: O(N+M)
// be9e10
struct BlockCutTree {
	int ncomp; // number of components
	vector<int> comp; // comp[e]: component of edge e
	vector<vector<int>> gart; // gart[v]: list of components an articulation point v is adjacent to
			          // if v is NOT an articulation point, then gart[v] is empty
				
	template <typename E> // assumes auto [neighbor_vertex, edge_id] = g[current_vertex][i]
	BlockCutTree(int n, int m, vector<E> g[]): ncomp(0), comp(m), gart(n) {
		vector<bool> vis(n), vise(m);
		vector<int> low(n), prof(n);
		stack<pair<int,int>> st;

		auto dfs = [&](auto& self, int v, bool root = 0) -> void {
			vis[v] = 1;
			int arb = 0; // arborescences
			for(auto [p, e]: g[v]) if(!vise[e]) {
				vise[e] = 1;
				int in = st.size();
				st.emplace(e, vis[p] ? -1 : p);
				if(!vis[p]) {
					arb++;
					low[p] = prof[p] = prof[v] + 1;
					self(self, p);
					low[v] = min(low[v], low[p]);
				} else low[v] = min(low[v], prof[p]);
				if(low[p] >= prof[v]) {
					gart[v].push_back(ncomp);
					while(st.size() > in) {
						auto [es, ps] = st.top();
						comp[es] = ncomp;
						if(ps != -1 && !gart[ps].empty())
							gart[ps].push_back(ncomp);
						st.pop();
					}
					ncomp++;
				}
			}
			if(root && arb <= 1) gart[v].clear();
		};
		for(int v=0;v<n;v++) if(!vis[v]) dfs(dfs, v, 1);
	}
};
