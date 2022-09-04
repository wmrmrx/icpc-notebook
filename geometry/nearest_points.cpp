using c_t = int;

// Returns minimum distance between two points
// Complexity: O(NlogN)
// ce570b
c_t nearest_points(vector<point> v) {
	using lim = numeric_limits<c_t>;
	c_t res = lim::max(), sq = sqrt((double)res);
	sort(all(v));
	for(int i=1;i<v.size();i++) if(v[i] == v[i-1]) return 0;
	auto by_y = [](const point& a, const point& b) {
		using tup = tuple<c_t, c_t>;
		return tup{a.y, a.x} < tup{b.y, b.x};
	};
	queue<point> active;
	set<point, decltype(by_y)> pts(by_y);
	for(auto& p: v) {
		while(!active.empty() && p.x-active.front().x > sq) {
			pts.erase(active.front());
			active.pop();
		}
		auto it = pts.lower_bound({lim::min(), p.y-sq});
		while(it != pts.end() && it->y <= p.y + sq) {
			c_t d = dist2(p, *it);
			if(d < res) {
				res = d;
				sq = sqrt((double)res);
			}
			it++;
		}
		active.push(p);
		pts.insert(p);
	}
	return res;
}
