// 2-SAT
// Description: Tells if a system is 2-Satisfiable
// Complexity: O(|V| + |E|)
// 
// Functions:
//     either (a, b) - (a | b) is true
//     implies (a, b) - (a -> b) is true
//     must (x) - x is true
//     solve () - returns true if the system is possible. 
//                ans[] is the answer for each variable.
// 
// Details:
//      Not x is equivalente to ~x on this template.
//      Did not test function atMostOne, but it add constraints
//      so that only one of these variables can be true.
// 46e497

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
    int N; SCC S; vector<bool> ans;
    void init(int _N) { 
        N = _N; 
        S.init(2*N); 
        ans.resize(N); 
    }
    int addVar() { 
        return N++; 
    }
    void either(int x, int y) { 
        x = max(2 * x, -1 - 2 * x), y = max(2 * y, -1 - 2 * y);
        S.add_edge(x ^ 1, y); S.add_edge(y ^ 1, x); 
    }
    void implies(int x, int y) { 
        either(~x, y); 
    }
    void must(int x) {
        either(x, x); 
    }
    void atMostOne(const vector<int>& li) {
        if (li.size() <= 1) return;
        int cur = ~li[0];
        for (int i = 2; i < li.size(); i++) {
            int next = addVar();
            either(cur, ~li[i]); either(cur, next);
            either(~li[i], next); cur = ~next;
        }
        either(cur,~li[1]);
    }
    bool solve(int _N = -1) {
        if (_N != -1) N = _N, S.init(2*N);
        S.gen(); reverse(all(S.comps));
        for (int i = 0; i < 2 * N; i += 2) 
            if (S.comp[i] == S.comp[i^1]) return 0;
        vector<int> tmp(2 * N); for (auto i : S.comps) if (!tmp[i]) 
            tmp[i] = 1, tmp[S.comp[i ^ 1]] = -1;
        for(int i = 0; i < N; i++) if (tmp[S.comp[2*i]] == 1) ans[i] = 1;
        return 1;
    }
};
