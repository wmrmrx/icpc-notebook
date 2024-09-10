// Compute Delaunay edges in O(N logN) with Fortune https://codeforces.com/blog/entry/85638
// Must use long double
// How to use: 
//   vector<pair<int,int>> edges = Delaunay(vector_of_points, coordinate_bigger_than_all).edges;
//   where big_value is a value greater that all coordinates
double sweepx;
struct Delaunay {
	static constexpr double INF = 1e100;
	struct arc {
		mutable point p, q;
		mutable int id = 0, i;
		arc(point _p, point _q, int _i) : p(_p), q(_q), i(_i) {}
		double gety(double x) const {
			if(q.y == INF) return INF;
			x += EPS;
			point med = (p + q) * 0.5;
			point dir = (p - med).rotated(ccw90);
			double d = (x - p.x) * (x - q.x);
			return med.y + ((med.x - x) * dir.x + sqrt(d) * dir.norm()) / dir.y;
		}
		bool operator<(const double &y) const { return gety(sweepx) < y; }
		bool operator<(const arc &o) const { return gety(sweepx) < o.gety(sweepx); }
	};
	using beach = multiset<arc, less<>>;
	using bit = beach::iterator;
	struct event {
		double x;
		int id;
		bit* it;
		event(double _x, int _id, bit* _it) : x(_x), id(_id), it(_it) {}
		bool operator<(const event &e) const { return x > e.x; }
	};
	int n, ti;
	beach line;
	vector<pair<point, int>> v;
	priority_queue<event> Q;
	vector<bool> valid;
	vector<pair<int,int>> edges;
	Delaunay(vector<point> p, double X = 1e9): n(p.size()), v(n) {
		point rad = point(sin(ang), cos(ang));
		for(int i = 0 ;i < n; i++) v[i] = {p[i].rotated(rad), i};
		sort(all(v));
		X *= 3;
		line.insert(arc(point(-X, -X), point(-X, X), -1));
		line.insert(arc(point(-X, X), point(INF, INF), -1));
		for(int i=0;i<n;i++) Q.push(event(v[i].first.x, i, nullptr));
		ti = 0;
		valid.assign(1, false);
		while(!Q.empty()) {
			event e = Q.top(); Q.pop();
			sweepx = e.x;
			if(e.id >= 0) {
				add(e.id);
			} else if(valid[-e.id]) {
				remove(*e.it);
				delete e.it;
			}
		}
	}
	void upd(bit it) {
		if(it->i == -1) return;
		valid[-it->id] = false;
		auto a = prev(it);
		if(parallel(it->q - it->p, a->p - it->p)) return;
		it->id = --ti;
		valid.pb(true);
		point c = circle(it->p, it->q, a->p).o;
		double x = c.x + (c - it->p).norm();
		if(x > sweepx - EPS && a->gety(x) + EPS > it->gety(x)) {
			Q.push(event(x, it->id, new bit(it)));
		}
	}
	void add_edge(int i, int j) {
		if(i == -1 || j == -1) return;
		edges.pb({v[i].second, v[j].second});
	}
	void add(int i) {
		point p = v[i].first;
		auto c = line.lower_bound(p.y);
		auto b = line.insert(c, arc(p, c->p, i));
		auto a = line.insert(b, arc(c->p, p, c->i));
		add_edge(i, c->i);
		upd(a); upd(b); upd(c);
	}
	void remove(bit it) {
		auto a = prev(it);
		auto b = next(it);
		line.erase(it);
		a->q = b->p;
		add_edge(a->i, b->i);
		upd(a); upd(b);
	}
};
