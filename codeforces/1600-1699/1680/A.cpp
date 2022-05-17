#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

typedef pair<int, int> pii;
void solve() {
    pii a, b;
    cin >> a.first >> a.second >> b.first >> b.second;
    if (a > b) {
        swap(a, b);
    }
    if (a.second < b.first) {
        int num = a.first + b.first;
        cout << num << endl;
    } else {
        cout << b.first << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}