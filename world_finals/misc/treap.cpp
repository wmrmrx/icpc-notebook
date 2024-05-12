/*
ecnerwala's code , from https://codeforces.com/contest/1558/submission/126874038
*/

static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
std::mt19937 mt(FIXED_RANDOM);
struct treap_node {
	std::array<treap_node*, 2> c{nullptr, nullptr};
	std::mt19937::result_type pri = mt();
	int lazy = 0;
	int v;
 
	void apply(int l) {
		v += l;
		lazy += l;
	}
 
	void downdate() {
		if (lazy) {
			if (c[0]) c[0]->apply(lazy);
			if (c[1]) c[1]->apply(lazy);
			lazy = 0;
		}
	}
};

/*
this code just merge if max(a) <= min(b), don't deal with complex merges
*/
treap_node* merge(treap_node* a, treap_node* b) {
	if (!b) return a;
	if (!a) return b;
 
	treap_node* r;
	if (a->pri < b->pri) {
		r = a;
		a->downdate();
		r->c[1] = merge(a->c[1], b);
	} else {
		r = b;
		b->downdate();
		r->c[0] = merge(a, b->c[0]);
	}
	return r;
}
 
std::pair<treap_node*, treap_node*> split(treap_node* r, int y) {
	if (!r) return {nullptr, nullptr};
	r->downdate();
	treap_node *a, *b;
	if (r->v >= y) {
		b = r;
		std::tie(a, b->c[0]) = split(r->c[0], y);
	} else {
		a = r;
		std::tie(a->c[1], b) = split(r->c[1], y);
	}
	return {a, b};
}

treap_node* add(treap_node* a, treap_node* node, int y){
	node->v = y;
	auto [l, r] = split(a, y);
	treap_node* ROOT;
	ROOT = merge(l, node);
	ROOT = merge(ROOT, r);
	return ROOT;
}

treap_node* find(treap_node *a, int y){
	if(!a) return nullptr;
	a->downdate();
	treap_node* b;
	if(a->v == y){
		b = a;
	}else if(a->v < y){
		b = find(a->c[1], y);
	}else{
		b = find(a->c[0], y);
	}
	return b;
}
