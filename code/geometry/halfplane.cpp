// Half-plane intersection
// The result of intersecting half-planes is either
// empty or a convex polygon (maybe degenerated). This template depends on double.cpp
//
// h - (input) set of half-planes to be intersected. Each half-plane is described as a pair
// of points such that the half-plane is at the left of them.
// pol - the intersection of the half-planes as a vector of points. If not empty, these
// points describe the vertices of the resulting polygon in clock-wise order.
// WARNING: Some points of the polygon might be repeated. This may be undesirable in some
// cases but it's useful to distinguish between empty intersections and degenerated
// polygons (such as a point, line, segment or half-line).
//
// Time complexity: O(n logn)

struct halfplane: public segment {
	double ang;
	halfplane() {}
	halfplane(point _a, point _b) {
		a = _a; b = _b;
		ang = atan2(v().y, v().x);
	}
	bool operator <(const halfplane& rhs) const {
		if (fabsl(ang - rhs.ang) < EPS) return right(a, b, rhs.a);
	        return ang < rhs.ang;
	}
	bool operator ==(const halfplane& rhs) const {
		return fabs(ang - rhs.ang) < EPS; 
	}
	bool out(point r) {
		return right(a, b, r);
	}
};

constexpr double INF = 1e19;
vector<point> hp_intersect(vector<halfplane> h) {
	array<point, 4> box = {
		point(-INF, -INF),
		point(INF, -INF),
		point(INF, INF),
		point(-INF, INF),
	};
	for(int i = 0; i < 4; i++)
		h.emplace_back(box[i], box[(i+1) % 4]);
	sort(all(h));
	h.resize(unique(all(h)) - h.begin());
	deque<halfplane> dq;

	auto sz = [&]() -> int { return dq.size(); };

	for(auto hp: h) {
		while(sz() > 1 && hp.out(line_intersection(dq.back(), dq[sz() - 2])))
			dq.pop_back();
		while(sz() > 1 && hp.out(line_intersection(dq[0], dq[1])))
			dq.pop_front();
		dq.push_back(hp);
	}
	while(sz() > 2 && dq[0].out(line_intersection(dq.back(), dq[sz() - 2])))
		dq.pop_back();
	while(sz() > 2 && dq.back().out(line_intersection(dq[0], dq[1])))
		dq.pop_front();
	if(sz() < 3) return {};
	vector<point> pol(sz());
	for(int i = 0; i < sz(); i++) {
		pol[i] = line_intersection(dq[i], dq[(i+1) % sz()]);
	}
	return pol;
}
