// Shamos Hoey
// TOLERA INTERSECÇÕES NAS EXTREMIDADES DOS SEGMENTOS
// SEGMENTOS NÃO DEVEM SER DEGENERADOS
//
// Checa se existem segmentos que se intersectam
// Complexidade: O(N logN)

bool shamos_hoey(vector<segment> seg) {
	// create sweep segment events {x, type, seg_id}
	vector<tuple<point, bool, int>> ev;
	for(int i=0; i<seg.size(); i++) {
		if(seg[i].b < seg[i].a) swap(seg[i].a, seg[i].b);
		ev.emplace_back(seg[i].a, 0, i);
		ev.emplace_back(seg[i].b, 1, i);
	}
	sort(all(ev));
	// CORNER CASE: r.a == s.a && collinear(r.a, r,b, s.b) 
	// cmp(r, s) == cmp(s, r) => r == s !!!
	auto cmp = [](segment r, segment s) -> bool {
		if(r.a == s.a) return left(r.a, r.b, s.b);
		else if(r.a < s.a) return left(r.a, r.b, s.a);
		else return !left(s.a, s.b, r.a);
	};
	set<segment, decltype(cmp)> s(cmp);
	for(auto [_, b, id]: ev) {
		segment at = seg[id];
		if(!b) {
			auto nxt = s.lower_bound(at);
			if((nxt != s.end() && intersects(*nxt, at))
				|| (nxt != s.begin() && intersects(*prev(nxt), at)))
					return 1;
			s.insert(at);
		} else {
			auto cur = s.find(at);
			if(cur != s.begin() && next(cur) != s.end() && 
					intersects(*prev(cur), *next(cur))) 
				return 1;
			s.erase(at);
		}
	}
	return 0;
}
