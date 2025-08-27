struct state {
    int len, link;
    map<char, int> next;
	vector<int> childs;
	long long cnt;
};
state st[MAXN*2];
int sz, last;
void sa_init() {
    st[0].len = 0; st[0].link = -1;
	st[0].cnt = 1; sz++; last = 0;
}
void sa_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
	st[cur].cnt = 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
			st[clone].cnt = 0;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}
void dfsArvore(int u){
	for(auto v : st[u].childs) dfsArvore(v);
	if(st[u].link != -1){
		st[st[u].link].cnt += st[u].cnt;
	}
}
void build(string &s){
	sa_init();
	for(auto c : s){
		sa_extend(c);
	}
	for(int i = 1; i < sz; i++){
		int v = st[i].link;
		st[v].childs.pb(i);
	}
	dfsArvore(0);
	st[0].cnt = 0;
}
