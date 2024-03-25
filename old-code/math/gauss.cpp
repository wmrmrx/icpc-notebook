// Gauss elimination
// Complexity: O(N*M*M)

using arr = valarray<double>;
struct Gauss {
	int n, m;
	vector<arr> v;
	Gauss(int _n, int _m): n(_n), m(_m), v(n, arr(m)) {}

	arr& operator[](int i) { return v[i]; }

	void eliminate() {
		// eliminate column j
		for(int j=0;j<min(n, m);j++) {
			v[j].swap(*max_element(v.begin()+j, v.end(), 
				[&](arr& a, arr& b) { return abs(a[j]) < abs(b[j]); }));
			for(int i=j+1;i<n;i++)
				v[i] -= v[i][j] / v[j][j] * v[j];
		}
	}
};
