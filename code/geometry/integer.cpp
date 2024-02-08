// Integer Geometry
#define int long long

bool zero(int x) {
	return x == 0;
}

// CORNER: point = (0, 0)
struct point {
	int x, y;
	
	point(): x(0), y(0) {}
	point(int _x, int _y): x(_x), y(_y) {}
	
	point operator+(point rhs) { return point(x+rhs.x, y+rhs.y); }
	point operator-(point rhs) { return point(x-rhs.x, y-rhs.y); }
	int operator*(point rhs) { return x*rhs.x + y*rhs.y; }
	int operator^(point rhs) { return x*rhs.y - y*rhs.x; }

	int norm2() { return *this * *this; }

	using tup = tuple<int, int>;

	bool operator<(const point& rhs) const {
		return tup{x, y} < tup{rhs.x, rhs.y};
	}
	
	bool operator==(const point& rhs) const {
		return tup{x, y} == tup{rhs.x, rhs.y};
	}
};

// angular comparison in [0, 2pi)
// smallest is (1, 0)
// CORNER: a || b == (0, 0)
bool ang_cmp(point a, point b) {
	auto quad = [](point p) -> bool {
		// 0 if ang in [0, pi), 1 if in [pi, 2pi)
		return p.y < 0 || (p.y == 0 && p.x < 0);
	};
	using tup = tuple<bool, int>;
	return tup{quad(a), 0} < tup{quad(b), a^b};
}

int dist2(point p, point q) { // squared distance
    return (p - q)*(p - q);
}

int area2(point a, point b, point c) { // two times signed area of triangle abc
	return (b - a) ^ (c - a);
}

bool left(point a, point b, point c) {
	return area2(a, b, c) > 0; // counterclockwise
}

bool right(point a, point b, point c) {
	return area2(a, b, c) < 0; // clockwise
}

bool collinear(point a, point b, point c) {
	return zero(area2(a,b,c));
}

// CORNER: a || b == (0, 0)
int parallel(point a, point b) {
	if(!zero(a ^ b)) return 0;
	return (a.x>0) == (b.x>0) && (a.y > 0) == (b.y > 0) ? 1 : -1;
}

// CORNER: a == b
struct segment {
	point a, b;
	
	segment(): a(), b() {}
	segment(point _a, point _b): a(_a), b(_b) {}

	point vec() { return b - a; }

	bool contains(point p) {
		return a == p || b == p || parallel(a-p, b-p) == -1;
	}
};

bool intersects(segment r, segment s) {
	if(contains(r, s.a) || contains(r, s.b) || contains(s, r.a) || contains(s, r.b)) return 1;
	return left(r.a,r.b,s.a) != left(r.a,r.b,s.b) && 
		left(s.a, s.b, r.a) != left(s.a, s.b, r.b);
}

bool parallel(segment r, segment s) {
	return parallel(r.vec(), s.vec());
}

struct polygon {
	vector<point> vp;
	int n;

	polygon(vector<point>& _vp): vp(_vp), n(vp.size()) {
		if(area2() < 0) reverse(all(_vp));
	}

	int nxt(int i) { return i+1<n ? i+1 : 0; }
	int prv(int i) { return i ? i-1 : n-1; }

	// If positive, the polygon is in ccw order. It is in cw order otherwise.
	int area2() { // O(n
		int acum = 0;
		for(int i = 0; i < n; i++)
			acum += vp[i] ^ vp[nxt(i)];
		return acum;
	}

	bool has(point p) { // O(log n). The polygon must be convex and in ccw order
		if(right(vp[0], vp[1], p) || left(vp[0], vp[n-1], p)) return 0;
		int lo = 1, hi = n;
		while(lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			if(!right(vp[0], vp[mid], p)) lo = mid;
			else hi = mid;
		}
		return hi != n ? !right(vp[lo], vp[hi], p) : dist2(vp[0], p) <= dist2(vp[0], vp[n-1]);
	}

	int calipers() { // O(n). The polygon must be convex and in ccw order.
		int ans = 0;
		for(int i = 0, j = 1; i < n; i++) {
			point v = vp[nxt(i)] - vp[i];
			while((v ^ (vp[nxt(j)] - vp[j])) > 0) j = nxt(j);
			// do something with vp[i] and vp[j]
			ans = max(ans, dist2(vp[i], vp[j])); // Example with polygon diameter squared
		}
		return ans;
	}

	// returns the maximal point using comparator cmp
	// example: 
	// 	extreme([&](point p, point q) {return p * v > q * v;});
	// 	returns point with maximal dot product with v
	int extreme(const function<bool(point, point)> &cmp) {
		auto is_extreme = [&](int i, bool& cur_dir) -> bool {
			cur_dir = cmp(vp[nxt(i)], vp[i]);
			return !cmp(vp[prv(i)], vp[i]) && !cur_dir;
		};
		bool last_dir, cur_dir;
		if(is_extreme(0, last_dir)) return 0;
		int lo = 0, hi = n; 
		while(lo + 1 < hi) {
			int m = (lo + hi) / 2;
			if(is_extreme(m, cur_dir)) return m;
			bool rel_dir = cmp(vp[m], vp[lo]);
			if((!last_dir && cur_dir) || (last_dir == cur_dir && rel_dir == cur_dir)) {
				lo = m;
				last_dir = cur_dir;
			} else hi = m;
		}
		return lo;
	}

	pair<int, int> tangent(point p) { // O(log n) for convex polygon in ccw orientation
		// Finds the indices of the two tangents to an external point q
		auto left_tangent = [&](point r, point s) -> bool {
			return right(p, r, s);
		};
		auto right_tangent = [&](point r, point s) -> bool {
			return left(p, r, s);
		};
		return {extreme(left_tangent), extreme(right_tangent)};
	}

	void normalize() { // p[0] becomes the lowest leftmost point 
		rotate(vp.begin(), min_element(all(vp)), vp.end());
	}

	polygon operator+(polygon& rhs) { // Minkowsky sum
		normalize();
		rhs.normalize();
		vector<point> sum;
		for(int i = 0, j = 0, dir; i < n || j < rhs.n; i += dir >= 0, j += dir <= 0) {
			sum.push_back(vp[i % n] + rhs.vp[j % rhs.n]);
			dir = (vp[(i + 1) % n] - vp[i % n]) 
				^ (rhs.vp[(j + 1) % rhs.n] - rhs.vp[j % rhs.n]);
		}
		return polygon(sum);
	}
};
