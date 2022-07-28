// dc962c
constexpr int INF = numeric_limits<int>::max();
struct Dinic {
	struct edge {
		int to, cap, flow;
	};

	vector<vector<int>> g;
	vector<int> lvl;
	vector<edge> e;

	Dinic(int sz): g(sz), lvl(sz) {}

	void add_edge(int s, int t, int cap) {
		int id = e.size();
		g[s].push_back(id);
		e.push_back({t, cap, 0});
		g[t].push_back(++id);
		e.push_back({s, cap, cap});
	}

	bool BFS(int s, int t) {
		fill(lvl.begin(), lvl.end(), INF);
		lvl[s] = 0;
		queue<int> q{{s}};
		while(!q.empty() && lvl[t] == INF) {
			int cur = q.front();
			q.pop();
			for(int id: g[cur]) {
				int prox = e[id].to;
				if(lvl[prox] != INF || e[id].cap == e[id].flow)
					continue;
				lvl[prox] = lvl[cur] + 1;
				q.push(prox);
			}
		}
		return lvl[t] != INF;
	}

	int DFS(int v, int pool, int start[], int t) {
		if(!pool) return 0;
		if(v == t) return pool;
		for(;start[v]<(int)g[v].size();start[v]++) {
			int id = g[v][start[v]], prox = e[id].to;
			if(lvl[v]+1 != lvl[prox] || e[id].cap == e[id].flow) continue;
			int pushed = DFS(prox,min(e[id].cap-e[id].flow,pool),start,t);
			if(pushed) {
				e[id].flow += pushed;
				e[id^1].flow -= pushed;
				return pushed;
			}
		}
		return 0;
	}

	int max_flow(int s, int t) {
		int total_flow = 0;
		vector<int> start(g.size());
		while(BFS(s,t)) {
			fill(start.begin(), start.end(), 0);
			while(int pushed = DFS(s,INF,start.data(),t)) 
				total_flow += pushed;
		}
		//reset to initial state
		//for(int i=0;i<e.size();i++) e[i].flow = (i&1) ? e[i].cap : 0;
		return total_flow;
	}
};
