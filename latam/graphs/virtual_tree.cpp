// Virtual Tree

namespace vtree {
	vector<int> vg[MAX];

	// receives list of vertexes and returns root of virtual tree
	// v must NOT be empty
	int build(vector<int> vs, LCA& lca) {
		auto cmp = [&](int i, int j) {
			return lca.pre[i] < lca.pre[j];
		};
		sort(all(vs), cmp);
		for(int i=vs.size()-1; i>0; i--) vs.push_back(lca.query(vs[i-1], vs[i]));
		sort(all(vs));
		vs.resize(unique(all(vs))-vs.begin());
		sort(all(vs), cmp);
		for(auto v: vs) vg[v].clear();
		for(int i=1;i<vs.size();i++) {
			int dad = lca.query(vs[i-1], vs[i]);
			vg[dad].push_back(vs[i]);
			vg[vs[i]].push_back(dad);
		}
		return vs[0];
	}
}
