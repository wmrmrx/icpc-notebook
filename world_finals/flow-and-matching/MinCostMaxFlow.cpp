//  If costs can be negative, call setpi before maxflow, but note that negative cost cycles are not supported.
//  To obtain the actual flow, look at positive values only.
// Time: $O(F E \log(V))$ where F is max flow. $O(VE)$ for setpi.
//INSERT RIGHT AFTER THE INCLUDE BELOW <bits/stdc++.h>
//#include <ext/pb_ds/priority_queue.hpp>
struct MCMF {
	static constexpr ll INF = numeric_limits<ll>::max() / 4;
	struct edge {
		int from, to, rev;
		ll cap, cost, flow;
	};
	int n;
	vector<vector<edge>> ed;
	vector<int> seen;
	vector<ll> dist, pi;
	vector<edge*> par;
	MCMF(int _n) : n(_n), ed(_n), seen(_n), dist(_n), pi(_n), par(_n) {}
	void add_edge(int u, int v, ll cap, ll cost) {
		if (u == v) return;
		int id_u = ed[u].size();
		int id_v = ed[v].size();
		ed[u].emplace_back( u, v, id_v, cap, cost, 0 );
		ed[v].emplace_back( v, u, id_u, 0, -cost, 0 );
	}
	void path(int s) {
		fill(all(seen), 0);
		fill(all(dist), INF);
		dist[s] = 0; ll di;
		__gnu_pbds::priority_queue<pair<ll, int>> q;
		vector<decltype(q)::point_iterator> its(n);
		q.push({ 0, s });
		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (edge& e : ed[s]) if (!seen[e.to]) {
				ll val = di - pi[e.to] + e.cost;
				if (e.cap - e.flow > 0 && val < dist[e.to]) {
					dist[e.to] = val;
					par[e.to] = &e;
					if (its[e.to] == q.end()) its[e.to] = q.push({ -dist[e.to], e.to });
					else q.modify(its[e.to], { -dist[e.to], e.to });
				}
			}
		}
		for(int i = 0; i < n; i++) pi[i] = min(pi[i] + dist[i], INF);
	}
	pair<ll, ll> max_flow(int s, int t) {
		ll totflow = 0, totcost = 0;
		while (path(s), seen[t]) {
			ll fl = INF;
			for (edge* x = par[t]; x; x = par[x->from])
				fl = min(fl, x->cap - x->flow);
			totflow += fl;
			for (edge* x = par[t]; x; x = par[x->from]) {
				x->flow += fl;
				ed[x->to][x->rev].flow -= fl;
			}
		}
		for(int i = 0; i < n; i++) for(edge& e : ed[i])
			totcost += e.cost * e.flow;
		return {totflow, totcost/2};
	}
	// If some costs can be negative, call this before maxflow:
	void setpi(int s) { // (otherwise, leave this out)
		fill(all(pi), INF); pi[s] = 0;
		int it = n, ch = 1; ll v;
		while (ch-- && it--)
			for(int i = 0; i < n; i++) if (pi[i] != INF)
			  for (edge& e : ed[i]) if (e.cap)
				  if ((v = pi[i] + e.cost) < pi[e.to])
					  pi[e.to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};
