#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// struct fast_ios {
//     fast_ios() {
//         cin.tie(nullptr);
//         ios::sync_with_stdio(false);
//         cout << fixed << setprecision(10);
//     };
// } fast_ios_;

void query1(int x) {
    cout << "+ " << x << endl;
    fflush(stdout);
    int res;
    cin >> res;
}

int query2(int i, int j) {
    cout << "? " << i << " " << j << endl;
    fflush(stdout);
    int res;
    cin >> res;
    return res;
}

void solve() {
    int n;
    cin >> n;

    if (n == 2) {
        cout << "! 1 2 2 1" << endl;
        return;
    }
    query1(n + 1);
    query1(n + 2);

    vector<int> response(n + 1);
    for (int i = 2; i <= n; i++) {
        response[i] = query2(1, i);
    }
    int idx = 1;
    for (int i = 2; i <= n; i++) {
        if (response[i] > response[idx]) {
            idx = i;
        }
    }
    if (idx != 1) {
        for (int i = 1; i <= n; i++) {
            if (i == idx) continue;
            response[i] = query2(idx, i);
        }
    }

    vector<int> ans1(n + 1), ans2(n + 1);
    vector<int> seq(n + 1);
    // ans1[idx] = 1, ans2[idx] =

    int now = 1;
    for (int i = 1; i <= n; i += 2) {
        seq[i] = now++;
    }
    now = n;
    for (int i = 2; i <= n; i += 2) {
        seq[i] = now--;
    }
    ans1[idx] = 1, ans2[idx] = seq[n];

    for (int i = 1; i <= n; i++) {
        if (i == idx) continue;
        ans1[i] = seq[response[i] + 1];
        ans2[i] = seq[n - response[i]];
    }
    cout << "!";
    for (int i = 1; i <= n; i++) {
        cout << " " << ans1[i];
    }
    for (int i = 1; i <= n; i++) {
        cout << " " << ans2[i];
    }
    cout << endl;
    fflush(stdout);
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}