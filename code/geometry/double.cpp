// Double geometry
// WARNING: INPUT IN DOUBLE IS SLOW, IF POSSIBLE READ WITH INTEGER

constexpr double EPS = 1e-10;

bool zero(double x) {
	return abs(x) <= EPS;
}

// CORNER: point = (0, 0)
struct point {
	double x, y;
	
	point(): x(0), y(0) {}
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

// CORNER: BE CAREFUL WITH PRECISION WITH THESE FUNCTIONS, 
// 	IF NEEDED NORMALIZE (b-a) AND (c-a)
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
	a = a / a.norm(); b = b / b.norm();
	if(!collinear(point(), a, b)) return 0;
	return zero(a.x - b.x) && zero(a.y - b.y) ? 1 : -1;
}

// CORNER: a == b
struct segment {
	point a, b;

	segment() {}
	segment(point _a, point _b): a(_a), b(_b) {}

	point vec() { return b - a; }

	bool contains(point p) {
		return a == p || b == p || parallel(a-p, b-p) == -1;
	}

	point proj(point p) { // projection of p onto segment
		p = p - a;
		point v = vec();
		return a + v*((p*v)/(v*v));
	}

};

bool intersects(segment r, segment s) {
	if(r.contains(s.a) || r.contains(s.b) || s.contains(r.a) || s.contains(r.b)) return 1;
	return left(r.a, r.b, s.a) != left(r.a, r.b, s.b) && 
		left(s.a, s.b, r.a) != left(s.a, s.b, r.b);
}

bool parallel(segment r, segment s) {
	return parallel(r.vec(), s.vec());
}

point line_intersection(segment r, segment s) {
	if(parallel(r, s)) return point(HUGE_VAL, HUGE_VAL);
	point vr = r.vec(), vs = s.vec();
	double cr = vr ^ r.a, cs = vs ^ s.a;
	return (vs*cr - vr*cs) / (vr ^ vs);
}

struct polygon {
	vector<point> vp;
	int n;

	polygon(vector<point>& _vp): vp(_vp), n(vp.size()) {
		if(area2() < -EPS) reverse(all(_vp));
	}

	int nxt(int i) { return i+1<n ? i+1 : 0; }
	int prv(int i) { return i ? i-1 : n-1; }

	// If positive, the polygon is in ccw order. It is in cw order otherwise.
	double area2() { // O(n
		double acum = 0;
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
		return hi != n ? !right(vp[lo], vp[hi], p) : dist2(vp[0], p) < dist2(vp[0], vp[n-1]) + EPS;
	}

	double calipers() { // O(n). The polygon must be convex and in ccw order.
		double ans = 0;
		for(int i = 0, j = 1; i < n; i++) {
			point v = vp[nxt(i)] - vp[i];
			while((v ^ (vp[nxt(j)] - vp[j])) > EPS) j = nxt(j);
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
		double dir;
		for(int i = 0, j = 0; i < n || j < rhs.n; i += dir > -EPS, j += dir < EPS) {
			sum.push_back(vp[i % n] + rhs.vp[j % rhs.n]);
			dir = (vp[(i + 1) % n] - vp[i % n]) 
				^ (rhs.vp[(j + 1) % rhs.n] - rhs.vp[j % rhs.n]);
		}
		return polygon(sum);
	}
};

// Circle
//  Basic structure of circle and operations related with it.
// 
// All operations' time complexity are O(1)

const double PI = acos(-1);

struct circle {
	point o; double r;

	circle() {}
	circle(point _o, double _r) : o(_o), r(_r) {}
	// CORNER CASE: a, b and c must NOT be collinear
	circle(point a, point b, point c) {
		b = b - a;
		c = c - a;
		double B = b.norm2();
		double C = c.norm2();
		double D = b ^ c;
		o = a + point( (c.y*B - b.y*C) / (2*D), (b.x * C - c.x * B) / (2*D) );
		r = (o-a).norm();
	}

	bool has(point p) { 
		return (o - p).norm2() < r*r + EPS;
	}
	bool in(circle c){ // non strict
		double d=(o-c.o).norm();
		return d+r<c.r+EPS;
	}
	vector<point> operator/(circle c) { // Intersection of circles.
		vector<point> inter;                   // The points in the output are in ccw order.
		double d = (o - c.o).norm();
		if(r + c.r < d - EPS || d + min(r, c.r) < max(r, c.r) - EPS)
			return {};
		double x = (r*r - c.r*c.r + d*d) / (2*d);
		double y = sqrt(r*r - x*x);
		point v = (c.o - o) / d;
		inter.pb(o + v*x + v.rotated(cw90)*y);
		if(y > EPS) inter.pb(o + v*x + v.rotated(ccw90)*y);
		return inter;
	}
	vector<point> tang(point p){
		double d = sqrt(dist2(p, o) - r*r);
		return *this / circle(p, d);
	}
	bool contains(point p){ // non strictly inside
		double d = dist2(o, p);
		return d < r * r + EPS;
	}
};

// Circle Area Intersection
// O(n^2 log n) (high constant)
// https://github.com/mhunicken/icpc-team-notebook-el-vasito/blob/master/geometry/circle.cpp

vector<double> intercircles(vector<circle> c){
	vector<double> r(c.size()+1); // r[k]: area covered by at least k circles
	for(int i=0;i<int(c.size());i++) {
		int k=1;
		auto cmp = [&](point a, point b) {
			return ang_cmp(a - c[i].o, b - c[i].o);
		};
		vector<pair<point,int> > p{
			{c[i].o + point(1,0) * c[i].r, 0},
			{c[i].o - point(1,0) * c[i].r, 0}
		};
		for(int j=0;j<int(c.size());j++) if(j != i) {
			bool b0 = c[i].in(c[j]), b1 = c[j].in(c[i]);
			if( b0 && ( !b1|| i<j ) ) k++;
			else if( !b0 && !b1 ) {
				auto v = c[i] / c[j];
				if(v.size() == 2){
					p.pb({v[0],1});
					p.pb({v[1],-1});
					if(cmp(v[1],v[0])) k++;
				}
			}
		}
		sort(p.begin(),p.end(),
			[&](pair<point,int> a, pair<point,int> b){return cmp(a.first, b.first);});
		for(int j=0;j<int(p.size());j++) {
			point p0 = p[j ? j-1 : p.size()-1].first, p1 = p[j].first;
			point v0 = (p0 - c[i].o), v1 = (p1 - c[i].o);
			double a = acos( v0 * v1 / ( v0.norm() * v1.norm() ) );
			r[k] += (p0.x-p1.x) * (p0.y+p1.y) / 2 + c[i].r * c[i].r * (a-sin(a)) / 2;
			k += p[j].second;
		}
	}
	return r;
}
