static const uint64_t FIXED_RANDOM = 12341231;
std::mt19937 mt(FIXED_RANDOM);
struct treap_node {
	std::array<treap_node*, 2> c{nullptr, nullptr};
	std::mt19937::result_type pri = mt();
	int lazy = 0, lazyf = 0, flip = 0, v;
	ll soma = 0, eu = 0;
	void apply(int a, int b) {
		if(b){
			swap(c[0],c[1]);
			v *= -1;
			lazy *= -1;
			lazyf ^= 1;
		}
		v += a; lazy += a;
	}
	void downdate() {
		if (lazy) {
			if (c[0]) c[0]->apply(lazy, lazyf);
			if (c[1]) c[1]->apply(lazy, lazyf);
			lazy = lazyf = 0;
		}
	}
	void update() {
		soma = eu;
		if(c[0]) soma += c[0]->soma;
		if(c[1]) soma += c[1]->soma;
	}
};
// this code just merge if max(a) <= min(b), don't deal with complex merges
treap_node* merge(treap_node* a, treap_node* b) {
	if (!b){
		a->update();
		return a;
	}
	if (!a){
		b->update();
		return b;
	}
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
	if(r) r->update(); 
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
	if(a) a->update();
	if(b) b->update();
	return {a, b};
}
treap_node* add(treap_node* a, treap_node* node, int y, int eu){
	node->v = y;
	node->eu = eu;
	auto [l, r] = split(a, y);
	treap_node* ROOT;
	ROOT = merge(l, node);
	ROOT = merge(ROOT, r);
	return ROOT;
}
//reverte L to R, a is a tree where the keys 
//are from 1 to N, 1 <= L <= R <= N
treap_node* reverte(treap_node *a, int L, int R){
	if(!a) return a;
	int tam = R-L+1;
	treap_node*x,*y,*z;
	tie(x,y) = split(a,L);
	tie(y,z) = split(y,R+1);
	if(y && tam >= 2){
		y->apply(R+L,1);
	}
	a = merge(x,y); a = merge(a,z);
	return a;
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
	b->update();
	return b;
}