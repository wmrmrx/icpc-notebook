// MODIFICADO PARA SEGMENTOS VERTICAIS
// RAZOAVELMENTE TESTADO COM CASOS PEQUENOS (N = 5) 
// NAO CONFIAR TOTALMENTE
//
// Checa se existem segmentos que se intersectam
// Complexidade: O(N logN)
// f308c0
bool shamos_hoey(vector<segment> seg) {
	// create sweep segment events {x, type, seg_id}
	vector<array<int, 3> > ev;
	for(int i=0; i<seg.size(); i++) {
		if(seg[i].b < seg[i].a) swap(seg[i].a, seg[i].b);
		ev.push_back({seg[i].a.x, 0, i});
		ev.push_back({seg[i].b.x, 1, i});
	}
	sort(ev.begin(), ev.end());
	auto cmp = [](segment r, segment s) -> bool {
		if(r.a == s.a) {
			if(zero(r.v().x) && zero(s.v().x))
				return r.v().y < s.v().y;
			return left(r.a, r.b, s.b);
		}
		bool b = s.a < r.a;
		if(b) swap(r, s);
		if(!zero(r.v().x))
			return b^left(r.a, r.b, s.a);
		return b^(r.b.y < s.a.y);
	};
	set<segment, decltype(cmp)> s(cmp);
	for(auto e: ev) {
		segment at = seg[e[2]];
		if(!e[1]) {
			auto nxt = s.lower_bound(at);
			if((nxt != s.end() && intersects(*nxt, at))
				|| (nxt != s.begin() && intersects(*(--nxt), at)))
					return 1;
			s.insert(at);
		} else {
			auto nxt = s.upper_bound(at), cur = nxt, prev = --cur;
			if(nxt != s.end() && prev != s.begin() 
				&& intersects(*nxt, *(--prev))) return 1;
			s.erase(cur);
		}
	}
	return 0;
}
