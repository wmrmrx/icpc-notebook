//  MO algorithm

//  Description: 
//      Answers queries offline with sqrt decomposition.
//  Complexity: 
//      exec - O(n*sqrt(n)*O(remove / add))
const int magic = 230;

struct Query {
    int l, r, idx;
    Query () {}
    Query (int _l, int _r, int _idx) : l(_l), r(_r), idx(_idx) {}
    bool operator < (const Query &o) const {
        return mp(l / magic, r) < mp(o.l / magic, o.r);
    }
};

struct MO {
    int sum;
    MO(vector<ll> &v) : sum(0), v(v), cnt(N), C(N) {}

    void exec(vector<Query> &queries, vector<ll> &answers) {
        answers.resize(queries.size());
        sort(queries.begin(), queries.end());

        int cur_l = 0;
        int cur_r = -1;

        for (Query q : queries) {
            while (cur_l > q.l) {
                cur_l--;
                add(cur_l);
            }
            while (cur_r < q.r) {
                cur_r++;
                add(cur_r);
            }
            while (cur_l < q.l) {
                remove(cur_l);
                cur_l++;
            }
            while (cur_r > q.r) {
                remove(cur_r);
                cur_r--;
            }
            answers[q.idx] = get_answer(cur_l, cur_r);
        }
    }

    void add(int i) {
        sum += v[i];
    }

    void remove(int i) {
        sum -= v[i];
    }

    ll get_answer(int l, int r) {
        return sum;
    }
};
