// RMQ
//  Description: 
//      Answers queries on a range.
//  Complexity: 
// 		build - O(N logN)
// 		query - O(1)

template <typename T> struct RMQ {
	vector<vector<T>> dp;
	T ops(T a, T b) { return min(a,b); }
	RMQ() {}
	RMQ(vector<T> v) {
		int n = v.size();
		int log = 32-__builtin_clz(n);
		dp.assign(log, vector<T>(n));
		copy(all(v), dp[0].begin());
		for(int l=1;l<log;l++) for(int i=0;i<n;i++) {
			auto &cur = dp[l], &ant = dp[l-1];
			cur[i] = ops(ant[i], ant[min(i+(1<<(l-1)), n-1)]);
		}
	}
	T query(int a, int b)  {
		if(a == b) return dp[0][a];
		int p = 31-__builtin_clz(b-a);
		auto &cur = dp[p];
		return ops(cur[a], cur[b-(1<<p)+1]);
	}
};
