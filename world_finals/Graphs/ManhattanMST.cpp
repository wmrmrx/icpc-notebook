// Computes O(n) edges that contains all the edges of the  Manhattan MST
// of a set of points int the 2D plane. Must apply Kruskal to these edges
// to obtain the actual MST.
//
// xs - (input) coordinates in the x-axis
// ys - (input) coordinates in the y-axis
// E - superset of the manhattan MST edges
//
// Complexity: O(n logn)	

vector<pair<ll, pair<int, int>> > E;

void manhattan_mst(vector<ll> xs, vector<ll> ys){
	int n = xs.size();
	vector<int> ord(n);
	for(int i = 0; i < n; i++) ord[i] = i;
	for(int s = 0; s < 2; s++) {
		for(int t = 0; t < 2; t++) {
			auto cmp = [&](int i, int j) -> bool {
				if(xs[i] + ys[i] == xs[j] + ys[j]) return ys[i] < ys[j];
				return xs[i] + ys[i] < xs[j] + ys[j];
			};
			sort(ord.begin(), ord.end(), cmp);
			map<int, int> id;
			for(int i: ord) {
				for(auto it = id.lower_bound(-ys[i]); it != id.end(); it = id.erase(it)) {
					int j = it->second;
					if(xs[j] - ys[j] > xs[i] - ys[i]) break;
					E.pb(pair(abs(xs[i] - xs[j]) + abs(ys[i] - ys[j]), pair(i, j)));
				}
				id[-ys[i]] = i;
			}
			swap(xs,ys);
		}
		for(int i = 0; i < n; i++) xs[i] *= -1;
	}
}
