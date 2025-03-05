// Suffix Automaton

struct suffix_automaton {
	struct Node {
		int len, link;
		map<char, int> to;
		Node() : len(0), link(-1) {}
	};

	int n, sz, last;
	vector<Node> t;

	void add(char c) {
		int cur = sz++;
		t[cur].len = t[last].len + 1;
		int p = last;
		while (p != -1 && !t[p].to.count(c)) {
			t[p].to[c] = cur;
			p = t[p].link;
		}
		if (p == -1) {
			t[cur].link = 0;
		} else {
			int q = t[p].to[c];
			if (t[p].len + 1 == t[q].len) {
				t[cur].link = q;
			} else {
				int clone = sz++;
				t[clone].len = t[p].len + 1;
				t[clone].to = t[q].to;
				t[clone].link = t[q].link;
				while (p != -1 && t[p].to[c] == q) {
					t[p].to[c] = clone;
					p = t[p].link;
				}
				t[q].link = t[cur].link = clone;
			}
		}
		last = cur;
	}

	suffix_automaton(string &s) : n(s.size()), sz(1), last(0), t(2*n) {
		for (auto c: s) add(c);
	};
};
