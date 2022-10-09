
/* Half-plane intersection algorithm. The result of intersecting half-planes is either
 * empty or a convex polygon (maybe degenerated). This template depends on point_double.cpp
 * and line_double.cpp.
 *
 * h - (input) set of half-planes to be intersected. Each half-plane is described as a pair
 * of points such that the half-plane is at the left of them.
 * pol - the intersection of the half-planes as a vector of points. If not empty, these
 * points describe the vertices of the resulting polygon in clock-wise order.
 * WARNING: Some points of the polygon might be repeated. This may be undesirable in some
 * cases but it's useful to distinguish between empty intersections and degenerated
 * polygons (such as a point, line, segment or half-line).
 *
 * Time complexity: O(n logn)
 */

struct halfplane: public line {
	ld ang;
	halfplane() {}
	halfplane(point _p, point _q) {
		p = _p; q = _q;
		point vec(q - p);
		ang = atan2(vec.y, vec.x);
	}
	bool operator <(const halfplane& other) const {
		if (fabsl(ang - other.ang) < EPS) return right(p, q, other.p);
	        return ang < other.ang;
	}
	bool operator ==(const halfplane& other) const {
		return fabsl(ang - other.ang) < EPS; 
	}
	bool out(point r) {
		return right(p, q, r);
	}
};

vector<point> hp_intersect(vector<halfplane> h) {
	point box[4] = {{-INF, -INF}, {INF, -INF}, {INF, INF}, {-INF, INF}};
	for(int i = 0; i < 4; i++)
		h.pb(halfplane(box[i], box[(i+1) % 4]));
	sort(h.begin(), h.end());
	h.resize(unique(h.begin(), h.end()) - h.begin());
	deque<halfplane> dq;
	for(auto hp: h) {
		while(sz(dq) > 1 && hp.out(intersect(dq.back(), dq[sz(dq) - 2])))
			dq.pop_back();
		while(sz(dq) > 1 && hp.out(intersect(dq[0], dq[1])))
			dq.pop_front();
		dq.pb(hp);
	}
	while(sz(dq) > 2 && dq[0].out(intersect(dq.back(), dq[sz(dq) - 2])))
		dq.pop_back();
	while(sz(dq) > 2 && dq.back().out(intersect(dq[0], dq[1])))
		dq.pop_front();
	if(sz(dq) < 3) return {};
	vector<point> pol(sz(dq));
	for(int i = 0; i < sz(dq); i++) {
		pol[i] = intersect(dq[i], dq[(i+1) % sz(dq)]);
	}
	return pol;
}
