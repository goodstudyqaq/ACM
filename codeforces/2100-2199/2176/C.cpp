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
    int n;
    cin >> n;
    vector<vector<int>> V(2);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        V[a % 2].push_back(a);
    }

    sort(V[0].begin(), V[0].end());
    sort(V[1].begin(), V[1].end());
    reverse(V[0].begin(), V[0].end());
    reverse(V[1].begin(), V[1].end());

    int even_num = V[0].size();
    int odd_num = V[1].size();
    vector<ll> sum(even_num);

    for (int i = 0; i < even_num; i++) {
        sum[i] = V[0][i];
        if (i) sum[i] += sum[i - 1];
    }

    if (odd_num == 0) {
        for (int i = 0; i < n; i++) {
            cout << 0 << ' ';
        }
        cout << '\n';
        return;
    }

    if (even_num == 0) {
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                cout << V[1][0] << ' ';
            } else {
                cout << 0 << ' ';
            }
        }
        cout << '\n';
        return;
    }

    int mx_odd = V[1][0];

    int N = 1 + even_num;

    ll now = mx_odd;
    cout << now << ' ';
    for (int i = 0; i < even_num; i++) {
        now += V[0][i];
        cout << now << ' ';
    }

    ll val1 = mx_odd + sum[even_num - 1];
    ll val2 = (even_num == 1 ? mx_odd : mx_odd + sum[even_num - 2]);

    for (int i = N; i < n - 1; i++) {
        if ((i - N) % 2) {
            cout << val1 << ' ';
        } else {
            cout << val2 << ' ';
        }
    }
    if (N != n) 
    if ((n - 1 - N) % 2) {
        cout << val1 << ' ';
    } else {
        cout << 0 << ' ';
    }


    cout << '\n';
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