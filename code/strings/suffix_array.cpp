//
//      Suffix Array

//      Description: Algorithm that sorts the suffixes of a string
//      Complexity: O(|s| log(|s|))
//      
//  Observation: There is a code below from KTH that is twice as faster.
//

// c26d8e
struct suffixArray {
    string s;
    vector<int> sa, lcp;
    int n;
    void cSort(int k, vector<int>& ra) {
        int maxi = max(300ll, n);
        vector<int> c(maxi, 0), temp_sa(n);
        for(int i = 0; i < n; i++)
            c[i + k < n ? ra[i + k] : 0]++;
        for(int i = 1; i < maxi; i++)
            c[i] += c[i - 1];
        for(int i = n - 1; i >= 0; i--)
            temp_sa[--c[sa[i] + k < n ? ra[sa[i] + k] : 0]] = sa[i];
        sa.swap(temp_sa);
    }
    suffixArray() {}
    suffixArray(vector<string>& v) {
        for(auto str: v) {
            s += str;
            s += '$';
        }
        n = s.size();
        sa.resize(n);
        vector<int> ra(n), temp_ra(n);
        for(int i = 0; i < n; i++) {
            ra[i] = s[i];
            sa[i] = i;
        }
        for(int k = 1; k < n; k <<= 1) {
            cSort(k, ra);
            cSort(0, ra);
            int r = temp_ra[sa[0]] = 0;
            for(int i = 1; i < n; i++)
                temp_ra[sa[i]] = (ra[sa[i]] == ra[sa[i - 1]] 
                                    && ra[sa[i] + k] == ra[sa[i - 1] + k]) ? r : ++r;
            ra.swap(temp_ra);
            if(r == n - 1) break;
        }
    }
    void computeLcp() {
        vector<int> phi(n);
        int k = 0;
        phi[sa[0]] = -1;
        for(int i = 1; i < n; i++)
            phi[sa[i]] = sa[i-1];
        vector<int> plcp(n);
        for(int i = 0; i < n - 1; i++) {
            if(phi[i] == -1) {
                plcp[i] = 0;
                continue;
            }
            while(s[i + k] == s[phi[i] + k]) k++;
            plcp[i] = k;
            k = max(k - 1, 0ll);
        }
        lcp.resize(n);
        for(int i = 0; i < n; i++)
            lcp[i] = plcp[sa[i]];
    }
};

// Suffix Array da KTH
// 528705
struct SuffixArray {
    string s;
    vector<int> sa, lcp;
    SuffixArray () {}
    SuffixArray(vector<string>& v, int lim=256) { // or basic_string<int>
        for(auto str : v) {
            s += str;
            s += '$';
        }
        int n = s.size(), k = 0, a, b;
        vector<int> x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
        sa = lcp = y, iota(all(sa), 0);
        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j, iota(all(y), n - j);
            for(int i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
            fill(all(ws), 0);
            for(int i = 0; i < n; i++) ws[x[i]]++;
            for(int i = 1; i < lim; i++) ws[i] += ws[i - 1];
            for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            for(int i = 1; i < n; i++) a = sa[i - 1], b = sa[i], x[b] =
                (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
        }
        for(int i = 1; i < n; i++) rank[sa[i]] = i;
        for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for (k && k--, j = sa[rank[i] - 1];
                    s[i + k] == s[j + k]; k++);
    }
};
