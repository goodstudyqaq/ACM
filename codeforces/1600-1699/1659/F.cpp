#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;

        vector<vector<int>> V;
        V.resize(n + 1);
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            V[u].push_back(v);
            V[v].push_back(u);
        }
        vector<int> p(n + 1);
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            p[x] = i;
        }
        bool flag = true;
        for (int i = 1; i <= n; i++) {
            if (p[i] != i) {
                flag = false;
                break;
            }
        }
        if (flag) {
            cout << "Alice" << endl;
            continue;
        }

        int rt;
        auto check = [&]() -> bool {
            int cnt = 0;
            for (int i = 1; i <= n; i++) {
                if (V[i].size() > 1) {
                    rt = i;
                    cnt++;
                }
            }
            return cnt == 1;
        };

        if (!check()) {
            cout << "Alice" << endl;
            continue;
        }
        int idx;
        for (int i = 1; i <= n; i++) {
            if (p[i] == rt) {
                idx = i;
                break;
            }
        }
        if (idx != rt && (k == idx || k == rt)) {
            cout << "Bob" << endl;
            continue;
        }

        debug(rt);

        auto check2 = [&]() -> bool {
            vector<bool> vis(n + 1);
            int num0 = 0, num1 = 0;
            for (int i = 1; i <= n; i++) {
                if (p[i] != i && vis[i] == 0) {
                    vis[i] = 1;
                    int cnt = 1;
                    int now = p[i];
                    while (now != i) {
                        vis[now] = 1;
                        cnt++;
                        now = p[now];
                    }
                    if (cnt % 2) {
                        num1++;
                    } else {
                        num0++;
                    }
                }
            }
            debug(num0, num1);
            if (num0 == 0 && num1 == 0) {
                return false;
            }
            if (num0 % 2 == 1) return false;
            return true;
        };

        auto check3 = [&]() -> bool {
            vector<bool> vis(n + 1);
            int num0 = 0, num1 = 0;
            int sz = 0;
            for (int i = 1; i <= n; i++) {
                if (p[i] != i && vis[i] == 0) {
                    vis[i] = 1;
                    int cnt = 1;
                    int now = p[i];
                    while (now != i) {
                        vis[now] = 1;
                        cnt++;
                        now = p[now];
                    }
                    if (cnt % 2) {
                        num1++;
                    } else {
                        num0++;
                    }
                    sz = cnt;
                }
            }
            // false 就是 Alice 赢;
            // true 就是 Bob 赢
            if (num0 % 2 == 0) {
                return false;
            } else {
                if (num0 == 1 && num1 == 0 && sz == 2) {
                    if (p[k] == k) {
                        return false;
                    } else {
                        return true;
                    }
                } else {
                    return true;
                }
            }

            // if (num0 == 2) {
            //     return false;
            // } else if (num0 == 0) {
            //     return false;
            // } else if (num0 == 1 && num1 == 0 && sz == 2) {
            //     if (p[k] == k) {
            //         return false;
            //     } else {
            //         return true;
            //     }
            // }
            // return true;
        };

        if (k == rt) {
            if (check2()) {
                cout << "Bob" << endl;
            } else {
                cout << "Alice" << endl;
            }
        } else {
            if (idx != rt) {
                swap(p[idx], p[rt]);
                if (check2()) {
                    cout << "Bob" << endl;
                } else {
                    cout << "Alice" << endl;
                }
            } else {
                if (check3()) {
                    cout << "Bob" << endl;
                } else {
                    cout << "Alice" << endl;
                }
            }
        }
    }
    return 0;
}