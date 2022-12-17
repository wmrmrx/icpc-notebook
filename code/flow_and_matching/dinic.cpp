// add_edge(s, t, cap): Adds a directed edge from s to t with capacity cap
// get_flow(s, t): Returns max flow with source s and sink t
//
// Complexity: O(E*V^2). If unit edges only: O(E*sqrt(V))
// 360dcf
struct Dinic {
	const int INF = 1e18;
	struct edge {
		int to, cap, flow;
		edge(int _to, int _cap, int _flow): to(_to), cap(_cap), flow(_flow) {}
	};

	vector<vector<int>> g;
	vector<int> lvl;
	vector<edge> e;

	Dinic(int sz): g(sz), lvl(sz) {}

	void add_edge(int s, int t, int cap) {
		int id = e.size();
		g[s].push_back(id);
		e.emplace_back(t, cap, 0);
		g[t].push_back(++id);
		e.emplace_back(s, cap, cap);
	}

	bool bfs(int s, int t) {
		fill(all(lvl), INF);
		lvl[s] = 0;
		queue<int> q;
		q.push(s);
		while(!q.empty() && lvl[t] == INF) {
			int v = q.front();
			q.pop();
			for(int id: g[v]) {
				auto [p, cap, flow] = e[id];
				if(lvl[p] != INF || cap == flow)
					continue;
				lvl[p] = lvl[v] + 1;
				q.push(p);
			}
		}
		return lvl[t] != INF;
	}

	int dfs(int v, int pool, int t, vector<int>& st) {
		if(!pool) return 0;
		if(v == t) return pool;
		for(;st[v]<(int)g[v].size();st[v]++) {
			int id = g[v][st[v]];
			auto &[p, cap, flow] = e[id];
			if(lvl[v]+1 != lvl[p] || cap == flow) continue;
			int f = dfs(p, min(cap-flow, pool) , t, st);
			if(f) {
				flow += f;
				e[id^1].flow -= f;
				return f;
			}
		}
		return 0;
	}

	int get_flow(int s, int t) {
		//reset to initial state
		//for(int i=0;i<e.size();i++) e[i].flow = (i&1) ? e[i].cap : 0;
		int res = 0;
		vector<int> start(g.size());
		while(bfs(s,t)) {
			fill(all(start), 0);
			while(int f = dfs(s,INF,t,start)) 
				res += f;
		}
		return res;
	}
};
