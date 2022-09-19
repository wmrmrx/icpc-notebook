// TODO: TESTAR
//
// Builds forest of block cut trees for an UNDIRECTED graph
// Constructor: SCC(|V|, |E|, [[v, e]; |V|])
// Complexity: O(N+M)
// 66ba49
struct BlockCutTree {
	vector<bool> art; // art[v]: true if v is an articulation point
	vector<int> comp; // comp[e]: component of edge e

	int ncomp; // number of components
	vector<int> sz; // sz[c]: size of component c (number of edges)
	vector<vector<int>> gart; // gart[c]: list of articulation points a component c is adjacent to
	vector<vector<int>> gc; // gc[v]: list of components an articulation point v is adjacent to
				// if v is NOT an articulation point, then gc[v] is empty
				
	BlockCutTree(int n, int m, vector<pair<int, int>> g[]): art(n), comp(m, -1), ncomp(0), gc(n) {
		vector<bool> vis(n);
		vector<int> low(n), prof(n);

		auto dfs = [&](auto& self, int v, int dad = -1) -> void {
			vis[v] = 1;
			int cnt = 0;
			for(auto [p, id]: g[v]) if(p != dad) {
				if(!vis[p]) {
					cnt++;
					low[p] = prof[p] = prof[v] + 1;
					self(self, p, v);
					low[v] = min(low[v], low[p]);
				} else low[v] = min(low[v], prof[p]);
				if(dad != -1 && low[p] >= prof[v]) art[v] = true;
			}
			if(dad == -1 && cnt > 1) art[v] = true;
			if(dad == -1 || art[v]) ncomp += cnt;
		};
		for(int i=0;i<n;i++) if(!vis[i]) dfs(dfs, i);

		sz.resize(ncomp); gart.resize(ncomp);
		
		vector<bool> vise(m);
		int cnt = 0;
		vector<int> st;
		auto paint = [&](auto& self, int v, int dad = -1) -> void {
			vis[v] = 1;
			for(auto [p, e]: g[v]) if(!vise[e]) {
				int in = st.size();
				st.push_back(e);
				vise[e] = 1;
				if(!vis[p]) {
					self(self, p, v);
					if(art[v] || dad == -1) {
						while(st.size() > in) {
							comp[st.back()] = cnt;
							sz[cnt]++;
							st.pop_back();
						}
						cnt++;
					}
				}
			}
		};
		fill(all(vis), false);
		for(int i=0;i<n;i++) if(!vis[i]) paint(paint, i);

		auto build = [&](auto& self, int v, int dad = -1) -> void {
			vis[v] = 1;
			for(auto [p, e]: g[v]) if(!vis[p]) {
				int c = comp[e];
				for(int a: {p, v}) if(art[a]) {
					gc[a].push_back(c);
					gart[c].push_back(a);
				}
				self(self, p, v);
			}
		};
		fill(all(vis), false);
		for(int i=0;i<n;i++) if(!vis[i]) build(build, i);
	}
};
