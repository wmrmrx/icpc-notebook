// WARNING: INPUT IN DOUBLE IS SLOW, IF POSSIBLE READ WITH INTEGER

constexpr double EPS = 1e-10;

bool zero(double x) {
	return abs(x) <= EPS;
}

// CORNER: point = (0, 0)
struct point {
	double x, y;
	
	point(): x(), y() {}
	point(double _x, double _y): x(_x), y(_y) {}
	
	point operator+(point rhs) { return point(x+rhs.x, y+rhs.y); }
	point operator-(point rhs) { return point(x-rhs.x, y-rhs.y); }
	point operator*(double k) { return point(x*k, y*k); }
	point operator/(double k) { return point(x/k, y/k); }
	double operator*(point rhs) { return x*rhs.x + y*rhs.y; }
	double operator^(point rhs) { return x*rhs.y - y*rhs.x; }

	point rotated(point polar) { return point(*this^polar,*this*polar); }
	point rotated(double ang) { return (*this).rotated(point(sin(ang),cos(ang))); }
	double norm2() { return *this * *this; }
	double norm() { return sqrt(norm2()); }

	bool operator<(const point& rhs) const {
		return x < rhs.x - EPS || (zero(x-rhs.x) && y < rhs.y - EPS);
	}

	bool operator==(const point& rhs) const {
		return zero(x-rhs.x) && zero(y-rhs.y);
	}
};

const point ccw90(1, 0), cw90(-1, 0);

// angular comparison in [0, 2pi)
// smallest is (1, 0)
// CORNER: a || b == (0, 0)
bool ang_cmp(point a, point b) {
	auto quad = [](point p) -> bool {
		// 0 if ang in [0, pi), 1 if in [pi, 2pi)
		return p.y < 0 || (p.y == 0 && p.x < 0);
	};
	using tup = tuple<bool, double>;
	return tup{quad(a), 0} < tup{quad(b), a^b};
}

double dist2(point p, point q) { // squared distance
    return (p - q)*(p - q);
}

double dist(point p, point q) {
    return sqrt(dist2(p, q));
}

double area2(point a, point b, point c) { // two times signed area of triangle abc
	return (b - a) ^ (c - a);
}

bool left(point a, point b, point c) {
	return area2(a, b, c) > EPS; // counterclockwise
}

bool right(point a, point b, point c) {
	return area2(a, b, c) < -EPS; // clockwise
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

	segment() {}
	segment(point _a, point _b): a(_a), b(_b) {}

	point v() { return b - a; }

};

bool contains(segment r, point p) {
	return r.a==p || r.b==p || parallel(r.a-p,r.b-p) == -1;
}

bool intersects(segment r, segment s) {
	if(contains(r, s.a) || contains(r, s.b) || contains(s, r.a) || contains(s, r.b)) return 1;
	return left(r.a,r.b,s.a) != left(r.a,r.b,s.b) && 
		left(s.a, s.b, r.a) != left(s.a, s.b, r.b);
}

bool parallel(segment r, segment s) {
	return parallel(r.v(), s.v());
}

point line_intersection(segment r, segment s) {
	if(parallel(r, s)) return point(HUGE_VAL, HUGE_VAL);
	point vr = r.v(), vs = s.v();
	double cr = vr ^ r.a, cs = vs ^ s.a;
	return (vs*cr - vr*cs) / (vr ^ vs);
}

point proj(segment r, point p) {
	p = p - r.a;
	point v = r.v();
	return r.a + v*((p*v)/(v*v));
}

struct polygon {
	vector<point> vp;
	int n;

	polygon(vector<point>& _vp): vp(_vp), n(vp.size()) {}

	int nxt(int i) { return i+1<n ? i+1 : 0; }
	int prv(int i) { return i ? i-1 : 0; }

	// If positive, the polygon is in ccw order. It is in cw order otherwise.
	double orientation() { // O(n
		int acum = 0;
		for(int i = 0; i < n; i++)
			acum += vp[i] ^ vp[nxt(i)];
		return acum;
	}

	double area2() { // O(n)
		return abs(orientation());
	}

	void turnCcw() { // O(n)
		if(orientation() < -EPS) reverse(all(vp));
	}

	bool has(point p) { // O(log n). The polygon must be convex and in ccw order
		if(right(vp[0], vp[1], p) || left(vp[0], vp[n-1], p)) return 0;
		int lo = 1, hi = n;
		while(lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			if(!right(vp[0], vp[mid], p)) lo = mid;
			else hi = mid;
		}
		return hi != n ? !right(vp[lo], vp[hi], p) : dist2(vp[0], p) < dist2(vp[0], vp[n-1]) + EPS;
	}

	double calipers() { // O(n). The polygon must be convex and in ccw order.
		double ans = 0;
		for(int i = 0, j = 1; i < n; i++) {
			point v = vp[nxt(i)] - vp[i];
			while((v ^ (vp[nxt(j)] - vp[j])) > EPS) j = nxt(j);
			ans = max(ans, dist2(vp[i], vp[j])); // Example with polygon diameter squared
		}
		return ans;
	}

	int extreme(const function<bool(point, point)> &cmp) {
		auto isExtreme = [&](int i, bool& curDir) -> bool {
			curDir = cmp(vp[nxt(i)], vp[i]);
			return !cmp(vp[prv(i)], vp[i]) && !curDir;
		};
		bool lastDir, curDir;
		if(isExtreme(0, lastDir)) return 0;
		int lo = 0, hi = n; 
		while(lo + 1 < hi) {
			int m = (lo + hi) / 2;
			if(isExtreme(m, curDir)) return m;
			bool relDir = cmp(vp[m], vp[lo]);
			if((!lastDir && curDir) || (lastDir == curDir && relDir == curDir)) {
				lo = m;
				lastDir = curDir;
			} else hi = m;
		}
		return lo;
	}

	pair<int, int> tangent(point p) { // O(log n) for convex polygon in ccw orientation
		// Finds the indices of the two tangents to an external point q
		auto leftTangent = [&](point r, point s) -> bool {
			return right(p, r, s);
		};
		auto rightTangent = [&](point r, point s) -> bool {
			return left(p, r, s);
		};
		return {extreme(leftTangent), extreme(rightTangent)};
	}

	int maximize(point v) { // O(log n) for convex polygon in ccw orientation
		// Finds the extreme point in the direction of the vector
		return extreme([&](point p, point q) {return p * v > q * v + EPS;});
	}

	void normalize() { // p[0] becomes the lowest leftmost point 
		rotate(vp.begin(), min_element(all(vp)), vp.end());
	}

	polygon operator+(polygon& rhs) { // Minkowsky sum
		vector<point> sum;
		normalize();
		rhs.normalize();
		double dir;
		for(int i = 0, j = 0; i < n || j < rhs.n; i += dir > -EPS, j += dir < EPS) {
			sum.push_back(vp[i % n] + rhs.vp[j % rhs.n]);
			dir = (vp[(i + 1) % n] - vp[i % n]) 
				^ (rhs.vp[(j + 1) % rhs.n] - rhs.vp[j % rhs.n]);
		}
		return polygon(sum);
	}
};
