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

    int n;
    cin >> n;
    string need, have;
    cin >> need >> have;

    map<char, vector<int>> M1, M2;
    set<int> position;
    for (int i = 0; i < n; i++) {
        if (need[i] == have[i]) continue;
        M1[need[i]].push_back(i);
        M2[have[i]].push_back(i);
        position.insert(i);
    }

    while (position.size()) {
        auto idx = *position.begin();

        




    }
}