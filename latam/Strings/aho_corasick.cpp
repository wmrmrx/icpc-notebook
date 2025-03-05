// Aho-Corasick
//
// Description: data structure that allows search
// for multiple patterns in text.
//
// Details: K is the alphabet size, in template
// it is using alphabet from 'a' to 'z' with offset 'a'.
//
// Useful property: O(sqrt(N)) 'term_link' when ascending the tree.

template <const int K = 26>
struct aho_corasick {
	struct node {
		int next[K], len,
			link, // suffix link
			term_link; // suffix link to "first" terminal state
		bool is_term; // terminal state (i.e., a word from dictionary ends here)
		node() : link(-1), term_link(-1), is_term(false) {
			fill(next, next+K, -1);
		}
	};

	vector<node> t;

	aho_corasick() : t(1) {}
	aho_corasick(int size) : t(1) { t.reserve(size); }

	int new_node() {
		t.emplace_back();
		return t.size()-1;
	}

	// O(|s|)
	void add_string(const string& s) {
		int u = 0;
		for (const char& ch: s) {
			int c = ch - 'a';
			if (t[u].next[c] == -1) t[u].next[c] = new_node();
			u = t[u].next[c];
		}
		t[u].is_term = true, t[u].len = s.size();
	}

	// O(|dictionary size|)
	void build() {
		queue<int> q; q.push(0);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (int c = 0; c < K; c++) if (t[u].next[c] != -1) {
				int v = t[u].next[c], l = t[u].link;
				while (l != -1 and t[l].next[c] == -1) {
					l = t[l].link;
				}
				t[v].link = (l == -1? 0: t[l].next[c]);
				t[v].term_link = (t[t[v].link].is_term? t[v].link: t[t[v].link].term_link);
				q.push(v);
			}
		}
	}

	// O(|dictionary size|)
	void add_dictionary(const vector<string>& dict) {
		for (const string& s: dict) add_string(s);
		build();
	}
};
