#include <bits/stdc++.h>

#include <limits>

#include "./structure/others/md-vector.hpp"

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

typedef md_vector<int, 2> mat;

template <typename T>
struct MinQueue {
    vector<pair<T, T>> st1, st2;
    // 注意顺序
    function<T(T&, T&, bool)> f;

    MinQueue() = default;

    MinQueue(function<T(T&, T&, bool)> &f) : f(f) {}

    void push(T &a) {
        if (!st1.empty()) {
            st1.push_back({a, f(st1.back().second, a, 1)});
        } else {
            st1.push_back({a, a});
        }
    }

    void pop() {
        if (st2.empty()) {
            st2 = st1;
            reverse(st2.begin(), st2.end());
            st1.clear();

            st2[0].second = st2[0].first;
            for (int i = 1; i < st2.size(); i++) {
                st2[i].second = f(st2[i].first, st2[i - 1].second, 0);
            }
        }
        st2.pop_back();
    }

    T get() {
        if (st1.empty()) {
            return st2.back().second;
        }
        if (st2.empty()) {
            return st1.back().second;
        }

        T res = f(st2.back().second, st1.back().second, 0);
        return res;
    }
};
void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = s[i] - '0';
    }

    const int inf = numeric_limits<int>::max() / 2;
    vector<md_vector<int, 2>> transfer(10, md_vector<int, 2>({10, 10}, inf));

    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            transfer[i][j][0] = j;
            transfer[i][j][j] = j;
        }
        transfer[i][0][i] = 0;
    }
    function<mat(mat&, mat&, bool)> mul = [&](mat& a, mat& b, bool fl) {
        const int inf = numeric_limits<int>::max() / 2;
        mat c({10, 10}, inf);
        if (fl) {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    c[j][i] = min({c[j][i], a[j][0] + b[0][i], a[j][i] + b[i][i]});
                    c[j][0] = min(c[j][0], a[j][i] + b[i][0]);
                }
            }
        } else {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    c[i][j] = min({c[i][j], a[i][0] + b[0][j], a[i][i] + b[i][j]});
                    c[0][j] = min(c[0][j], a[0][i] + b[i][j]);
                }
            }
        }
        return c;
    };

    MinQueue<mat> mq(mul);
    for (int i = 0; i < n; i++) {
        mq.push(transfer[a[i]]);
        if (i >= k - 1) {
            cout << mq.get()[0][0] << ' ';
        }
        if (i >= k - 1) {
            mq.pop();
        }
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T = 1;
    while (T--) {
        solve();
    }
    return 0;
}