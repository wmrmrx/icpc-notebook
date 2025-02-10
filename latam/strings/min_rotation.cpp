// Description: Finds the lexicographically smallest rotation of a string.
// Author: Stjepan Glavina
// License: Unlicense
// Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/MinRotation.h
// Time: O(N)
// Usage:
//  rotate(v.begin(), v.begin()+minRotation(v), v.end());

int min_rotation(string s) {
	int a = 0, n = s.size(); 
	s += s;
	for(int b=0;b<n;b++) for(int k=0;k<n;k++) {
		if (a+k == b || s[a+k] < s[b+k]) { 
			b += max<int>(0, k-1); 
			break; 
		}
		if (s[a+k] > s[b+k]) { 
			a = b; 
			break; 
		}
	}
	return a;
}
