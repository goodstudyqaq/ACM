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
    fast_ios(){
        // cin.tie(nullptr);
        // ios::sync_with_stdio(false);
        // cout << fixed << setprecision(10);
    };
} fast_ios_;

char ask1(int idx) {
    cout << "? 1 " << idx << endl;
    fflush(stdout);
    char it;
    cin >> it;
    return it;
}

map<pii, int> M;

int ask2(int l, int r) {
    if (M.count({l, r})) return M[{l, r}];
    cout << "? 2 " << l << ' ' << r << endl;
    fflush(stdout);
    int num;
    cin >> num;
    return M[{l, r}] = num;
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif
    int n;
    cin >> n;

    string res(n + 1, ' ');

    res[1] = ask1(1);
    int now = 2;

    vector<int> V(26, -1);
    V[res[1] - 'a'] = 1;

    auto get_idx = [&](int idx) -> int {
        vector<int> tmpV;
        for (auto it : V) {
            if (it != -1) {
                tmpV.push_back(it);
            }
        }
        sort(tmpV.begin(), tmpV.end());

        int diff = tmpV.size();
        int tmp = ask2(1, idx);
        if (tmp == diff + 1) {
            return -1;
        }

        int l = 0, r = tmpV.size() - 1;
        int ans = -1;
        while (l <= r) {
            int mid = l + r >> 1;
            int idx2 = tmpV[mid];
            int tmp = ask2(idx2, idx);
            int diff = tmpV.size() - mid;
            if (tmp == diff) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return tmpV[ans];
    };

    while (now <= n) {
        int idx = get_idx(now);
        if (idx == -1) {
            res[now] = ask1(now);
            V[res[now] - 'a'] = now;
        } else {
            res[now] = res[idx];
            int tmp = V[res[now] - 'a'];
            V[res[now] - 'a'] = now;
        }
        now++;
    }
    cout << "! ";
    for (int i = 1; i <= n; i++) {
        cout << res[i];
    }
    cout << endl;
    return 0;
}