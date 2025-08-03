// iterator through all masks with n bits and m set bits
// usage: for(uint32_t msk: BitIterator(n,m) { ... }
struct BitIterator {
	struct Mask {
		uint32_t m;
		Mask(uint32_t _m): m(_m) {}
		bool operator!=(const Mask& rhs) const { return m < rhs.m; };
		void operator++(){const uint32_t t=m|(m-1);m=(t+1)|(((~t&-~t)-1)>>__builtin_ffs(m));}
		uint32_t operator*() const { return m; }
	};
	const uint32_t n, m;
	BitIterator(const uint32_t _n, const uint32_t _m): n(_n), m(_m) {}
	Mask begin() const { return Mask((1<<m)-1); }
	Mask end() const { return Mask((1<<n)); }
};
