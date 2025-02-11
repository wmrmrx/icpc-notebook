// Binary lifting on a rooted tree
//
// Operations:
// jump(v, j): 
//   parent of v after jumping up j edges
//   jump(v, 0) = 0
// lca(a, b)
// dist(a, b)
struct BLift {
	vector<int> dep;
	vector<vector<int>> dp;

	BLift(int sz, vector<int> g[], int root): dep(sz) {
		int log = 32-__builtin_clz(sz);
		dp.assign(log, vector<int>(sz));
		function<void(int,int)> dfs = [&](int v, int dad) {
			dp[0][v] = dad;
			for(int p: g[v]) if(p != dad) {
				dep[p] = dep[v] + 1;
				dfs(p, v);
			}
		};
		dfs(root, root);
		for(int l=1;l<log;l++) {
			auto &cur = dp[l], &ant = dp[l-1];
			for(int i=0;i<sz;i++) 
				cur[i] = ant[ant[i]];
		}
	}

	int jump(int v, int j) {
		for(int l=0;l<(int)dp.size();l++) if(j&(1<<l))
			v = dp[l][v];
		return v;
	}

	int lca(int a, int b) {
		if(dep[a] < dep[b]) swap(a,b);
		a = jump(a, dep[a] - dep[b]);
		if(a == b) return a;
		for(int l=(int)dp.size()-1;l>=0;l--) 
			if(dp[l][a] != dp[l][b])
				a = dp[l][a], b = dp[l][b];
		return dp[0][a];
	}

	int dist(int a, int b) {
		return dep[a] + dep[b] - 2*dep[lca(a,b)];
	}
};
