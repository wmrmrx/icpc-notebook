// Fast Suffix Array
// Around ~3x faster than kactl suffix array template
// Source: https://judge.yosupo.jp/submission/52300
//
// Given a vector<int>/string s, compute its SA and LCP
//      vector<int> sa = suffix_array::suffix_array(s);
//      vector<int> lcp = suffix_array::lcp(sa, s);
//
// (No need to add a "$" to end of string)

namespace suffix_array {
    void induced_sort(vector<int> &vec, int val_range, vector<int> &sa, vector<bool> &sl, vector<int> &lms_idx) {
	vector<int> l(val_range), r(val_range);
	for (int c : vec) {
	    if (c + 1 < val_range) ++l[c + 1];
	    ++r[c];
	}
	partial_sum(all(l), l.begin());
	partial_sum(all(r), r.begin());
	fill(all(sa), -1);
	for (int i = int(lms_idx.size()) - 1; i >= 0; --i)
	    sa[ --r[ vec[ lms_idx[i] ] ] ] = lms_idx[i];
	for (int i : sa)
	    if ( i >= 1 && sl[i - 1] ) {
		sa[ l [ vec[i - 1]]++ ] = i - 1;
	    }
	fill(all(r), 0);
	for (int c : vec)
	    ++r[c];
	partial_sum(all(r), r.begin());
	for (int k = int(sa.size()) - 1, i = sa[k]; k >= 1; --k, i = sa[k])
	    if (i >= 1 && !sl[i - 1]) {
		sa[ --r[ vec[i - 1] ] ] = i - 1;
	    }
    }

    vector<int> sa_is(vector<int> &vec, int val_range) {
	const int n = vec.size();
	vector<int> sa(n), lms_idx;
	vector<bool> sl(n);
	sl[n - 1] = false;
	for (int i = n - 2; i >= 0; i--) {
	    sl[i] = (vec[i] > vec[i + 1] || (vec[i] == vec[i + 1] && sl[i + 1]));
	    if (sl[i] && !sl[i + 1]) lms_idx.push_back(i + 1);
	}
	reverse(all(lms_idx));
	induced_sort(vec, val_range, sa, sl, lms_idx);
	vector<int> new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
	for (int i = 0, k = 0; i < n; i++)
	    if (!sl[sa[i]] && sa[i] >= 1 && sl[sa[i] - 1]) {
		new_lms_idx[k++] = sa[i];
	    }
	int cur = 0;
	sa[n - 1] = cur;
	for (size_t k = 1; k < new_lms_idx.size(); k++) {
	    int i = new_lms_idx[k - 1], j = new_lms_idx[k];
	    if (vec[i] != vec[j]) {
		sa[j] = ++cur;
		continue;
	    }
	    bool flag = false;
	    for (int a = i + 1, b = j + 1;; ++a, ++b) {
		if (vec[a] != vec[b]) {
		    flag = true;
		    break;
		}
		if ((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) {
		    flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1]));
		    break;
		}
	    }
	    sa[j] = (flag ? ++cur : cur);
	}
	for (size_t i = 0; i < lms_idx.size(); ++i)
	    lms_vec[i] = sa[lms_idx[i]];
	if (cur + 1 < (int)lms_idx.size()) {
	    auto lms_sa = sa_is(lms_vec, cur + 1);
	    for (size_t i = 0; i < lms_idx.size(); ++i) {
		new_lms_idx[i] = lms_idx[lms_sa[i]];
	    }
	}
	induced_sort(vec, val_range, sa, sl, new_lms_idx);
	return sa;
    }

    template <typename T>
    vector<int> suffix_array(const T &s) {
	int sz = s.size();
	vector<int> v(sz + 1);
	int mn = *min_element(all(s)), mx = *max_element(all(s));
	for(int i = 0; i < sz; i++)
		v[i] = int(s[i]) - mn + 1;
	auto ret = sa_is(v, mx - mn + 2);
	ret.erase(ret.begin());
	return ret;
    }

    template <typename T>
    vector<int> lcp(const T &s, const vector<int> &sa) {
	int n = s.size(), k = 0;
	vector<int> lcp(n), rank(n);
	for (int i = 0; i < n; i++) rank[sa[i]] = i;
	for (int i = 0; i < n; i++, k ? k-- : 0) {
	    if (rank[i] == n - 1) {
		k = 0;
		continue;
	    }
	    int j = sa[rank[i] + 1];
	    while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++ k;
	    lcp[rank[i]] = k;
	}
	lcp.pop_back();
	return lcp;
    }
}
