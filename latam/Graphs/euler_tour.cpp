//  Euler Walk
//  Description: Find an Eulerean Path that passes through all edges
//               starting at src. Not necesseraly a cycle. Works for both 
//               directed and undirected. Returns vector 
//               of \{vertex,label of edge to vertex\}.
//               Second element of first pair is always $-1$.
//  Complexity: O(N + M)
//

template<bool directed> struct Euler {
    using pii = pair<int, int>;
    int N;
    vector<vector<pii>> adj; 
    vector<vector<pii>::iterator> its; 
    vector<bool> used;
    Euler (int _N) : N (_N), adj (_N) {}
    void add_edge(int a, int b) {
        int M = used.size (); used.push_back(0); 
        adj[a].emplace_back(b, M); 
        if (!directed) adj[b].emplace_back(a, M);
    }
    vector<pii> solve(int src = 0) { 
        its.resize(N);
        for (int i = 0; i < N; i++) its[i] = begin (adj[i]);

        vector<pii> ans, s{{src,-1}}; // {{vert,prev vert},edge label}
        int lst = -1; // ans generated in reverse order
        while (s.size ()) { 
            int x = s.back ().first; auto& it=its[x], en=end(adj[x]);
            while (it != en && used[it->second]) ++it;
            if (it == en) { // no more edges out of vertex
                if (lst != -1 && lst != x) return {};
                // not a path, no tour exists
                ans.push_back(s.back ()); s.pop_back(); 
                if (s.size ()) lst=s.back ().first;
            } else s.push_back(*it), used[it->second] = 1;
        } // must use all edges
        if (ans.size () != used.size () + 1) return {}; 
        reverse(all(ans)); return ans;
    }
};
