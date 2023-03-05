// Convex Hull
// Works with double and integer
// Returns in CCW order (reversed in x in UPPER)
// Complexity: O(NlogN)

template <bool UPPER>
vector<point> hull(vector<point> v) {
	vector<point> res;
	if(UPPER) for(auto& p: v) p.x = -p.x, p.y = -p.y;
	sort(all(v));
	for(auto& p: v) {
		if(res.empty()) { res.push_back(p); continue; }
		if(res.back().x == p.x) continue;
		while(res.size() >= 2) {
			point a = res[res.size()-2], b = res.back();
			if(!left(a, b, p)) res.pop_back();
			//to include collinear points
			//if(right(a, b, p)) res.pop_back();
			else break;
		}
		res.push_back(p);
	}
	if(UPPER) for(auto& p: res) p.x = -p.x, p.y = -p.y;
	return res;
}
