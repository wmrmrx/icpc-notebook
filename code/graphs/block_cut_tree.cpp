// TODO: TESTAR
//
// Builds forest of block cut trees for an UNDIRECTED graph
// Constructor: SCC(|V|, |E|, [[v, e]; |V|])
// Complexity: O(N+M)
// ea9e08
struct BlockCutTree {
	vector<bool> art; // art[v]: true if v is an articulation point
	vector<int> comp; // comp[e]: component of edge e

	int ncomp; // number of components
	vector<int> sz; // sz[c]: size of component c (number of edges)
	vector<vector<int>> gc; // gc[c]: list of articulation points a component c is adjacent to
	vector<vector<int>> gart; // gart[v]: list of components an articulation point v is adjacent to
				  // if v is NOT an articulation point, then gart[v] is empty
				
	template <typename E>
	BlockCutTree(int n, int m, vector<E> g[]): art(n), comp(m, -1), ncomp(0), gart(n) {
		vector<bool> vis(n), vise(m);
		vector<int> low(n), prof(n);
		vector<pair<int,int>> st;

		auto dfs = [&](auto& self, int v, bool root = 0) -> void {
			vis[v] = 1;
			int arb = 0; // arborescences
			for(auto [p, e]: g[v]) if(!vise[e]) {
				vise[e] = 1;
				int in = st.size();
				st.emplace_back(e, vis[p] ? -1 : p);
				if(!vis[p]) {
					arb++;
					low[p] = prof[p] = prof[v] + 1;
					self(self, p);
					low[v] = min(low[v], low[p]);
				} else low[v] = min(low[v], prof[p]);
				if(low[p] >= prof[v]) {
					art[v] = 1;
					gart[v].push_back(ncomp);
					sz.push_back(0);
					while(st.size() > in) {
						auto [es, ps] = st.back();
						sz[ncomp]++;
						comp[es] = ncomp;
						if(ps != -1 && art[ps])
							gart[ps].push_back(ncomp);
						st.pop_back();
					}
					ncomp++;
				}
			}
			if(root && arb <= 1) {
				art[v] = false;
				gart[v].clear();
			}
		};
		for(int v=0;v<n;v++) if(!vis[v]) dfs(dfs, v, 1);

		gc.resize(ncomp);
		for(int v=0;v<n;v++) for(int c: gart[v]) gc[c].push_back(v);
	}
};
