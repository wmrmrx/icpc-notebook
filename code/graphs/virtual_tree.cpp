// 5badc5
namespace vtree {
	vector<int> vg[MAX];

	// receives list of vertexes and returns root of virtual tree
	// v must NOT be empty
	int build(vector<int> v, LCA& lca) {
		auto cmp = [&](int i, int j) {
			return lca.pre[i] < lca.pre[j];
		};
		sort(all(v), cmp);
		for(int i=0;i+1<v.size();i++) v.push_back(lca.query(v[i], v[i+1]));
		sort(all(v), cmp);
		v.resize(unique(all(v))-v.begin());
		for(auto x: v) vg[x].clear();
		for(int i=1;i<v.size();i++) {
			int dad = lca.query(v[i-1], v[i]);
			vg[dad].push_back(v[i]);
			vg[v[i]].push_back(dad);
		}
		return v[0];
	}
}
