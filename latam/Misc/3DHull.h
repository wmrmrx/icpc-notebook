// Computes all faces of the 3-dimension hull of a point set.
// *No four points must be coplanar*, or else random results will be returned.
// All faces will point outwards.
// Time: O(n^2)
typedef Point3D<double> P3;
struct PR {
	void ins(int x) { (a == -1 ? a : b) = x; }
	void rem(int x) { (a == x ? a : b) = -1; }
	int cnt() { return (a != -1) + (b != -1); }
	int a, b;
};
struct F { P3 q; int a, b, c; };
vector<F> hull3d(const vector<P3>& A) {
	int n = A.size();
	assert(n >= 4);
	vector<vector<PR>> E(n, vector<PR>(n, {-1, -1}));
#define E(x,y) E[f.x][f.y]
	vector<F> FS;
	auto mf = [&](int i, int j, int k, int l) {
		P3 q = (A[j] - A[i]).cross((A[k] - A[i]));
		if (q.dot(A[l]) > q.dot(A[i]))
			q = q * -1;
		F f{q, i, j, k};
		E(a,b).ins(k); E(a,c).ins(j); E(b,c).ins(i);
		FS.push_back(f);
	};
	for(int i = 0; i < 4; i++){
		for(int j = i+1; j < 4; j++){
			for(int k = j+1; k < 4; k++){
				mf(i, j, k, 6 - i - j - k);
			}
		}
	}
	for(int i = 4; i < n; i++){
		for(int j = 0; j < (int)FS.size(); j++){
			F f = FS[j];
			if(f.q.dot(A[i]) > f.q.dot(A[f.a])) {
				E(a,b).rem(f.c);
				E(a,c).rem(f.b);
				E(b,c).rem(f.a);
				swap(FS[j--], FS.back());
				FS.pop_back();
			}
		}
		int nw = FS.size();
		for(int j = 0; j < nw; j++){
			F f = FS[j];
#define C(a, b, c) if (E(a,b).cnt() != 2) mf(f.a, f.b, i, f.c);
			C(a, b, c); C(a, c, b); C(b, c, a);
		}
	}
	for (F& it : FS) if ((A[it.b] - A[it.a]).cross(
		A[it.c] - A[it.a]).dot(it.q) <= 0) swap(it.c, it.b);
	return FS;
};
