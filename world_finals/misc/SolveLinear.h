/**
 * Author: Per Austrin, Simon Lindholm
 * Date: 2004-02-08
 * License: CC0
 * Description: Solves $A * x = b$. If there are multiple solutions, an arbitrary one is returned.
 *  Returns rank, or -1 if no solutions. Data in $A$ and $b$ is lost.
 * Time: O(n^2 m)
 * Status: tested on kattis:equationsolver, and bruteforce-tested mod 3 and 5 for n,m <= 3
 */
typedef vector<double> vd;
const double eps = 1e-12;

int solveLinear(vector<vd>& A, vd& b, vd& x) {
	int n = A.size(), m = x.size(), rank = 0, br, bc;
	if (n) assert(int32_t(A[0].size()) == m);
	vector<int> col(m); iota(all(col), 0);
	
	for(int i = 0; i < n; i++){
		double v, bv = 0;
		for(int r = i; r < n; r++){
			for(int c = i; c < m; c++){
				if ((v = fabs(A[r][c])) > bv)
					br = r, bc = c, bv = v;
			}
		}
		if (bv <= eps) {
			for(int j = i; j < n; j++){
				if (fabs(b[j]) > eps) return -1;
			}
			break;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		for(int j = 0; j < n; j++){
			swap(A[j][i], A[j][bc]);
		}
		bv = 1/A[i][i];
		for(int j = i+1; j < n; j++){
			double fac = A[j][i] * bv;
			b[j] -= fac * b[i];
			for(int k = i+1; k < m; k++){
				A[j][k] -= fac*A[i][k];
			}
		}
		rank++;
	}

	x.assign(m, 0);
	for (int i = rank; i--;) {
		b[i] /= A[i][i];
		x[col[i]] = b[i];
		for(int j = 0; j < i; j++){
			b[j] -= A[j][i] * b[i];
		}
	}
	return rank; // (multiple solutions if rank < m)
}
