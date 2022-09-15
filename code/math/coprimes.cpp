/*
    Coprimes
    Description: 
        Given a set o integers, calculates the quantity of integers
        in the set coprimes with x.
    Complexity: 
        precalc - O(n logn)
        add - O(sigma(N))
        coprime - O(sigma(N))
    Details:
        It uses Mobius Function. To add or remove an integer of the set
        just change sign to +1 or -1.
    e9bba1
*/
struct Coprimes {
    int n;
    vector<ll> U, cnt;
    vector<vector<int>> fat;
    Coprimes () {}
    Coprimes (int n) : n(n), U(n), fat(n), cnt(n) {
        precalc ();
    }
    void precalc () {
        for (int i = 1; i < n; i++) {
            for (int j = i; j < n; j += i) fat[j].pb(i); 
            if (i == 1) U[i] = 1;
            else if ((i / fat[i][1]) % fat[i][1] == 0) U[i] = 0;
            else U[i] = -U[i / fat[i][1]];
        }
    }
    void add(int x, int sign){
        for(auto d : fat[x]) cnt[d] += sign;
    }
    int coprimo(int x){
        int quant = 0;
        for(auto d : fat[x]){
            quant += U[d] * cnt[d];
        }
        return quant;
    }
};