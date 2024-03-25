// Heavy Light Decomposition
// if EDGE is true, the child of the edge represents it

template<typename SEG, bool EDGE> struct HLD {
	vector<int> dad, pos, in, out, h;
	// dad[u]: self-explaining
	// pos[k]: k-th vertex to be visited in dfs order
	// in[u], out[u]: time of visit in dfs of vertex u
	// h[u]: highest ancestor from same hld chain ("head")
	// 	 two vertices u and v are from the same chain iff h[u] == h[v]
	SEG seg;

	HLD(int n, vector<int> g[]): dad(n), pos(n), in(n), out(n), h(n), seg(n) {
		int t = -1;
		function<void(int)> dfs = [&](int u) {
			pos[ in[u] = ++t ] = u;
			int mx = -1;
			for(int &v: g[u]) if(v != dad[u]) {
				dad[v] = u;
				h[v] = g[u][0] == v ? h[u] : v;
				dfs(v);
				if(out[v] - in[v] > mx) 
					mx = out[v] - in[v], swap(g[u][0], v);
			}
			out[u] = t;
		};
		dfs(0); t = -1; dfs(0); // yes, twice 
	}

	// if EDGE == true, the child of an edge represents it
	template<typename T>
	void updade(int u, T val) {
		seg.update(in[u] + EDGE, val);
	}

	// If range update is needed, just replace seg.query with seg.update
	template<typename RES> 
	RES query_path(int u, int v) {
		RES res = RES();
		while(h[u] != h[v]) {
			if(in[h[u]] < in[h[v]]) swap(u, v);
			res = res + seg.query(in[h[u]], in[u]);
			u = dad[h[u]];
		}
		if(in[u] > in[v]) swap(u, v);
		// u is now the LCA of u and v
		if(in[u] + EDGE <= in[v]) 
			res = res + seg.query(in[u] + EDGE, in[v]);
		return res;
	}

	template<typename RES> 
	RES query_subtree(int u) {
		if(in[u] + EDGE <= out[u])
			return seg.query(in[u] + EDGE, out[u]);
		return RES();
	}
};
