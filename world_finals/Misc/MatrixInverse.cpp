// Description: Invert matrix $A$. Returns rank; result is stored in $A$ unless singular (rank < n).
int matInv(vector<vector<double>>& A) {
	int n = A.size(); vector<int> col(n);
	vector<vector<double>> tmp(n, vector<double>(n));
	for(int i = 0; i < n; i++) tmp[i][i] = 1, col[i] = i;
	for(int i = 0; i < n; i++) {
		int r = i, c = i;
		for(int j = i; j < n; j++){
			for(int k = i; k < n; k++){
				if (fabs(A[j][k]) > fabs(A[r][c]))
					r = j, c = k;
			}
		}
		if (fabs(A[r][c]) < 1e-12) return i;
		A[i].swap(A[r]); tmp[i].swap(tmp[r]);
		for(int j = 0; j < n; j++)
			swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
		swap(col[i], col[c]);
		double v = A[i][i];
		for(int j = i+1; j < n; j++) {
			double f = A[j][i] / v;
			A[j][i] = 0;
			for(int k = i+1; k < n; k++)
				A[j][k] -= f*A[i][k];
			for(int k = 0; k < n; k++)
				tmp[j][k] -= f*tmp[i][k];
		}
		for(int j = i+1; j < n; j++) A[i][j] /= v;
		for(int j = 0; j < n; j++) tmp[i][j] /= v;
		A[i][i] = 1;
	}
	/// forget A at this point, just eliminate tmp backward
	for (int i = n-1; i > 0; --i) {
		for(int j = 0; j < i; j++){
			double v = A[j][i];
			for(int k = 0; k < n; k++)
				tmp[j][k] -= v*tmp[i][k];
		}
	}
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			A[col[i]][col[j]] = tmp[i][j];
	return n;
}
