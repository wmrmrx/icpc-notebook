// Persistent segment tree.
// 
// Complexity: 
//      Update - O(logn) memory and time
//      Query - O(logn) time
// Lazy works, but is very expensive. Every query will need O(logn) memory.

template<class T, int SZ> struct pseg {
    static const int LIMIT = 1e7; // adjust
    int nex;
    vector<int> l, r;
    vector<T> val, lazy;
    pseg () : l (LIMIT), r (LIMIT), val (LIMIT), nex (0) {}

    int copy(int cur) {
        int x = nex++;
        val[x] = val[cur], l[x] = l[cur], r[x] = r[cur]; // lazy[x] = lazy[cur];
        return x;
    }
    T comb(T a, T b) { return a + b; }
    void pull(int x) { val[x] = comb (val[l[x]], val[r[x]]); } 
//  void push(int cur, int L, int R) { 
//      if (!lazy[cur]) return;
//      if (L != R) {
//          l[cur] = copy(l[cur]);
//          val[l[cur]] += lazy[cur];
//          lazy[l[cur]] += lazy[cur];
//          
//          r[cur] = copy(r[cur]);
//          val[r[cur]] += lazy[cur];
//          lazy[r[cur]] += lazy[cur];
//      }
//      lazy[cur] = 0;
//  }
 
    //// MAIN FUNCTIONS
    T query(int cur, int lo, int hi, int L, int R) {  
        if (lo <= L && R <= hi) return val[cur];
        if (R < lo || hi < L) return 0;
        int M = (L+R)/2;
        return comb(query(l[cur],lo,hi,L,M), query(r[cur],lo,hi,M+1,R));
    }
    int upd(int cur, int pos, T v, int L, int R) {
        if (R < pos || pos < L) return cur;

        int x = copy(cur);
        if (pos <= L && R <= pos) { val[x] = v; return x; }
        
        int M = (L+R)/2;
        l[x] = upd(l[x],pos,v,L,M), r[x] = upd(r[x],pos,v,M+1,R);
        pull(x); return x;
    }
    int build(vector<T>& arr, int L, int R) {
        int cur = nex++;
        if (L == R) {
            if (L < (int) arr.size ()) val[cur] = arr[L];
            else val[cur] = T ();
            return cur;
        }

        int M = (L+R)/2;
        l[cur] = build(arr,L,M), r[cur] = build(arr,M+1,R);
        pull(cur); return cur;
    }
    
    //// PUBLIC
    vector<int> loc;
    void upd(int pos, T v) { loc.pb (upd (loc.back(), pos, v, 0, SZ-1)); }
    T query(int ti, int lo, int hi) { return query (loc[ti], lo, hi ,0 , SZ - 1); }
    void build(vector<T>& arr) { loc.pb (build(arr, 0, SZ - 1)); }
};
