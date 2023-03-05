// Extended gcd
// returns X, Y such that a*X + b*Y = gcd(a, b)
pair<int,int> egcd(int a, int b) {
	if(b == 0) return {1, 0};
	auto [x, y] = egcd(b, a%b);
	return {y, x - y * (a/b)};
}
