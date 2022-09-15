// c2e4d3
template <typename T> struct RMQ {
	vector<vector<T>> dp;
	T ops(T a, T b) { return min(a,b); }
	RMQ() {}
	RMQ(int sz, T v[]) {
		int log = 64-__builtin_clzll(sz);
		dp.assign(log, vector<T>(sz));
		for(int i=0;i<sz;i++) dp[0][i] = v[i];
		for(int l=1;l<log;l++) for(int i=0;i<sz;i++) 
			dp[l][i] = ops(dp[l-1][i],dp[l-1][min(i+(1<<(l-1)), sz-1)]);
	}
	T query(int a, int b)  {
		if(a == b) return dp[0][a];
		int pot = 63-__builtin_clzll(b-a);
		return ops(dp[pot][a], dp[pot][b-(1<<pot)+1]);
	}
};
