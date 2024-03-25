// Mint
template <const int MOD>
struct mint {
	int x;
	mint(): x(0) {}
	mint(int _x): x(_x%MOD<0?_x%MOD+MOD:_x%MOD) {}
	void operator+=(mint rhs) { x+=rhs.x; if(x>=MOD) x-=MOD; }
	void operator-=(mint rhs) { x-=rhs.x; if(x<0)x+=MOD; }
	void operator*=(mint rhs) { x*=rhs.x; x%=MOD; }
	void operator/=(mint rhs) { *this *= rhs.inv(); }
	mint operator+(mint rhs) { mint res=*this; res+=rhs; return res; }
	mint operator-(mint rhs) { mint res=*this; res-=rhs; return res; }
	mint operator*(mint rhs) { mint res=*this; res*=rhs; return res; }
	mint operator/(mint rhs) { mint res=*this; res/=rhs; return res; }
	mint inv() { return this->pow(MOD-2); }
	mint pow(int e) {
		mint res(1);
		for(mint p=*this;e>0;e/=2,p*=p) if(e%2)
			res*=p;
		return res;
	}
};
