// Mincost Max-Flow
// Solves the minimum-cost maximum-flow problem using spfa for the finding the incremental
// shortest paths. Useful when the edges costs are negative. 
// Infinite loop if there's a negative cycle.
//
// Constructor:
// MinCost(n, s, t)
// n - number of nodes in the flow graph.
// s - source of the flow graph.
// t - sink of the flow graph.
//
// Methods:
// - add_edge(u, v, cap, cost)
//   adds a directed edge from u to v with capacity 'cap' and cost 'cost'.
// - get_flow()
//   returns a pair of integers in which the first value is the maximum flow and the
//   second is the minimum cost to achieve this flow.
//
// Complexity: There are two upper bounds to the time complexity of getFlow
//              - O(max_flow * (E log V))
//              - O(V * E * (E log V))

struct MinCost {
	static constexpr int INF = 1e18;
	struct edge {
		int to, next, cap, cost;
	};
	int n, s, t;
	vector<int> first, prev, dist;
	vector<bool> queued;
	vector<edge> g;

	MinCost(int _n) : n(_n), first(n, -1), prev(n), dist(n), queued(n) {};

	void add_edge(int u, int v, int cap, int cost) {
		int id = g.size();
		g.pb({v, first[u], cap, cost});
		first[u] = id;
		g.pb({u, first[v], 0, -cost});
		first[v] = ++id;
	}

	bool augment() {
		fill(all(dist), INF);
		dist[s] = 0;
		queued[s] = 1;
		queue<int> q;
		q.push(s);
		while(!q.empty()) {
			int u = q.front(); 
			q.pop();
			queued[u] = 0;
			for(int e = first[u]; e != -1; e = g[e].next) {
				int v = g[e].to;
				int ndist = dist[u] + g[e].cost;
				if(g[e].cap > 0 && ndist < dist[v]) {
					dist[v] = ndist;
					prev[v] = e;
					if(!queued[v]) {
						q.push(v);
						queued[v] = 1;
					}
				}
			}
		}
		return dist[t] < INF;
		//UNCOMMENT FOR MIN COST WITH ANY FLOW (NOT NECESSARILY MAXIMUM)
		//return dist[t] < 0;
	}

	pair<int, int> get_flow(int _s, int _t) {
		s = _s; t = _t;
		//if multiple runs are needed (resets flow)
		//for(int i = 0; i < int(g.size()); i += 2) {
		//	int cap = g[i].cap + g[i+1].cap;
		//	g[i].cap = cap;
		//	g[i + 1].cap = 0;
		//}
		int flow = 0, cost = 0;
		while(augment()) {
			int cur = t, curf = INF;
			while(cur != s) {
				int e = prev[cur];
				curf = min(curf, g[e].cap);
				cur = g[e^1].to;
			}
			flow += curf; 
			cost += dist[t] * curf;
			cur = t;
			while(cur != s) {
				int e = prev[cur];
				g[e].cap -= curf;
				g[e^1].cap += curf;
				cur = g[e^1].to;
			}
		}
		return {flow, cost};
	}
};
