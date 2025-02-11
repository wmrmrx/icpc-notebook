// Bit iterator
// iterator through all masks with n bits and m set bits
// use: for(auto it: BitIterator(n,m) { int mask = *it; ... }

struct BitIterator {
	struct Mask {
		uint32_t msk;
		Mask(uint32_t _msk): msk(_msk) {}
		bool operator!=(const Mask& rhs) const { return msk < rhs.msk; };
		void operator++(){const uint32_t t=msk|(msk-1);msk=(t+1)|(((~t&-~t)-1)>>__builtin_ffs(msk));}
		uint32_t operator*() const { return msk; }
	};
	uint32_t n, m;
	BitIterator(uint32_t _n, uint32_t _m): n(_n), m(_m) {}
	Mask begin() const { return Mask((1<<m)-1); }
	Mask end() const { return Mask((1<<n)); }
};
