// Dirichlet Trick
// Description:
//      Find the partial sum of a multiplicative function.
//      This code works for Phi or Mobius functions.
// Details:
//      It is necessary to precalculate the values of at least
//      sqrt (N). But, the optimal value might be around N^(2/3)

namespace Dirichlet {
    vector<int> f;
    map<int,int> mp;

    void init (vector<int> &mul_func) {
        f.resize (mul_func.size ());
        for (int i = 1; i < mul_func.size (); i++) f[i] = f[i - 1] + mul_func[i];
    }

    int calc (int x) {
        if(x<=N) return f[x];
        if(mp.find(x)!=mp.end()) return mp[x];
        int ans = x * (x + 1) / 2;
        for(int i = 2, r; i <= x; i = r + 1) {
            r=x/(x/i);
            ans -= calc(x/i)*(r-i+1);
        }
        return mp[x]=ans;
    }
}
