// Push-Relabel / fast flow
// Description: Quickly calculate max flow in O(V^2 E)
// Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/PushRelabel.h
struct PushRelabel {
	struct edge {
		int dest, back;
		ll f, c;
	};
	vector<vector<edge>> g;
	vector<ll> ec;
	vector<edge*> cur;
	vector<vector<int>> hs; vector<int> H;
	PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}
 
	void add_edge(int s, int t, ll cap, ll rcap=0) {
		if (s == t) return;
		g[s].push_back({t, (int)g[t].size(), 0, cap});
		g[t].push_back({s, (int)g[s].size()-1, 0, rcap});
	}
 
	void add_flow(edge& e, ll f) {
		edge &back = g[e.dest][e.back];
		if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
		e.f += f; e.c -= f; ec[e.dest] += f;
		back.f -= f; back.c += f; ec[back.dest] -= f;
	}
	ll get_flow(int s, int t) {
		int v = g.size(); H[s] = v; ec[t] = 1;
		vector<int> co(2*v); co[0] = v-1;
		for(int i=0;i<v;i++) cur[i] = g[i].data();
		for (edge& e : g[s]) add_flow(e, e.c);
 
		for (int hi = 0;;) {
			while (hs[hi].empty()) if (!hi--) return -ec[s];
			int u = hs[hi].back(); hs[hi].pop_back();
			while (ec[u] > 0)
				if (cur[u] == g[u].data() + g[u].size()) {
					H[u] = 1e9;
					for (edge& e : g[u]) if (e.c && H[u] > H[e.dest]+1)
						H[u] = H[e.dest]+1, cur[u] = &e;
					if (++co[H[u]], !--co[hi] && hi < v)
						for(int i=0;i<v;i++) if (hi < H[i] && H[i] < v)
							--co[H[i]], H[i] = v + 1;
					hi = H[u];
				} else if (cur[u]->c && H[u] == H[cur[u]->dest]+1)
					add_flow(*cur[u], min(ec[u], cur[u]->c));
				else ++cur[u];
		}
	}
	bool left_of_min_cut(int a) { return H[a] >= g.size(); }
};
