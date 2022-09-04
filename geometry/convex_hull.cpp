// Complexity: O(NlogN)
// c3b176
template <bool UPPER>
vector<point> hull(vector<point> v) {
	vector<point> res;
	if(UPPER) for(auto& p: v) p.y = -p.y;
	sort(all(v));
	for(auto& p: v) {
		if(res.empty()) { res.push_back(p); continue; }
		if(res.back().x == p.x) continue;
		while(res.size() >= 2) {
			point a = res[res.size()-2], b = res.back();
			if(!right(a, b, p)) res.pop_back();
			//to include collinear points
			//if(right(a, b, p)) res.pop_back();
			else break;
		}
		res.push_back(p);
	}
	if(UPPER) for(auto &p: res) p.y = -p.y;
	return res;
}
