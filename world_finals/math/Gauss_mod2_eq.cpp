//  Gauss elimination - modulo 2

//  Description: 
//      Solves a linear system with n equations and m - 1 variables.
//      Is faster duo to the use of bitset.
//  Complexity: O(n^2 * m / 32)


//  Details:
//      Function solve return a boolean indicating if system is possible
//      or not. Also, if it is possible, the parameter maintains the answer.

struct Gauss_mod2 {
    int n, m;
    array<int, M> pos;
    int rank = 0;
    vector<bitset<M>> a;
 
    // n equations, m-1 variables, last column is for coefficients
    Gauss_mod2(int n, int m, vector<bitset<M>> &a): n(n), m(m), a(a) {
        pos.fill(-1);
    }
 
    int solve(bitset<M> &ans) {
        for (int col = 0, row = 0; col < m && row < n; col++) {
            int one = -1;
            for (int i = row; i < n; i++) {
                if (a[i][col]) {
                    one = i;
                    break;
                }
            }
 
            if (one == -1) { continue; }
 
            swap(a[one], a[row]);
 
            pos[col] = row;
 
            for (int i = row + 1; i < n; i++) {
                if (a[i][col])
                    a[i] ^= a[row];
            }
            ++row, ++rank;
        }
 
        ans.reset();
 
        for (int i = m - 1; i >= 0; i--) {
            if (pos[i] == -1) ans[i] = true;
            else {
                int k = pos[i];
                for (int j = i + 1; j < m; j++) if (a[k][j]) ans[i] = ans[i] ^ ans[j];
                ans[i] = ans[i] ^ a[k][m];
            }
        }
 
        for (int i = rank; i < n; i++) if (a[i][m]) return 0;
 
        return 1;
    }
};
