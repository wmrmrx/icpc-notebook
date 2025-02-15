// TODO: how to use

struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};

struct LineContainer : vector<Line> {
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b) {
        return a / b - ((a^b) < 0 && a%b);
    }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k  - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        push_back({k, m, 0}); 
        auto z = prev(end()), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(this->begin(), this->end(), x);
        return l.k * x + l.m;
    }
};
 
LineContainer merge(LineContainer a, LineContainer b) {
    vector<Line> tmp(a.size() + b.size());
    merge(all(a), all(b), tmp.begin());
    LineContainer res;
    for (auto x : tmp) res.add(x.k, x.m);
    return res;
}

LineContainer add(LineContainer a, LineContainer b) {
    LineContainer res;
    int x = 0, y = 0;
    while (x < a.size() && y < b.size()) {
        res.add(a[x].k + b[y].k, a[x].m + b[y].m);
        if (a[x].p < b[y].p) x++;
        else y++;
    }
    return res;
}
