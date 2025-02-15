// Offline Dynamic Connectivity
// Solves dynamic connectivity for general graphs.
// Time complexity: O(Nlg^2N).

struct Query {};

vector<Query> seg[4*N];

// [ql, qr] is the range that 'q' is active.
void update(Query q, int ql, int qr, int v, int l, int r) {
  if (qr < l || r < ql) return;
  if (ql <= l && r <= qr) {
    seg[v].push_back(q);
  } else {
    int m = (l+r)/2;
    update(q, ql, qr, 2*v, l, m);
    update(q, ql, qr, 2*v + 1, m+1, r);
  }
}

void update(Query q, int ql, int qr) { update(q, ql, qr, 1, 0, N-1); }

RollbackDSU dsu(N);

void solve(int v, int l, int r) {
  int snapshot = dsu.snapshot();
  for (const auto q: seg[v]) {
    // Add the changes here, e.g. adding edges.
  }

  if (l == r) {
    // This is the DSU state at time 'l'.
    // Solve the queries for this time.
  } else {
    int m = (l+r)/2;
    solve(2*v, l, m);
    solve(2*v+1, m+1, r);
  }
  
  // Reverse the changes.
  dsu.rollback(snapshot);
}

void solve() { solve(1, 0, N-1); }
