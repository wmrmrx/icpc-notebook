//  LIS-2D
//  Description: 
//      Given N pairs of numbers, find the lenght of the biggest
//      sequence such that a_i < a_i+1, b_i<b_i+1
//  Complexity: 
//      O(N (logN)^2)
//  Details:
//      It uses divide & conquer with a segtree to make all
//      comparisons fast. memo[i] contains the answer for 
//      the biggest sequence ending in i.
//  0eb0fc
//

const int N = 2e5 + 10;

int n, memo[N];
pair<int, int> a[N];

struct segTree {
    int n;
    vector<ll> st;
    ll combine(ll a, ll b) {
        return max (a, b); // TODO define merge operator
    }
    segTree() {}
    segTree(int n) : n (n), st (2 * n, -1) {}
    void update(int i, ll x) {
        st[i += n] = max (x, st[i + n]); // TODO change update operation
        while (i > 1) {
            i >>= 1;
            st[i] = combine(st[i << 1], st[i << 1 | 1]);
        }
    }
    // query from l to r, inclusive
    ll query(int l, int r) {
        ll resl = -1, resr = -1;
        for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = combine(resl, st[l++]);
            if (r & 1) resr = combine(st[--r], resr);
        }
        return combine(resl, resr);
    }
};


void divide_conquer (int l, int r) {
    if (l == r) return;
    int m = (l + r) / 2;
    divide_conquer (l, m); // calculamos o valor para esquerda

    // propagamos para a direita
    // temos que comprimir coordenadas
    vector<int> M;
    for (int j = l; j <= m; j++) {
        M.push_back (a[j].first + 1);
        M.push_back (a[j].second);
    }
    for (int j = m + 1; j <= r; j++) {
        M.push_back (a[j].first);
        M.push_back (a[j].second);
    }
    sort (all (M));
    unique (all (M));
    auto find_pos = [&] (int x) {
        return (int) (lower_bound (all (M), x) - M.begin ());
    };

    vector<array<int, 4>> events;
    // coord_x, L/R, coord_y, memo/ind
    for (int j = l; j <= m; j++)
        events.pb ({find_pos(a[j].first + 1), 0, find_pos(a[j].second), memo[j]});
    for (int j = m + 1; j <= r; j++)
        events.pb ({find_pos(a[j].first), 1, find_pos(a[j].second), j});
    sort (all (events));

    segTree st (M.size () + 1);
    for (auto [x, op, y, M] : events) {
        if (op == 0) st.update (y, M);
        else memo[M] = max (memo[M], st.query (0, y - 1) + 1);
    }
    divide_conquer (m + 1, r); // calculamos o valor para direita
}
