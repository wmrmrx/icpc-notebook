struct AhoCorasick {

	struct node {
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

	// Adiciona uma string no aho corasick
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

		aho[cur].end++; // quantas strings esse no representa
	}

	// Calcula o suffix link dos nos
	void build() {
		queue<pair<char, int> > q;
		for(auto & [c, x] : aho[0].ch) {
			q.emplace(c, x);
		}

		while(q.size()) {
			char c; int cur;
			tie(c, cur) = q.front(); q.pop();

			int & j = aho[cur].suf;
			if(aho[cur].par) {
				j = aho[aho[cur].par].suf;
				while(j and aho[j].ch.count(c) == 0) j = aho[j].suf;
				if(aho[j].ch.count(c)) j = aho[j].ch[c];
			}

			// Se descomentado, guarda a quantidade de strings que sao sufixo da string representada por esse no
			// aho[cur].cnt = aho[cur].end + aho[aho[cur].suf].cnt;

			for(auto & [c, v] : aho[cur].ch) {
				q.emplace(c, v);
			}
		}
	}

	// Proximo estado do Aho Corasick automata. Retorna o no que representa a maior string sufixo da sequencia atual de caracteres
	int next_state(int st, char c) {
		while(st and aho[st].ch.count(c) == 0) st = aho[st].suf;
		if(aho[st].ch.count(c)) st = aho[st].ch[c];
		return st;
	}
};
