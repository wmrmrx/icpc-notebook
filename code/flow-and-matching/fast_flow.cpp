// Push-Relabel / fast flow
// Description: Quickly calculate max flow in O(V^2 E)
// Source: https://gist.github.com/Chillee/ad2110fc17af453fb6fc3357a78cfd28#file-hlpp-cpp
// Verification: https://www.spoj.com/problems/FASTFLOW/
 

struct HLPP {
    using F = ll; // flow type
    struct Edge { 
        int to, rev; 
        F f; 
        Edge (int to, int rev, F f) : to (to), rev (rev), f (f) {}
    };
    const F INF = numeric_limits<F>::max();

    int N,s,t;
    vector<vector<Edge>> adj;

    HLPP (int N) : N (N), adj (N), lst (N), gap (N), excess (N), height (N), cnt (N), highest (0) {}
    
    void add_edge(int u, int v, F cap) {
        assert(cap >= 0); // don't try smth dumb
        Edge a(v, (int) adj[v].size (), cap), b(u, (int) adj[u].size (), 0);
        adj[u].pb(a), adj[v].pb(b);
    }

    vector<vector<int>> lst, gap;
    vector<F> excess;
    int highest, work;
    vector<int> height, cnt;
    void updHeight(int v, int nh) {
        work++;
        if (height[v] != N) cnt[height[v]]--;
        height[v] = nh;
        if (nh == N) return;
        cnt[nh]++, highest = nh;
        gap[nh].pb(v);
        if (excess[v] > 0) lst[nh].pb(v);
    }
    void globalRelabel() {
        work = 0;
        for (int i = 0; i < N; i++) height[i] = N, cnt[i] = 0;
        for (int i = 0; i < highest; i++) lst[i].clear(), gap[i].clear();
        height[t] = 0;
        queue<int> q({t});
        while (q.size ()) {
            int v = q.front (); q.pop();
            for (auto &e : adj[v])
                if (height[e.to] == N && adj[e.to][e.rev].f > 0)
                    q.push(e.to), updHeight(e.to, height[v] + 1);
            highest = height[v];
        }
    }
    void push(int v, Edge& e) {
        if (excess[e.to] == 0) lst[height[e.to]].pb(e.to);
        F df = min(excess[v], e.f);
        e.f -= df, adj[e.to][e.rev].f += df;
        excess[v] -= df, excess[e.to] += df;
    }
    void discharge(int v) {
        int nh = N;
        for (auto &e : adj[v]) {
            if (e.f > 0) {
                if (height[v] == height[e.to] + 1) {
                    push(v, e);
                    if (excess[v] <= 0) return;
                } else height[e.to] + 1 < nh ? nh = height[e.to] + 1, 1 : 0;
            }
        }
        if (cnt[height[v]] > 1) updHeight(v, nh);
        else {
            for (int i = height[v]; i <= highest; i++) {
                for (auto &j : gap[i]) updHeight(j, N);
                gap[i].clear();
            }
        }
    }
    F get_flow(int _s, int _t) {
        s = _s, t = _t; if (s == t) return -1;
        for (int i = 0; i < N; i++) excess[i] = 0;
        excess[s] = INF, excess[t] = -INF;
        globalRelabel();
        for (auto &e : adj[s]) push(s,e);
        for (; highest >= 0; highest--) 
            while (lst[highest].size ()) {
                int v = lst[highest].back ();
                lst[highest].pop_back();
                discharge(v);
                if (work > 4*N) globalRelabel();
            }
        return excess[t]+INF;
    }
};
