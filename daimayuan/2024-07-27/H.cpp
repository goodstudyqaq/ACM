#include <bits/stdc++.h>

#include "./string/aho-corasick.hpp"
#include "./structure/others/binary-grouping.hpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;
using Data = string;
struct Structure {
    vector<Data> datas;
    AhoCorasick ac;
    virtual void add(const Data &d) {
        datas.emplace_back(d);
    }
    void build() {
        ac = AhoCorasick(2, '0');
        for (auto &d : datas) {
            ac.add(d, 0);
        }
        ac.build();
    }
    static Structure merge(const Structure &s1, const Structure &s2) {
        Structure new_s;
        for (auto &d : s1.datas) {
            new_s.add(d);
        }
        for (auto &d : s2.datas) {
            new_s.add(d);
        }
        new_s.build();
        return new_s;
    }

    int query(const string &s) {
        return ac.query(s);
    }

    size_t size() const { return datas.size(); }
};

void solve() {
    int m;
    cin >> m;
    int last_ans = 0;
    BinaryGrouping<Structure, Data> bg;

    auto query = [&](const string &s) {
        int res = 0;
        for (auto &st : bg.structures) {
            res += st.query(s);
        }
        return res;
    };

    set<string> S;
    while (m--) {
        string s;
        cin >> s;
        char s0 = s[0];
        s.erase(s.begin());
        int n = s.size();
        int shift = last_ans % n;
        string news = s.substr(shift, n - shift) + s.substr(0, shift);
        if (s0 == '+') {
            if (S.count(news)) continue;
            S.insert(news);
            bg.insert(news);
        } else {
            int ans = query(news);
            cout << ans << endl;
            last_ans = ans;
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << i << ":" << endl;
        solve();
    }
    return 0;
}