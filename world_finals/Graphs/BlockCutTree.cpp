// Block Cut Tree
// Builds forest of block cut trees for an UNDIRECTED graph
// Constructor: SCC(|V|, |E|, [[v, e]; |V|])
// Complexity: O(N+M)

struct BlockCutTree {
	int ncomp; // number of components
	vector<int> comp; // comp[e]: component of edge e
	vector<vector<int>> gart; // gart[v]: list of components an articulation point v is adjacent to
			          // if v is NOT an articulation point, then gart[v] is empty
				
	// assumes auto [neighbor_vertex, edge_id] = g[current_vertex][i]
	BlockCutTree(int n, int m, vector<pair<int,int>> g[]): ncomp(0), comp(m), gart(n) {
		vector<bool> vis(n), vise(m);
		vector<int> low(n), prof(n);
		stack<pair<int,int>> st;

		function<void(int,bool)> dfs = [&](int v, bool root) {
			vis[v] = 1;
			int arb = 0; // arborescences
			for(auto [p, e]: g[v]) if(!vise[e]) {
				vise[e] = 1;
				int in = st.size();
				st.emplace(e, vis[p] ? -1 : p);
				if(!vis[p]) {
					arb++;
					low[p] = prof[p] = prof[v] + 1;
					dfs(p, 0);
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
		for(int v=0;v<n;v++) if(!vis[v]) dfs(v, 1);
	}
};
