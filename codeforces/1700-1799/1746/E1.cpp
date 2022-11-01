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

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif

    int n;
    cin >> n;

    vector<int> V;
    for (int i = 1; i <= n; i++) {
        V.push_back(i);
    }

    auto ask = [&](const vector<int> &v) -> bool {
        cout << "? " << v.size();
        for (auto it : v) {
            cout << ' ' << it;
        }
        cout << endl;
        fflush(stdout);
        string res;
        cin >> res;
        return res == "YES";
    };

    auto out = [&](int x) -> bool {
        cout << "! " << x << endl;
        fflush(stdout);
        string res;
        cin >> res;
        return res == ":)";
    };

    while (V.size() > 3) {
        vector<vector<int>> v(4);

        int sz = V.size();
        int num = sz / 4;
        for (int i = 0; i < num * 4; i++) {
            v[i / num].push_back(V[i]);
        }
        for (int i = num * 4; i < sz; i++) {
            v[i % 4].push_back(V[i]);
        }
        debug(v);

        vector<int> tmp;
        for (int i = 0; i < 2; i++) {
            for (auto it : v[i]) {
                tmp.push_back(it);
            }
        }

        int f1 = ask(tmp);
        tmp.clear();
        for (auto it : v[0]) {
            tmp.push_back(it);
        }
        for (auto it : v[2]) {
            tmp.push_back(it);
        }
        int f2 = ask(tmp);

        int flag;
        if (f1 == 0 && f2 == 0) {
            // 去掉 v0
            flag = 0;
        } else if (f1 == 1 && f2 == 1) {
            // 去掉 v3
            flag = 3;
        } else if (f1 == 0 && f2 == 1) {
            flag = 1;
        } else {
            flag = 2;
        }

        V.clear();
        for (int i = 0; i < 4; i++) {
            if (i == flag) continue;
            for (auto it : v[i]) {
                V.push_back(it);
            }
        }
    }

    if (V.size() == 3) {
        int x = V[0], y = V[1];
        int f1 = ask({x});
        int f2 = ask({y});
        if (f1 == 1 && f2 == 1) {
            V.erase(V.begin() + 2);
        } else if (f1 == 0 && f2 == 0) {
            int f3 = ask({y});
            if (f3 == 0) {
                V.erase(V.begin() + 1);
            } else {
                int f4 = ask({x});
                if (f4 == 0) {
                    V.erase(V.begin());
                } else {
                    V.erase(V.begin() + 2);
                }
            }
        } else if (f1 == 0 && f2 == 1) {
            V.erase(V.begin());
        } else {
            V.erase(V.begin() + 1);
        }
    }

    if (V.size() == 1) {
        out(V[0]);
    } else if (V.size() == 2) {
        bool ans = out(V[0]);
        if (ans == 0) {
            out(V[1]);
        }
    }
    return 0;
}