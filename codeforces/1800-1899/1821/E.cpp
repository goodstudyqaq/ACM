#include <bits/stdc++.h>

#include <queue>
#include <vector>

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

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int k;
    string s;
    cin >> k >> s;

    int n = s.size();
    vector<int> match(n);
    vector<int> sum(n);

    vector<int> stk;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            stk.push_back(i);
        } else {
            int idx = stk.back();
            stk.pop_back();
            match[i] = idx;
            match[idx] = i;
        }

        if (s[i] == ')') {
            sum[i]++;
        }
        if (i > 0) sum[i] += sum[i - 1];
    }

    typedef pair<int, int> pii;
    typedef pair<int, pii> piii;
    priority_queue<piii> Q;

    int now = 0;
    while (now < n) {
        int idx = match[now];
        int cnt = sum[idx];
        if (now > 0) cnt -= sum[now - 1];
        Q.push({cnt, {now, idx}});
        now = idx + 1;
    }

    while (k--) {
        auto it = Q.top();
        if (it.first == 1) {
            break;
        }
        Q.pop();
        int l = it.second.first, r = it.second.second;
        int now = l + 1;
        while (now < r) {
            int idx = match[now];
            int cnt = sum[idx];
            if (now > 0) cnt -= sum[now - 1];
            Q.push({cnt, {now, idx}});
            now = idx + 1;
        }
    }

    function<long long(int, int, int)> cal = [&](int l, int r, int d) -> long long {
        int now = l + 1;
        long long ans = 0;
        while (now < r) {
            int idx = match[now];
            ans += cal(now, idx, d + 1) + d;
            now = idx + 1;
        }
        return ans;
    };

    long long ans = 0;
    while (!Q.empty()) {
        auto it = Q.top();
        Q.pop();
        ans += cal(it.second.first, it.second.second, 1);
    }
    cout << ans << endl;
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