bool zero(int x) {
	return x == 0;
}

// CORNER: point = (0, 0)
struct point {
	int x, y;
	
	point(int x=0, int y=0): x(x), y(y) {}
	
	point operator+(point rhs) { return point(x+rhs.x, y+rhs.y); }
	point operator-(point rhs) { return point(x-rhs.x, y-rhs.y); }
	int operator*(point rhs) { return x*rhs.x + y*rhs.y; }
	int operator^(point rhs) { return x*rhs.y - y*rhs.x; }

	int norm2() { return *this * *this; }

	using tup = tuple<int, int>;

	bool operator<(const point& rhs) const {
		return tup{x, y} < tup{rhs.x, rhs.y};
	}
};

// angular comparison in [0, 2pi)
// smallest is (1, 0)
// CORNER CASE: a, b == (0, 0)
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

int parallel(point a, point b) {
	if((a ^ b) != 0) return 0;
	return (a.x>0) == (b.x>0) && (a.y > 0) == (b.y > 0) ? 1 : -1;
}

// CORNER: a == b
struct segment {
	point a, b;

	segment(point a=point(), point b=point()): a(a), b(b) {}

	//MAINTAIN a < b FOR SHAMOS-HOEY
	//segment(point a=point(), point b=point()): a(min(a,b)), b(max(a,b)) {}
	
	segment sorted() {
		return segment(min(a,b), max(a,b));
	}

	bool contains(point p) {
		int lx = a.x, ux = b.x, ly = a.y, uy = b.y;
		if(lx > ux) swap(lx, ux); 
		if(ly > uy) swap(ly, uy);
		return collinear(a, b, p)
			&& lx <= p.x && p.x <= ux
			&& ly <= p.y && p.y <= uy;
	}

	bool intersects(segment rhs) {
		segment lhs = *this;
		auto sign = [](int x) { if(zero(x)) return 0; return x > 0 ? 1 : -1; };
		if(sign(area2(lhs.a, lhs.b, rhs.a))*sign(area2(lhs.a, lhs.b, rhs.b)) == 1) return false;
		swap(lhs, rhs);
		if(sign(area2(lhs.a, lhs.b, rhs.a))*sign(area2(lhs.a, lhs.b, rhs.b)) == 1) return false;
		return true;
	}

	point v() { return b - a; }

};

bool parallel(segment r, segment s) {
	return parallel(r.v(), s.v());
}
