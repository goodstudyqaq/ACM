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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    unordered_map<string, int> M;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (M[s] == 0) {
            cout << s << endl;
        } else {
            int num = M[s];
            cout << s << '(' << num << ')' << endl;
        }
        M[s]++;
    }
    return 0;
}