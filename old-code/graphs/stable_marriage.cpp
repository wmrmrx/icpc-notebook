//  Stable Marriage problem
//
//  Given n men and n women, where each person has ranked all 
//  members of the opposite sex in order of preference, marry 
//  the men and women together such that there are no two people 
//  of opposite sex who would both rather have each other than 
//  their current partners. When there are no such pairs of 
//  people, the set of marriages is deemed stable.
//
//  If the lists are complete, there is always a solution that
//  can be founc in O(n * m).
//
//  a - Rank list of first group
//  b - Rank list of first group
//  solve () - Gives an stable matching covering the first group.
//             It is necessary that n <= m.
//

struct StableMarriage {
    int n, m;
    using vvi = vector<vector<int>>;
    vvi a, b;
    StableMarriage (int n, int m, vvi a, vvi b) : n (n), m (m), a (a), b (b) {};

    vector<pair<int, int>> solve () {
        assert (n <= m);
        vector<int> p (n), mb (m, -1);
        vector rank (m, vector<int> (n));
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) rank[i][b[i][j]] = j;
        queue<int> q;

        for (int i = 0; i < n; i++) q.push (i);
        while (q.size ()) {
            int u = q.front (); q.pop ();

            int v = a[u][p[u]++];
            if (mb[v] == -1) {
                mb[v] = u;
            }
            else {
                int other_u = mb[v];
                if (rank[v][u] < rank[v][other_u]) {
                    mb[v] = u;
                    q.push (other_u);
                }
                else {
                    q.push (u);
                }
            }
        }
        vector<pair<int, int>> ans;
        for (int i = 0; i < m; i++) if (mb[i] != -1) ans.pb ({mb[i], i});
        return ans;
    }
};
