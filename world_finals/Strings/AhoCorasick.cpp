struct AhoCorasick {
	// const int AL = 26;
	struct node {
		//array<int,AL> ch;
		//array<int,AL> dp;
		map<char, int> ch;
		int par, suf, end;
	};
	vector<node> aho;
	int new_node() {
		aho.emplace_back();
		return (int) aho.size() - 1;
	}
	AhoCorasick() {
		aho.resize(1);
	}
	void add(string & s) {
		int cur = 0;
		for(auto c : s) {
			if(aho[cur].ch.count(c) == 0) {
				int x = new_node();
				aho[cur].ch[c] = x;
				aho[x].par = cur;
			}
			cur = aho[cur].ch[c];
		}
		aho[cur].end++; 
	}
	void build() {
		queue<pair<char, int> > q;
		for(auto & [c, x] : aho[0].ch) {
			q.emplace(c, x);
		}
		//for(int i = 0; i < AL; i++) if(aho[0].ch[i] != 0){
		//	q.emplace(i,aho[0].ch[i]);
		//	aho[0].dp[i] = aho[0].ch[i];
		//}
		while(q.size()) {
			char c; int cur;
			tie(c, cur) = q.front(); q.pop();
			int & j = aho[cur].suf;
			if(aho[cur].par) {
				//j = aho[aho[cur].par].suf;
				//j = aho[j].dp[c];
				j = aho[aho[cur].par].suf;
				while(j and aho[j].ch.count(c) == 0) j = aho[j].suf;
				if(aho[j].ch.count(c)) j = aho[j].ch[c];
			}
			//for(int i = 0; i < AL; i++){
			//	if(aho[cur].ch[i]){
			//		aho[cur].dp[i] = aho[cur].ch[i];
			//		q.emplace(i,aho[cur].ch[i]);
			//	}else{
			//		aho[cur].dp[i] = aho[j].dp[i];
			//	}
			//}
			for(auto & [c, v] : aho[cur].ch) {
				q.emplace(c, v);
			}
		}
	}
	int next_state(int st, char c) {
		// return aho[st].dp[c-'a'];
		while(st and aho[st].ch.count(c) == 0) st = aho[st].suf;
		if(aho[st].ch.count(c)) st = aho[st].ch[c];
		return st;
	}
};
