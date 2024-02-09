#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

// #define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct fast_ios {
    fast_ios(){
        // cin.tie(nullptr);
        // ios::sync_with_stdio(false);
        // cout << fixed << setprecision(10);
    };
} fast_ios_;

template <class T>
auto vect(const T& v, int n) { return vector<T>(n, v); }
template <class T, class... D>
auto vect(const T& v, int n, D... m) {
    return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}

template <typename T>
static constexpr T inf = numeric_limits<T>::max() / 2;
mt19937_64 mrand(random_device{}());
long long rnd(long long x) { return mrand() % x; }
int lg2(long long x) { return sizeof(long long) * 8 - 1 - __builtin_clzll(x); }

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef pair<int, int> pii;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

void solve() {
    int n;
    cin >> n;

    vector<int> a;
    for (int i = 1; i <= n; i++) a.push_back(i);
    vector<int> res(n + 1);

    auto ask = [&](int idx) -> char {
        cout << "? " << idx << endl;
        fflush(stdout);
        char it;
        cin >> it;
        return it;
    };

    function<void(vector<int>&, int, int)> work = [&](vector<int>& a, int l, int r) {
        int sz = a.size();
        if (sz == 0) return;
        int idx = rnd(sz);
        while (true) {
            char res = ask(a[idx]);
            if (res == '=') {
                break;
            }
        }
        vector<int> go[2];
        for (int i = 0; i < sz; i++) {
            if (i == idx) continue;
            char res = ask(a[i]);
            go[res == '>'].push_back(a[i]);
            ask(a[idx]);
        }
        res[a[idx]] = l + go[0].size();
        work(go[0], l, res[a[idx]] - 1);
        work(go[1], res[a[idx]] + 1, r);
    };

    work(a, 1, n);

    auto out = [&]() {
        cout << "!";
        for (int i = 1; i <= n; i++) {
            cout << " " << res[i];
        }
        cout << endl;
        fflush(stdout);
    };
    out();
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}