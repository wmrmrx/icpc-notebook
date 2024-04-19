// 2-SAT
// Description: Tells if a system is 2-Satisfiable
// Complexity: O(|V| + |E|)
// 
// Functions:
//     either (a, b) - (a | b) is true
//     implies (a, b) - (a -> b) is true
//     must (x) - x is true
//     atMostOne (v) - ensure that at most one of these
//                     variables is true
//     solve () - returns the answer if system is possible.
// 
// Details:
//      Not x is equivalente to ~x on this template.

struct SCC {
    int N, ti = 0; vector<vector<int>> adj;
    vector<int> disc, comp, st, comps;
    void init(int _N) { 
        N = _N; 
        adj.resize(N);
        disc.resize(N);
        comp = vector<int>(N,-1); 
    }
    void add_edge(int x, int y) { adj[x].push_back(y); }
    int dfs(int x) {
        int low = disc[x] = ++ti; st.push_back(x); // disc[y] != 0 -> in stack
        for (auto y : adj[x]) if (comp[y] == -1) {
            auto b = disc[y] ? : dfs(y); auto &a = low;
            b < a ? a = b, 1 : 0;
        } 
        if (low == disc[x]) { // make new SCC, pop off stack until you find x
            comps.push_back(x); for (int y = -1; y != x;) 
                comp[y = st.back()] = x, st.pop_back();
        }
        return low;
    }
    void gen() {
        for (int i = 0; i < N; i++) if (!disc[i]) dfs(i);
        reverse(all(comps));
    }
};
 
struct TwoSAT {
    int N = 0; vector<pair<int, int>> edges;
    void init (int _N) { N = _N; }
    int addVar () { return N++; }
    void either (int x, int y) { 
        x = max(2 * x, -1 - 2 * x), y = max(2 * y, -1 - 2 * y);
        edges.push_back ({x, y}); 
    }
    void implies (int x, int y) { 
        either (~x,y); 
    }
    void must (int x) { 
        either (x,x); 
    }
    void atMostOne (const vector<int>& li) {
        if (li.size () <= 1) return;
        int cur = ~li[0];
        for (int i = 2; i < li.size (); i++) {
            int next = addVar();
            either(cur, ~li[i]); either(cur, next);
            either(~li[i], next); cur = ~next;
        }
        either(cur, ~li[1]);
    }
    vector<bool> solve() {
        SCC S; S.init(2 * N);
        for (auto [x, y] : edges) 
            S.add_edge(x ^ 1, y), S.add_edge(y ^ 1, x);
        S.gen(); reverse(all(S.comps)); // reverse topo order
        for (int i = 0; i < 2 * N; i += 2) 
            if (S.comp[i] == S.comp[i^1]) return {};
        vector<int> tmp(2 * N); 
        for (auto i : S.comps) if (!tmp[i]) 
            tmp[i] = 1, tmp[S.comp[i^1]] = -1;
        vector<bool> ans(N); 
        for (int i = 0; i < N; i++) ans[i] = tmp[S.comp[2*i]] == 1;
        return ans;
    }
};
