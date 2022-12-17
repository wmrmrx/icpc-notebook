/* Solves the minimum-cost maximum-flow problem using spfa for the finding the incremental
 * shortest paths. Useful when the edges costs are negative.
 *
 * Constructor:
 * mcf(n, s, t)
 * n - number of nodes in the flow graph.
 * s - source of the flow graph.
 * t - sink of the flow graph.
 *
 * Methods:
 * - addEdge(u, v, cap, cost)
 *   adds a directed edge from u to v with capacity `cap` and cost `cost`.
 * - getFlow()
 *   returns a pair of integers in which the first value is the maximum flow and the
 *   second is the minimum cost to achieve this flow.
 *
 * Complexity: There are two upper bounds to the time complexity of getFlow
 *              - O(max_flow * (E log V))
 *              - O(V * E * (E log V))
 */

// 82e170
const int INF = 1e18;
struct mcf {
	int n, s, t, fl, cost;
	vector<int> first, prev, dist;
	vector<bool> queued;
	struct edge {
		int to, next, cap, cost;
		edge(int _to, int _next, int _cap, int _cost):
			to(_to), next(_next), cap(_cap), cost(_cost) {}
	};
	vector<edge> g;
	mcf() {}
	mcf(int _n, int _s,int _t) : n(_n), s(_s), t(_t), fl(0), cost(0),
		first(n, -1), prev(n), dist(n), queued(n) {
		g.reserve(n*n);
	};
	void add_edge(int u, int v, int cap, int cost) {
		g.emplace_back(v, cap, cost, first[u]);
		first[u] = g.size() - 1;
		g.emplace_back(u, 0, -cost, first[v]);
		first[v] = g.size() - 1;
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
	}
	pair<int, int> getFlow() {
		while(augment()) {
			int cur = t, curf = INF;
			while(cur != s) {
				int e = prev[cur];
				curf = min(curf, g[e].cap);
				cur = g[e^1].to;
			}
			fl += curf; 
			cost += dist[t] * curf;
			cur = t;
			while(cur != s) {
				int e = prev[cur];
				g[e].cap -= curf;
				g[e^1].cap += curf;
				cur = g[e^1].to;
			}
		}
		return {fl, cost};
	}
};
