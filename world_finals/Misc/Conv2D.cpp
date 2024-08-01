vector<int> multiply(vector<vector<int>> a, vector<vector<int>> b){
	int na = a.size();
	int ma = a[0].size();
	int nb = b.size();
	int mb = b[0].size();
	int N = max(na,nb);
	int M = max(ma,mb);
	vector<int> A(N*M*2), B(N*M*2);
	for(int i = 0; i < na; i++){	
		for(int j = 0; j < ma; j++){
			A[i*M*2+j] = a[i][j];
		}
	}
	for(int i = 0; i < nb; i++){
		for(int j = 0; j < mb; j++){
			B[i*M*2+j] = b[i][j];
		}
	}
	vector<int> C = convMOD(A,B);
	int n = na+nb-1;
	int m = ma+mb-1;
	vector<<vector<int>> ret(n, vector<int>(m));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			int pos = i*M*2+j;
			pos += (n-1)*M*2+(m-1);
			ret[i][j] = C[pos];
		}
	}
	return ret;
}
