//  String Hashing
template<int MOD> 
struct str_hash {
    static int P;
    vector<ll> h, p;
    str_hash () {}
    str_hash(string s) : h(s.size()), p(s.size()) {
        p[0] = 1, h[0] = s[0];
        for (int i = 1; i < s.size(); i++)
            p[i] = p[i - 1]*P%MOD, h[i] = (h[i - 1]*P + s[i])%MOD;
    }
    ll operator()(int l, int r) { // retorna hash s[l...r]
        ll hash = h[r] - (l ? h[l - 1]*p[r - l + 1]%MOD : 0);
        return hash < 0 ? hash + MOD : hash;
    }
};
template<int MOD> int str_hash<MOD>::P = 1234; // l > |sigma|
struct Hash {
    str_hash<mod1> H1;
    str_hash<mod2> H2;
    Hash (string s) : H1(str_hash<mod1>(s)), H2(str_hash<mod2>(s)) {}
    ll operator()(int l, int r) {
        ll ret1 = H1(l, r), ret2 = H2(l, r);
        return (ret1 << 30) ^ (ret2);
    }
};
