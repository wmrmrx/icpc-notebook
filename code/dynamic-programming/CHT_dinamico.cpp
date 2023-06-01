// CHT - Dynamic Convex Hull Trick
// Description: Maintain the convex hull of some functions
// Complexity: 
//     add - O(logN)
//     query - O(logN)

// Functions:
//     add(a, b) - add line (a * x + b) to the convex hull.
//     query (x) - return the maximum value of any line on point x.

// Details:
//     If you want to maintain the bottom convex hull, it is
//     easier to just change the sign. Be careful with overflow
//     on query. Can use __int128 to avoid.

struct Line {
    mutable ll a, b, p;
    bool operator<(const Line& o) const { return a < o.a; }
    bool operator<(ll x) const { return p < x; }
};

struct dynamic_hull : multiset<Line, less<>> {
    ll div(ll a, ll b) { 
        return a / b - ((a ^ b) < 0 and a % b);
    }
    
    void update(iterator x) {
        if (next(x) == end()) x->p = LINF;
        else if (x->a == next(x)->a) x->p = x->b >= next(x)->b ? LINF : -LINF;
        else x->p = div(next(x)->b - x->b, x->a - next(x)->a);
    }

    bool overlap(iterator x) {
        update(x);
        if (next(x) == end()) return 0;
        if (x->a == next(x)->a) return x->b >= next(x)->b;
        return x->p >= next(x)->p;
    }
        
    void add(ll a, ll b) {
        auto x = insert({a, b, 0});
        while (overlap(x)) erase(next(x)), update(x);
        if (x != begin() and !overlap(prev(x))) x = prev(x), update(x);
        while (x != begin() and overlap(prev(x))) 
            x = prev(x), erase(next(x)), update(x);
    }
    
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
#warning cuidado com overflow
        return l.a * x + l.b;
    }
};