//Li Chao Tree
//add lines on a interval and ask minimum
//it is possible to do it sparse of persistent
//it is possible to only add in range with calling add_line
//log (n) in the intervals of the seg_tree
struct Line{
	int a, b;
	Line(): a(0), b(0) {}
	Line(int _a, int _b): a(_a), b(_b) {}

	int eval(int x){
		return a*x+b;
	}
};
struct LiChaoTree{
	vector<Line> seg;
	int n;
	LiChaoTree(int _n){
		n = _n;
		seg = vector<Line>(4*(n+1));
	}
	void add_line(int r, int i, int j, Line nw){
		int m = (i+j)/2;
		bool left = nw.eval(i) < seg[r].eval(i);
		bool mid = nw.eval(m) < seg[r].eval(m);
		if(mid){
			swap(seg[r],nw);
		}
		if(i == j) return;
		if(left != mid){
			add_line(2*r,i,m,nw);
		}else{
			add_line(2*r+1,m+1,j,nw);
		}
	}
	int get(int r, int i, int j, int x){
		int m = (i+j)/2;
		if(i == j){
			return seg[r].eval(x);
		}
		int ret;
		if(x <= m) ret = get(2*r,i,m,x);
		else ret = get(2*r+1,m+1,j,x);
		return min(ret, seg[r].eval(x));
	}
};