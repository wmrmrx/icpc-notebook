// Polynomial operations
// Polynomial division: O(n*log(n))
// Multi-point polynomial evaluation: O(n*log^2(n))
// Polynomial interpolation: O(n*log^2(n))
 
// Works with NTT. For FFT, just replace the type.

#define SZ(s) int(s.size())
using Z = mint<998244353>;
typedef vector<Z> poly;

poly add(poly &a, poly &b) {
    int n = SZ(a), m = SZ(b);
    poly ans(max(n, m));
    for (int i = 0; i < max(n, m); i++) {
        if (i < n)
            ans[i] += a[i];
        if (i < m)
            ans[i] += b[i];
    }
    while (SZ(ans) > 1 && !ans.back().x) ans.pop_back();
    return ans;
}

poly invert(poly &b, int d) {
    poly c = {b[0].inv ()};
    while (SZ(c) <= d) {
        int j = 2 * SZ(c);
        auto bb = b;
        bb.resize(j);
        poly cb = NTT::multiply(c, bb);
        for (int i = 0; i < SZ(cb); i++) cb[i] = Z(0) - cb[i];
        cb[0] += 2;
        c = NTT::multiply(c, cb);
        c.resize(j);
    }
    c.resize(d + 1);
    return c;
}

pair<poly, poly> divslow(poly &a, poly &b) {
    poly q, r = a;
    while (SZ(r) >= SZ(b))
    {
        q.pb(r.back() * b.back().inv ());
        if (q.back().x)
            for (int i = 0; i < SZ(b); i++)
            {
                r[SZ(r) - i - 1] = r[SZ(r) - i - 1] - q.back() * b[SZ(b) - i - 1];
            }
        r.pop_back();
    }
    reverse(all(q));
    return {q, r};
}

pair<poly, poly> divide(poly &a, poly &b) { // returns {quotient,remainder}
    int m = SZ(a), n = SZ(b), MAGIC = 750;
    if (m < n)
        return {{0}, a};
    if (min(m - n, n) < MAGIC)
        return divslow(a, b);
    poly ap = a; reverse(all(ap));
    poly bp = b; reverse(all(bp));
    bp = invert(bp, m - n);
    poly q = NTT::multiply(ap, bp);
    q.resize(SZ(q) + m - n - SZ(q) + 1, 0);
    reverse(all(q));
    poly bq = NTT::multiply(b, q);
    for (int i = 0; i < SZ(bq); i++) bq[i] = Z(0) - bq[i];
    poly r = add(a, bq);
    return {q, r};
}

vector<poly> tree;

void filltree(vector<Z> &x) {
    int k = SZ(x);
    tree.resize(2 * k);
    for (int i = k; i < 2 * k; i++) tree[i] = {Z(0) - x[i - k], 1};
    for (int i = k - 1; i; i--)
        tree[i] = NTT::multiply(tree[2 * i], tree[2 * i + 1]);
}

vector<Z> evaluate(poly &a, vector<Z> &x) {
    filltree(x);
    int k = SZ(x);
    vector<poly> ans(2 * k);
    ans[1] = divide(a, tree[1]).second;
    for (int i = 2; i < 2 * k; i++) ans[i] = divide(ans[i >> 1], tree[i]).second;
    vector<Z> r;
    for (int i = 0; i < k; i++) r.pb(ans[i + k][0]);
    return r;
}

poly derivate(poly &p) {
    poly ans(SZ(p) - 1);
    for (int i = 1; i < SZ(p); i++) ans[i - 1] = p[i] * i;
    return ans;
}

poly interpolate(vector<Z> &x, vector<Z> &y) {
    filltree(x);
    poly p = derivate(tree[1]);
    int k = SZ(y);
    vector<Z> d = evaluate(p, x);
    vector<poly> intree(2 * k);
    for (int i = k; i < 2 * k; i++) intree[i] = {y[i - k] / d[i - k]};
    for (int i = k - 1; i; i--) {
        poly p1 = NTT::multiply(tree[2 * i], intree[2 * i + 1]);
        poly p2 = NTT::multiply(tree[2 * i + 1], intree[2 * i]);
        intree[i] = add(p1, p2);
    }
    return intree[1];
}
