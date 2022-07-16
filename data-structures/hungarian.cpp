template <typename T>
using arr = unique_ptr<T[]>;

constexpr int NONE = numeric_limits<int>::max();

using w_t = double;
constexpr w_t INF = 1e100;
bool zero(w_t x) { return abs(x) < 1e-9; }

template <bool MAXIMIZE> struct Hungarian {
	int n, m;
	arr<arr<w_t>> w;
	arr<int> ml, mr; // ml: matched vertexes of left side
	arr<w_t> y, z, d;
	arr<bool> S, T;

	Hungarian(int n, int m): n(n), m(m), 
	w(new arr<w_t>[n]),
	ml(new int[n]), mr(new int[m]),
	y(new w_t[n]), z(new w_t[m]), d(new w_t[m]),
	S(new bool[n]), T(new bool[m]) {
		for(int i=0;i<n;i++) {
			w[i].reset(new w_t[m]);
			fill_n(w[i].get(), m, MAXIMIZE?-INF:INF);
		}
	}

	void set(int i, int j, w_t weight) { w[i][j] = MAXIMIZE?weight:-weight; }

	w_t assign() {
		fill_n(ml.get(), n, NONE); fill_n(mr.get(), m, NONE);
		for(int i=0;i<n;i++) y[i] = *max_element(w[i].get(), w[i].get()+m);
		fill_n(z.get(), m, 0);
		for(int i=0;i<n;i++) for(int j=0;j<m;j++) {
			if(mr[j] == NONE && zero(y[i]+z[j]-w[i][j])) {
				ml[i] = j; mr[j] = i;
				break;
			}
		}
		auto kuhn = [&](int s, auto&& self) -> bool {
			if(S[s]) return false; S[s] = 1;
			for(int t=0;t<m;t++) if(!T[t]) {
				w_t diff = y[s]+z[t]-w[s][t];
				if(zero(diff)) {
					T[t] = 1;
					if(mr[t] == NONE || self(mr[t], self)) {
						mr[t] = s; ml[s] = t;
						return true;
					}
				} else d[t] = min(d[t], diff);
			}
			return false;
		};
		for(int i=0;i<n;i++) if(ml[i] == NONE) {
			fill_n(d.get(), m, numeric_limits<w_t>::max());
			while(true) {
				fill_n(S.get(), n, false); fill_n(T.get(), m, false);
				if(kuhn(i,kuhn)) break;
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
