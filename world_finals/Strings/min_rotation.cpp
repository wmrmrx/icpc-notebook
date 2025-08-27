// Source: https://github.com/stjepang/snippets/blob/master/min_rotation.cpp
// Finds the lexicographically smallest rotation of a string in O(N)
// Usage:
// rotate(v.begin(), v.begin()+min_rotation(v), v.end());
// template <typename T> int min_rotation(basic_string<T> s) {
int min_rotation(string s) {
	int a = 0, n = s.size(); s += s;
	for(int b=0;b<n;b++) for(int k=0;k<n;k++) {
		if( a+k == b || s[a+k] < s[b+k] ) { b += max<int>(0, k-1); break; }
		if( s[a+k] > s[b+k] ) { a = b; break; }
	}
	return a;
}
