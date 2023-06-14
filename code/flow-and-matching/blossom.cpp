// Blossom
// 1-based indexing
// If white[v] = 0 after solve() returns, v is part of every max matching
//
// Complexity: O(NM), faster in practice

struct MaxMatching {
	int n;
	vector<vector<int>> adj;
	vector<int> mate, first;
	vector<bool> white;
	vector<pair<int,int>> label;

	MaxMatching(int _n): n(_n), adj(n+1), mate(n+1), first(n+1), white(n+1), label(n+1) {}

	void add_edge(int u, int v) { adj[u].pb(v); adj[v].pb(u); }

	int group(int x) { return white[first[x]] ? first[x] = group(first[x]) ? first[x]; }

	void match(int p, int b) {
		swap(b, mate[p]); if(mate[b] != p) return;
		auto [f, s] = label[p];
		if(!s) mate[b] = f, match(f, b); // vertex label
		else match(f, s), match(s, f); // edge label
	}

	bool augment(int st) { // assert(st);
		white[st] = 1; first[st] = 0; label[st] = {0,0};
		queue<int> q; q.push(st);
		while (!q.empty()) {
			int a = q.front(); q.pop(); // outer vertex
			for(auto &b: adj[a]) { // assert(b);
				if (white[b]) { // two outer vertices, form blossom
					int x = group(a), y = group(b), lca = 0;
					while(x || y) {
						if(y) swap(x, y);
						if(label[x] == {a, b}) { lca = x; break; }
						label[x] = {a,b}; x = group(label[mate[x]].first);
					}
					for (int v: {group(a), group(b)}) while (v != lca) {
						// assert(!white[v]); // make everything along path white
						q.push(v); white[v] = true; first[v] = lca;
						v = group(label[mate[v]].first);
					}
				} else if (!mate[b]) { // found augmenting path
					mate[b] = a; match(a,b); white = vb(n+1); // reset
					return true;
				} else if (!white[mate[b]]) {
					white[mate[b]] = true; first[mate[b]] = b;
					label[b] = {0,0}; label[mate[b]] = pi{a,0};
					q.push(mate[b]);
				}
			}
		}
		return false;
	}
	int solve() {
		int ans = 0;
		for(int st=1; st<=n; st++) if(!mate[st]) ans += augment(st);
		// for(int st=1; st<=n; st++) if(!mate[st] && !white[st]) assert(!augment(st));
		return ans;
	}
};
