//  Err Tree - Palindromic Tree

//  Description: A tree such that each node represents a 
//               palindrome of string s. It is possible to append
//               a character.
//  Complexity: Amortized O(|s|)
//

struct palindromic_tree {
    // node info
    vector<int> len, link, freq;
    vector<map<char, int>> to;

    int cur, cnt;
    palindromic_tree (int N): cur(1), cnt(2), len (N), link (N), to (N), freq (N) { len[0] = -1; }
    void add(int i, string& s) {
        int p = len[cur] == i ? link[cur] : cur;
        while (s[i - len[p] - 1] != s[i]) p = link[p];
        if (to[p].find(s[i]) != to[p].end()) cur = to[p][s[i]];
        else {
            int L = link[p];
            while (s[i - len[L] - 1] != s[i]) L = link[L];
            L = max<int>(1, to[L][s[i]]);
            cur = to[p][s[i]] = cnt;
            len[cnt] = len[p] + 2; link[cnt] = L;
            cnt++;
        }
        freq[cur]++;
    }
    void insert(string& s) {
        for (int i = 0; i < s.size (); i++)
            add(i, s);
    }
};