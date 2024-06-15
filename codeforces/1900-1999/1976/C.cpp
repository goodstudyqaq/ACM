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

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, m;
    cin >> n >> m;
    int N = n + m + 1;
    vector<vector<long long>> c(N + 1, vector<long long>(2));
    for (int i = 1; i <= N; i++) {
        cin >> c[i][0];
    }
    for (int i = 1; i <= N; i++) {
        cin >> c[i][1];
    }

    vector<int> choose(N + 1);
    vector<vector<long long>> sum(N + 1, vector<long long>(2));
    vector<long long> summax(N + 1);
    vector<vector<long long>> sumchoose(N + 1, vector<long long>(2));
    for (int i = 1; i <= N; i++) {
        choose[i] = (c[i][0] < c[i][1]);

        sumchoose[i][0] = sumchoose[i - 1][0];
        sumchoose[i][1] = sumchoose[i - 1][1];
        sumchoose[i][choose[i]]++;

        sum[i][0] = sum[i - 1][0] + c[i][0];
        sum[i][1] = sum[i - 1][1] + c[i][1];
        summax[i] = summax[i - 1] + max(c[i][0], c[i][1]);
    }

    int cnt[2] = {0, 0};
    long long nowval = 0;
    int need[2] = {n, m};

    auto get_idx = [&](int idx) -> pii {
        int l = idx;
        if (cnt[0] == need[0]) {
            return {l - 1, 0};
        } else if (cnt[1] == need[1]) {
            return {l - 1, 1};
        }
        int r = N;
        int ans = -1;

        while (l <= r) {
            int m = l + r >> 1;
            int tmp0 = sumchoose[m][0] - sumchoose[idx - 1][0] + cnt[0];
            int tmp1 = sumchoose[m][1] - sumchoose[idx - 1][1] + cnt[1];
            if (tmp0 <= need[0] && tmp1 <= need[1]) {
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        int tmp0 = sumchoose[ans][0] - sumchoose[idx - 1][0] + cnt[0];
        int tmp1 = sumchoose[ans][1] - sumchoose[idx - 1][1] + cnt[1];
        if (tmp0 == need[0]) {
            return {ans, 0};
        } else {
            return {ans, 1};
        }
    };

    for (int i = 1; i <= N; i++) {
        auto it = get_idx(i + 1);
        // debug(i, it);
        long long tmp = nowval + summax[it.first] - summax[i];
        tmp += sum[N][it.second ^ 1] - sum[it.first][it.second ^ 1];
        cout << tmp << ' ';

        int f = choose[i];
        cnt[f]++;
        if (cnt[f] > need[f]) {
            cnt[f]--;
            cnt[f ^ 1]++;
            nowval += c[i][f ^ 1];
        } else {
            nowval += c[i][f];
        }
    }
    cout << endl;
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