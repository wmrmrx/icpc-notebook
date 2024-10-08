//  Segtree 2D
template <typename Node>
struct Seg2D {
    int n,m;
    vector<vector<int>> a, st;
    Seg2D (int _n, int _m, vector<vector<int>> _a): n(_n), m(_m), a(_a), st(2 * n, vector<int> (2 * m)) {
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++)st[i+n][j+m]=a[i][j];
        for(int i = 0; i < n; i++) for(int j = m - 1; j; --j)
            st[i + n][j] = st[i + n][j << 1] + st[i + n][j << 1 | 1];
        for(int i = n - 1; i; --i) for(int j = 0; j < 2 * m; j++)
            st[i][j]= st[2 * i][j] + st[2 * i + 1][j];
    }
    void upd (int x, int y, Node v){
        st[x + n][y + m] = v;
        for(int j = y + m; j > 1; j /= 2) st[x + n][j / 2] = st[x + n][j] + st[x + n][j ^ 1];
        for(int i = x + n; i > 1; i /= 2) for(int j = y + m; j; j /= 2)
            st[i / 2][j] = st[i][j] + st[i ^ 1][j];
    }
    // essa query vai de x0, y0 ate x1 - 1, y1 - 1 !!!
    Node query (int x0, int y0, int x1, int y1) {
        Node r = Node (); // definir elemento neutro da query!!!
        for (int i0 = x0 + n, i1 = x1 + n; i0 < i1; i0 /= 2, i1 /= 2){
            int t[4], q = 0;
            if (i0 & 1) t[q++] = i0++;
            if (i1 & 1) t[q++] = --i1;
            for(int k = 0; k < q; k++) for(int j0 = y0 + m, j1 = y1 + m; j0 < j1; j0 /= 2,j1 /= 2){
                if (j0 & 1) r = r + st[t[k]][j0++];
                if (j1 & 1) r = r + st[t[k]][--j1];
            }
        }
        return r;
    }
};