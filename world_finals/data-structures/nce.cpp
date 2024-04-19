// NCE
// For each i, find nearest l < i < r such that 
// op(l, i), op(r, i) = true if they exist
// l = -1, r = v.size() otherwise
//
// Example: nce(v, greater<T>()): for each i returns
// nce[i] = {
//  biggest l < i such that v[l] > v[i]
//  smallest r > i such that v[r] > v[i]
// }
//
// Complexity: O(N)

template <typename T, typename OP>
vector<pair<int, int>> nce(vector<T> v, OP op) {
	int n = v.size();
	vector<pair<int, int>> res(n);
	vector<pair<T, int>> st;
	for(int i=0;i<n;i++) {
		while(!st.empty() && !op(st.back().first, v[i])) 
			st.pop_back();
		if(st.empty()) res[i].first = -1;
		else res[i].first = st.back().second;
		st.emplace_back(v[i], i);
	}
	st.clear();
	for(int i=n-1;i>=0;i--) {
		while(!st.empty() && !op(st.back().first, v[i])) 
			st.pop_back();
		if(st.empty()) res[i].second = n;
		else res[i].second = st.back().second;
		st.emplace_back(v[i], i);
	}
	return res;
}
