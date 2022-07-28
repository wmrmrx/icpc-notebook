// iterator through all masks with n bits and m set bits
// use: for(auto it: BitIterator(n,m) { int mask = *it; ... }
// e7a130
struct BitIterator {
	struct Mask {
		uint32_t mask;
		Mask(uint32_t mask): mask(mask) {}
		bool operator!=(const Mask& rhs) const { return mask < rhs.mask; };
		void operator++(){const uint32_t t=mask|(mask-1);mask=(t+1)|(((~t&-~t)-1)>>__builtin_ffs(mask));}
		uint32_t operator*() const { return mask; }
	};
	const uint32_t n, m;
	BitIterator(const uint32_t n, const uint32_t m): n(n), m(m) {}
	Mask begin() const { return Mask((1<<m)-1); }
	Mask end() const { return Mask((1<<n)); }
};
