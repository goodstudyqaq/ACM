#line 1 "test/yosupo-line-add-get-min.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"
#include <bits/stdc++.h>

#line 2 "structure/others/binary-grouping.hpp"
using namespace std;

/*
struct Structure {
    vector<Data> datas;
    virtual void add(const Data &d) {
        datas.emplace_back(d);
    }
    void build() {
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


    size_t size() const { return datas.size(); }
};
*/

template <typename Structure, typename Data>
struct BinaryGrouping {
    vector<Structure> structures;
    const function<Structure(const Structure &, const Structure &)> merge;
    BinaryGrouping() : merge(Structure::merge) {}

    void insert(const Data &d) {
        Structure s;
        s.add(d);
        s.build();

        structures.emplace_back(s);

        while (structures.size() >= 2 && structures[structures.size() - 1].size() == structures[structures.size() - 2].size()) {
            Structure new_s = merge(structures[structures.size() - 1], structures[structures.size() - 2]);
            structures.pop_back();
            structures.pop_back();
            structures.emplace_back(new_s);
        }
    }
};
#line 5 "test/yosupo-line-add-get-min.test.cpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;
using Data = pair<long long, long long>;

Data operator-(const Data &a, const Data &b) {
    return Data(a.first - b.first, a.second - b.second);
}

long long operator*(const Data &a, const Data &b) {
    return a.first * b.second - a.second * b.first;
}

struct Structure {
    vector<Data> datas;
    vector<Data> convexHull;
    virtual void add(const Data &d) {
        datas.emplace_back(d);
    }

    inline int sgn(long long x) { return x == 0 ? 0 : (x < 0 ? -1 : 1); }

    bool check(const Data &a, const Data &b, const Data &c) {
        // return (b.F-a.F)*(c.S-b.S) >= (b.S-a.S)*(c.F-b.F); return ab * bc >= 0
        if (b.first == a.first || c.first == b.first) {
            return sgn(b.first - a.first) * sgn(c.second - b.second) >= sgn(c.first - b.first) * (b.second - a.second);
        }
        // return (b.second - a.second) / (a.first - b.first) >= (c.second - b.second) / (b.first - c.first);

        Data ab = b - a;
        Data bc = c - b;

        if (sgn(ab.first) * sgn(bc.second) != sgn(ab.second) * sgn(bc.first)) {
            return sgn(ab.first) * sgn(bc.second) >= sgn(ab.second) * sgn(bc.first);
        }

        Data left = {bc.second / bc.first, bc.second % bc.first};
        Data right = {ab.second / ab.first, ab.second % ab.first};

        if (left.first != right.first) {
            return left.first >= right.first;
        }

        return left.second * ab.first >= right.second * bc.first;
    }

    void build() {
        convexHull.clear();
        sort(datas.begin(), datas.end());
        int tp = 0;
        vector<int> stk;
        stk.push_back(0);
        int n = datas.size();
        for (int i = 1; i < n; i++) {
            while (stk.size() >= 2 && check(datas[i], datas[stk.back()], datas[stk[stk.size() - 2]])) {
                stk.pop_back();
            }
            stk.push_back(i);
        }

        for (int i = 0; i < stk.size(); i++) {
            convexHull.emplace_back(datas[stk[i]]);
        }
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

    long long query(long long x) {
        // if (convexHull.size() == 1) {
        //     return convexHull[0].first * x + convexHull[0].second;
        // }
        debug(convexHull);
        long long res = numeric_limits<long long>::max() / 2;
        res = min(convexHull[0].first * x + convexHull[0].second, convexHull.back().first * x + convexHull.back().second);
        int l = 0, r = convexHull.size() - 2;
        while (l <= r) {
            int m = l + r >> 1;
            long long tmp1 = convexHull[m].first * x + convexHull[m].second;
            long long tmp2 = convexHull[m + 1].first * x + convexHull[m + 1].second;
            if (tmp1 > tmp2) {
                res = min(res, tmp2);
                l = m + 1;
            } else {
                res = min(res, tmp1);
                r = m - 1;
            }
        }
        return res;
    }

    size_t size() const { return datas.size(); }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    BinaryGrouping<Structure, Data> bg;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        long long a, b;
        cin >> a >> b;
        bg.insert({a, b});
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            long long a, b;
            cin >> a >> b;
            bg.insert({a, b});
        } else {
            long long p;
            cin >> p;
            auto &structures = bg.structures;
            long long res = numeric_limits<long long>::max() / 2;
            for (auto &s : structures) {
                res = min(res, s.query(p));
            }
            cout << res << endl;
        }
    }
    return 0;
}
