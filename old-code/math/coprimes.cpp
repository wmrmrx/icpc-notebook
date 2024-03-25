//  Coprimes
//  Description: 
//      Given a set o integers, calculates the quantity of integers
//      in the set coprimes with x. You can actually make queries on
//      anything related to the coprimes. For example, sum of comprimes.
//  Complexity: 
//      precalc - O(n logn)
//      add - O(sigma(N))
//      coprime - O(sigma(N))
//  Details:
//      It uses Mobius Function. To add or remove an integer of the set
//      just change sign to +1 or -1.

struct Coprimes {
    int n;
    vector<ll> cnt;
    vector<int> U;
    vector<vector<int>> fat;
    Coprimes () {}
    Coprimes (int n) : n(n), U(n), fat(n), cnt(n) {
        precalc ();
    }
    void precalc () {
        U[1] = 1;
        for (int i = 1; i < n; i++) fat[i].pb (1);
        for (int i = 1; i < n; i++) {
            for (int j = 2 * i; j < n; j += i) U[j] -= U[i];
            if (fat[i].size () == 1 && i > 1) {
                for (int j = i; j < n; j += i)
                    for (int k = fat[j].size () - 1; k >= 0; k--) 
                        fat[j].pb (i * fat[j][k]);
            }
        }
    }
    void add(int x, int sign){
        for(auto d : fat[x]) cnt[d] += sign;
    }
    ll coprimo(int x){
        ll quant = 0;
        for(auto d : fat[x]){
            quant += U[d] * cnt[d];
        }
        return quant;
    }
};
