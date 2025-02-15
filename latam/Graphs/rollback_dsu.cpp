// Disjoint Set Union with rollback.

struct RollbackDSU {
  vector<int> p, sz;
  vector<pair<ll&, ll>> history;

  RollbackDSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }

  int find(int x) { return (p[x] == x) ? x : find(p[x]); } // O(lgN).

  // merge(a, b) returns true if 'a' and 'b' belong to different components.
  // O(lgN)
  bool merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);

    history.emplace_back(p[b], p[b]);
    history.emplace_back(sz[a], sz[a]);

    p[b] = a;
    sz[a] += sz[b];
    return true;
  }

  int snapshot() { return history.size(); }

  void rollback(int until) {
    while (snapshot() > until) {
      history.back().first = history.back().second;
      history.pop_back();
    }
  }
};
