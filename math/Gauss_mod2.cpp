/*
    Gauss_xor - Gauss elimination mod 2
    Description: Given a set of Vectors of size D,
                 maintains a basis of the set.
    Complexity: check - O(D)
                add - O(D)

    Functions:
        check(mask) - returns true if the mask can be represented
                      by the basis;
        add(mask) - adds mask to the basis if it is independent.

    Details:
        We are assuming the vectors have size D <= 64. For general
        case, you may change ll basis[] for bitset<D> basis[].
    e45fa9
*/

const int logN = 30;

struct Gauss_xor {
    ll sz, basis[logN];

    Gauss_xor () {
        sz = 0;
        for(int i = 0; i < logN; i++)
            basis[i] = 0;
    }

    bool check (ll mask) {
        for(int i = 0; i < logN; i++) {
            if(((1ll << i) & mask) == 0) continue;
            if(!basis[i]) return false;
            mask ^= basis[i];
        }
        return true;
    }

    void add (ll mask) {
        for (int i = 0; i < logN; i++) {
            if(!((1ll << i) & mask)) continue;
            if(!basis[i]) {
                sz++;
                basis[i] = mask;
                return;
            }
            mask ^= basis[i];
        }
    }
};