// Iterative Segment Tree
// 0-indexed
// Supports non-commutative operations
//
// functions:
// 	update(pos, val): set leaf node in pos to val
// 	query(l, r): get sum of nodes in l and r
//
// Example: Range minimum queries segtree:
// 	struct Node {
// 		using T = int;
// 		T mn;
// 		Node(): mn(numeric_limits<T>::max()) {}
// 		Node(T x): mn(x) {}
// 		friend Node operator+(Node lhs, Node rhs) {
// 			return Node(min(lhs.mn, rhs.mn));
// 		}
// 	};
// 	using SegMin = SegIt<Node>;
//
//	int main() {
//		vector<int> v{3,1,3};
// 		SegMin seg(v);
// 		assert(seg.query(0, 2).mn == 1);
// 		seg.update(1, 5);
// 		assert(seg.query(0, 2).mn == 3);
// 		assert(seg.query(1, 1).mn == 5);
// 	}
//
// Submission: https://codeforces.com/contest/380/submission/193484078

template <typename ND, typename T = typename ND::T>
struct SegIt {
	int n;
	vector<ND> t;

	SegIt(int _n): n(_n), t(2*n) {} 
	SegIt(vector<T> &v): n(v.size()), t(2*n) {
		for(int i=0;i<n;i++)
			t[i+n] = ND(v[i]);
		build();
	}

	void build() {
		for(int i=n-1;i>0;i--) 
			t[i] = t[2*i] + t[2*i+1];
	}

	void update(int pos, T val) {
		int p = pos + n;
		t[p] = ND(val);
#warning Maybe t[p] = t[p] + ND(val)
		// can merge invalid intervals, but query only merges valid intervals (can ignore bad merges)
		while(p /= 2) 
			t[p] = t[2*p] + t[2*p+1];
	}

	ND query(int l, int r) {
		ND tl, tr;
		r++; // to make query inclusive
		for(l += n, r += n; l < r; l /= 2, r /= 2) {
			if(l&1) tl = tl + t[l++];
			if(r&1) tr = t[--r] + tr;
		}
		return tl + tr;
	}
};
