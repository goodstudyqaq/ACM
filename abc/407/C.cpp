#include <bits/stdc++.h>

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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    string s;
    cin >> s;

    int n = s.size();
    long long ans = n;
    for (int i = 0; i < n - 1; i++) {
        int c = s[i] - s[i + 1];
        if (c < 0) c += 10;
        ans += c;
    }
    ans += s[n - 1] - '0';
    cout << ans << '\n';
}