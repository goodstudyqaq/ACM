#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, k;
    cin >> n >> k;
    if (k % 2) {
        for (int i = 0; i < k; i++) {
            cout << n << ' ';
        }
        cout << '\n';
        return;
    }
    vector<int> v;
    int x = n;
    while (x) {
        v.push_back(x % 2);
        x /= 2;
    }
    reverse(v.begin(), v.end());

    int idx = -1;
    for (int i = 1; i < v.size(); i++) {
        if (v[i] == 1) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        cout << 0 << ' ';
        for (int i = 0; i < k - 1; i++) {
            cout << n << ' ';
        }
        cout << '\n';
        return;
    }
    int num = v.size() - idx;
    int val1 = (1 << num) - 1;
    int val2 = n ^ val1;

    int now = 0;
    for (int i = 0; i < idx; i++) {
        now = now * 2 + v[i];
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
    return 0;
}