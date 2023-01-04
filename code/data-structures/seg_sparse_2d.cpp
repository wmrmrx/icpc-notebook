/*  
    Segtree 2D:
    Data structure that makes operation on a grid.
    Grid of dimensions N x M
    Sum on point
    Query of sum of points in rectangle
   

    Complexity:
        update, query - O(logN^2)
*/

// 9363b0
namespace seg2d {
	const int N = 200'000, M = 200'000;
	struct Node {
		int32_t s = 0;
		int32_t l = 0, r = 0;
	};
	vector<Node> v;

	void upd(int& no, int l, int r, int pos, int val) {
		if(pos < l || r < pos) return;
		if(not no) {
			no = v.size();
			//assert(no < v.capacity());
			v.emplace_back();
		}
		if(l == r) v[no].s += val; // !!! OR v[no].s = val !!!
		else {
			int m = (l+r)/2;
			auto &[s, nl, nr] = v[no];
			upd(nl, l, m, pos, val);
			upd(nr, m+1, r, pos, val);
			s = v[nl].s + v[nr].s;
		}
	}

	int qry(int no, int l, int r, int ql, int qr) {
		if(not no) return 0;
		if(qr < l || r < ql) return 0;
		auto &[s, nl, nr] = v[no];
		if(ql <= l && r <= qr) return s;
		int m = (l+r)/2;
		return qry(nl, l, m, ql, qr)
			+ qry(nr, m+1, r, ql, qr);
	}

	void update(int x, int y, int val) {
		for(x+=1;x<=N;x+=x&-x) upd(x, 0, M-1, y, val);
	}

	int query(int x, int ly, int ry) {
		int res = 0;
		for(x+=1;x>0;x-=x&-x) res += qry(x, 0, M-1, ly, ry);
		return res;
	}

	int query(int lx, int ly, int rx, int ry) {
		return query(rx, ly, ry) - query(lx-1, ly, ry);
	}

	// receives max number of updates
	// each update creates at most logN logM nodes
	// RTE if we reserve less than number of nodes created
	void init(int maxu) {
		v.reserve(400*maxu);
		v.resize(N+1);
	}
}
