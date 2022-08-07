/*
    Euler Tour
    Description: Find a path that passes through all edges
    Complexity: O(N + M)

    Details:
        It also works for directed graphs and it is supposed
        that the first vertex is 1.

    bb6db8
*/

template<int SZ, bool directed> 
struct Euler {
    int N, M;
    vector< pair<int, int> > adj[SZ], circuit;
    int out[SZ], in[SZ], deg[SZ];
    bool used[SZ], bad;
 
    void clr() {
        for(int i = 0; i < N; i++) adj[i].clear();
        circuit.clear();
        for(int i = 0; i < N; i++) out[i] = in[i] = deg[i] = 0;
        for(int i = 0; i < M; i++) used[i] = 0;
        N = M = bad = 0;
    }
 
    void dfs(int pre, int cur) {
        while (adj[cur].size()) {
            pair<int, int> x = adj[cur].back(); adj[cur].pop_back();
            if (used[x.second]) continue;
            used[x.second] = 1; dfs(cur,x.first);
        }
        if (circuit.size() && circuit.back().first != cur) bad = 1;
        circuit.pb({pre,cur}); // generate circuit in reverse order
    }
 
    void addEdge(int a, int b) {
        if (directed) {
            adj[a].pb({b,M});
            out[a] ++, in[b] ++;
        } else {
            adj[a].pb({b,M}), adj[b].pb({a,M});
            deg[a] ++, deg[b] ++;
        }
        M ++;
    }
 
    vector<int> solve(int _N) {
        N = _N; // edges only involve vertices from 0 to N-1
 
        int start = 1; 
        for(int i = 1; i <= N; i++) if (deg[i]%2 != 0) return {};
        dfs(-1,start);
 
        if (circuit.size() != M+1 || bad) return {}; // return empty if no sol
        vector<int> ans; 
        for(int i = (int) circuit.size() - 1; i >= 0; i--) ans.pb(circuit[i].second);
        return ans;
    }
};
