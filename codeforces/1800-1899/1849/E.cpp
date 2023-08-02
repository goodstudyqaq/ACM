#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

typedef pair<int, int> pii;

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
    int n;
    cin >> n;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    vector<int> stk1, stk2;

    vector<int> left_mi(n + 1, 0), left_mx(n + 1, 0);
    vector<int> right_mi(n + 1, n + 1), right_mx(n + 1, n + 1);

    for (int i = 1; i <= n; i++) {
        int val = p[i];
        while (stk1.size() && p[stk1.back()] > val) {
            stk1.pop_back();
        }

        if (stk1.size()) {
            left_mi[i] = stk1.back();
        }
        stk1.push_back(i);

        while (stk2.size() && p[stk2.back()] < val) {
            stk2.pop_back();
        }
        if (stk2.size()) {
            left_mx[i] = stk2.back();
        }
        stk2.push_back(i);
    }

    stk1.clear();
    stk2.clear();

    for (int i = n; i >= 1; i--) {
        int val = p[i];
        while (stk1.size() && p[stk1.back()] > val) {
            stk1.pop_back();
        }
        if (stk1.size()) {
            right_mi[i] = stk1.back();
        }
        stk1.push_back(i);

        while (stk2.size() && p[stk2.back()] < val) {
            stk2.pop_back();
        }
        if (stk2.size()) {
            right_mx[i] = stk2.back();
        }
        stk2.push_back(i);
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        // i is the max element's localtion
        int val = p[i];

        int l = left_mx[i], r = right_mx[i];
        // (l, r)

        if (r == i + 1) {
            ans += i - l;
            continue;
        }

        int j = i;

        while (j > l) {
            int r2 = right_mi[j];
            r2 = min(r, r2);
            int go = max(left_mi[j], l);
            long long tmp = 1LL * (r2 - i) * (j - go);
            ans += tmp;
            j = go;
        }
    }
    cout << ans - n << endl;
    return 0;
}