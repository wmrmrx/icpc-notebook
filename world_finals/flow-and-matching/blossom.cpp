// Blossom
// 1-based indexing
// If white[v] = 0 after solve() returns, v is part of every max matching
// ans is the size of the maximum matching
// Complexity: O(NM), faster in practice
#warning 1-based indexing
struct MaxMatching {
	int n, ans = 0;
	vector<vector<int>> adj;
	vector<int> mate, first;
	vector<bool> white;
	vector<pair<int,int>> label;
	MaxMatching(int _n, vector<pair<int,int>> edges): n(_n), adj(n+1), mate(n+1), first(n+1), white(n+1), label(n+1) {
		for(auto [u, v]: edges) adj[u].pb(v), adj[v].pb(u);
		for(int st = 1; st<=n; st++) if(!mate[st]) ans += augment(st);
	}
	int group(int x) { int &f = first[x]; return white[f] ? f = group(f) : f; }
	void match(int p, int b) {
		swap(b, mate[p]); if(mate[b] != p) return;
		auto [f, s] = label[p];
		if(!s) mate[b] = f, match(f, b);
		else match(f, s), match(s, f);
	}
	bool augment(int st) {
		white[st] = 1; first[st] = 0; label[st] = {0,0};
		queue<int> q; q.push(st);
		while (!q.empty()) {
			int a = q.front(); q.pop();
			for(auto &b: adj[a]) {
				if(white[b]) { 
					int x = group(a), y = group(b), lca = 0;
					while(x || y) {
						if(y) swap(x, y);
						if(label[x] == pair(a, b)) { lca = x; break; }
						label[x] = {a,b}; x = group(label[mate[x]].first);
					}
					for (int v: {group(a), group(b)}) while (v != lca) {
						q.push(v); white[v] = true; first[v] = lca;
						v = group(label[mate[v]].first);
					}
				} else if(not mate[b]) {
					mate[b] = a; match(a, b); fill(all(white), false);
					return true;
				} else if(not white[mate[b]]) {
					white[mate[b]] = true; first[mate[b]] = b;
					label[b] = {0,0}; label[mate[b]] = {a, 0};
					q.push(mate[b]);
				}
			}
		}
		return false;
	}
};
