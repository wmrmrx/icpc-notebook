// Dinitz
// add_edge(s, t, cap): Adds a directed edge from s to t with capacity cap
// get_flow(s, t): Returns max flow with source s and sink t
//
// Complexity: O(E*V^2). If unit edges only: O(E*sqrt(V))

bool zero(int x) {
	return x == 0;
}
bool zero(double x) {
	return abs(x) < (1e-6);
}

template<typename F>
struct Dinic {
	static constexpr F INF = numeric_limits<F>::max();
	struct edge {
		int to;
		F cap, flow;
		F f() { return cap - flow; }
	};

	int n, s, t;
	vector<vector<int>> adj;
	vector<int> lvl;
	vector<edge> g;

	Dinic(int sz): n(sz), adj(sz), lvl(sz) {}

	void add_edge(int u, int v, F cap) {
		int id = g.size();
		g.pb({v, cap, 0});
		g.pb({u, cap, cap});
		adj[u].pb(id);
		adj[v].pb(id+1);
	}

	F dfs(int u, F pool, vector<int>& ptr) {
		if(zero(pool) || u == t) return pool;
		for(auto &i = ptr[u]; i < int(adj[u].size()); i++) {
			int id = adj[u][i];
			auto &e = g[id];
			if( lvl[u] + 1 != lvl[e.to] || zero(e.f()) ) continue;
			F f;
			if(not zero( f = dfs(e.to, min(e.f(), pool), ptr) )) {
				g[id].flow += f;
				g[id^1].flow -= f;
				return f;
			}
		}
		return 0;
	}

	F get_flow(int _s, int _t) {
		//reset to initial state
		//for(int i=0;i<e.size();i++) e[i].flow = (i&1) ? e[i].cap : 0;
		s = _s; t = _t;
		F ret = 0;
		vector<int> ptr(n), q(n);
		do {
			fill(all(lvl), 0);
			lvl[s] = 1;
			int qi = 0, qe = 1;
			q[0] = s;
			while(qi < qe && !lvl[t]) {
				int u = q[qi++];
				for(int id: adj[u]) {
					auto &e = g[id];
					if( !lvl[e.to] && not zero(e.f()) )
						q[qe++] = e.to, lvl[e.to] = lvl[u] + 1;
				}
			}
			F f;
			fill(all(ptr), 0);
			while(not zero( f = dfs(s, INF, ptr) ) ) 
				ret += f;
		} while(lvl[t]);
		return ret;
	}
};
