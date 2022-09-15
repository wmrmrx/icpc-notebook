// NAO FUNCIONA BEM PARA DOUBLE
//
// MODIFICADO PARA SEGMENTOS VERTICAIS
// RAZOAVELMENTE TESTADO
//
// TOLERA INTERSECÇÕES NAS EXTREMIDADES DOS SEGMENTOS
// SEGMENTOS NÃO DEVEM SER DEGENERADOS
//
// Checa se existem segmentos que se intersectam
// Complexidade: O(N logN)
// 365cc1
template <typename C_T>
bool shamos_hoey(vector<segment> seg) {
	// create sweep segment events {x, type, seg_id}
	vector<tuple<C_T, bool, int>> ev;
	for(int i=0; i<seg.size(); i++) {
		if(seg[i].b < seg[i].a) swap(seg[i].a, seg[i].b);
		ev.emplace_back(seg[i].a.x, 0, i);
		ev.emplace_back(seg[i].b.x, 1, i);
	}
	sort(all(ev));
	auto cmp = [](segment r, segment s) -> bool {
		if(r.a == s.a) return left(r.a, r.b, s.b);
		bool b = s.a < r.a;
		if(b) swap(r, s);
		if(!zero(r.v().x)) return b^left(r.a, r.b, s.a);
		return b^(r.b.y < s.a.y);
	};
	set<segment, decltype(cmp)> s(cmp);
	for(auto [_, b, id]: ev) {
		segment at = seg[id];
		if(!b) {
			auto nxt = s.lower_bound(at);
			if((nxt != s.end() && intersects(*nxt, at))
				|| (nxt != s.begin() && intersects(*(--nxt), at)))
					return 1;
			s.insert(at);
		} else {
			s.erase(at);
		}
	}
	return 0;
}
