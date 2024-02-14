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
	};

	int n, s, t;
	vector<vector<int>> adj;
	vector<int> lvl;
	vector<edge> g;

	Dinic(int sz): n(sz), adj(sz), lvl(sz) {}

	void add_edge(int u, int v, F cap) {
		int id = g.size();
		adj[u].pb(id);
		adj[v].pb(++id);
		g.pb({v, cap, 0});
		g.pb({u, cap, cap});
	}

	bool bfs() {
		fill(all(lvl), n);
		lvl[s] = 0;
		queue<int> q;
		q.push(s);
		while(!q.empty() && lvl[t] == n) {
			int u = q.front();
			q.pop();
			for(int id: adj[u]) {
				auto [v, cap, flow] = g[id];
				if( lvl[v] != n || zero(cap - flow) )
					continue;
				lvl[v] = lvl[u] + 1;
				q.push(v);
			}
		}
		return lvl[t] != n;
	}

	F dfs(int u, F pool, vector<size_t>& st) {
		if(zero(pool)) return 0;
		if(u == t) return pool;
		for( ; st[u]<adj[u].size() ; st[u]++) {
			int id = adj[u][st[u]];
			auto &[v, cap, flow] = g[id];
			if( lvl[u] + 1 != lvl[v] || zero(cap - flow) ) continue;
			int f = dfs(v, min(cap-flow, pool) , st);
			if(f) {
				flow += f;
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
		F res = 0;
		vector<size_t> start(n);
		while(bfs()) {
			fill(all(start), 0);
			F f;
			while( not zero(f = dfs(s, INF, start)) )
				res += f;
		}
		return res;
	}
};
