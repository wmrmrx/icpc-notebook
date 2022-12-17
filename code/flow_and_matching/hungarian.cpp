// Find max matching of min/max weight
// set(i, j, weight): add edge from left vertex i to right vertex j 
// assign(): returns min/max weight max matching
// Change w_t for edge weight type
//
// Complexity: O(V^3)

constexpr int NONE = numeric_limits<int>::max();

using w_t = double;
constexpr w_t INF = 1e100;
bool zero(w_t x) { return abs(x) < 1e-9; }

// HASH FROM HERE
// 95453b
template <bool MAXIMIZE> struct Hungarian {
	int n, m;
	vector<vector<w_t>> w;
	vector<int> ml, mr; // ml: matched vertexes of left side
	vector<w_t> y, z, d;
	vector<bool> S, T;

	Hungarian(int n, int m): n(n), m(m), w(n, vector<w_t>(m, MAXIMIZE?-INF:INF)), 
	ml(n), mr(m), y(n), z(m), d(m), S(n), T(m) {}

	void set(int i, int j, w_t weight) { w[i][j] = MAXIMIZE?weight:-weight; }

	w_t assign() {
		fill(all(ml), NONE); fill(all(mr), NONE);
		for(int i=0;i<n;i++) y[i] = *max_element(all(w[i]));
		fill(all(z), 0);
		for(int i=0;i<n;i++) for(int j=0;j<m;j++) {
			if(mr[j] == NONE && zero(y[i]+z[j]-w[i][j])) {
				ml[i] = j; mr[j] = i;
				break;
			}
		}
		function<bool(int)> kuhn = [&](int s) {
			if(S[s]) return false; S[s] = 1;
			for(int t=0;t<m;t++) if(!T[t]) {
				w_t diff = y[s]+z[t]-w[s][t];
				if(zero(diff)) {
					T[t] = 1;
					if(mr[t] == NONE || kuhn(mr[t])) {
						mr[t] = s; ml[s] = t;
						return true;
					}
				} else d[t] = min(d[t], diff);
			}
			return false;
		};
		for(int i=0;i<n;i++) if(ml[i] == NONE) {
			fill(all(d), numeric_limits<w_t>::max());
			while(true) {
				fill(all(S), false); fill(all(T), false);
				if(kuhn(i)) break;
				w_t delta = numeric_limits<w_t>::max();
				for(int j=0;j<m;j++) if(!T[j]) delta=min(delta, d[j]);
				for(int s=0;s<n;s++) if(S[s]) y[s] -= delta;
				for(int j=0;j<m;j++) {
					if(T[j]) z[j] += delta;
					else d[j] -= delta;
				}
			}
		}
		w_t res = 0;
		for(int i=0;i<n;i++) res += y[i];
		for(int j=0;j<m;j++) res += z[j];
		return MAXIMIZE?res:-res;
	}
};
