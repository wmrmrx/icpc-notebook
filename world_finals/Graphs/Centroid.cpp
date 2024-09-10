vector<int> g[MAXN];
int morto[MAXN], sz[MAXN];
void calc_sz(int u, int p){
	sz[u] = 1;
	for(int v : g[u]) if(v != p && !morto[v]){
		calc_sz(v,u);
		sz[u] += sz[v];
	}
}
int centroid(int u, int p, int tot){
	for(int v: g[u]) if(v != p && !morto[v]){
		if(sz[v]*2 > tot) return centroid(v,u,tot);
	}
	return u;
}
