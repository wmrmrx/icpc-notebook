//  Gauss Xor - Gauss elimination mod 2
//  Description: Given a set of Vectors of size D,
//               maintains a basis of the set.
//  Complexity: query - O(D)
//              add - O(D)

//  Functions:
//      query(mask) - returns the biggest number that can
//                    be made if you initially have cur and
//                    it cannot be bigger than lim.
//      add(mask) - adds mask to the basis.

//  Details:
//      We are assuming the vectors have size D <= 64. For general
//      case, you may change ll basis[] for bitset<D> basis[].

const int logN = 30;

struct Gauss_xor {
    int basis[logN];
    Gauss_xor () { memset (basis, 0, sizeof (basis)); }
 
    void add (int x) {
        for (int j = logN - 1; j >= 0; j--) {
            if (x & (1ll << j)) {
                if (basis[j]) x ^= basis[j];
                else {
                    basis[j] = x;
                    return;
                }
            }
        }
    }
 
    int query (int j, int cur, int lim, bool mn) {
        if (j < 0) return cur;
        if (mn) {
            return query (j - 1, max (cur, cur ^ basis[j]), lim, 1);
        }
        else {
            if (lim & (1ll << j)) {
                if (cur & (1ll << j)) {
                    int res = query (j - 1, cur, lim, 0);
                    if (res) return res;
                }
                else {
                    if (basis[j]) {
                        int res = query (j - 1, cur ^ basis[j], lim, 0);
                        if (res) return res;
                    }
                }
                int val = min (cur, cur ^ basis[j]);
                if ((val & (1ll << j)) == 0) return query (j - 1, val, lim, 1);
                else return 0;
            }
            else {
                if (cur & (1ll << j)) {
                    if (!basis[j]) return 0;
                }
                return query (j - 1, min (cur, cur ^ basis[j]), lim, 0);
            }
        }
    }
};
