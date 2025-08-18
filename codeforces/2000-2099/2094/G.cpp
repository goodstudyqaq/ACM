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

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int q;
    cin >> q;
    long long sum = 0;
    int n = 0;
    int s, k;
    cin >> s >> k;
    n++;
    sum += k;
    long long ans = k;
    q--;
    list<int> L;
    L.push_back(k);
    bool reverse = false;
    cout << ans << '\n';

    while (q--) {
        int beg, end;
        beg = *L.begin();
        end = *L.rbegin();
        if (reverse) {
            swap(beg, end);
        }

        cin >> s;
        if (s == 1) {
            ans -= 1LL * n * end;
            ans += sum;
            if (!reverse) {
                L.pop_back();
                L.push_front(end);
            } else {
                L.pop_front();
                L.push_back(end);
            }
        } else if (s == 2) {
            ans = 1LL * (n + 1) * sum - ans;
            reverse ^= 1;
        } else if (s == 3) {
            cin >> k;
            if (reverse) {
                L.push_front(k);
            } else {
                L.push_back(k);
            }
            n++;
            sum += k;
            ans += 1LL * n * k;
        }
        cout << ans << '\n';
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