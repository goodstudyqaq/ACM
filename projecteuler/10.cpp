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
const int maxn = 2000001;
vector<int> is;
vector<int> prm;
vector<int> min_prm;

void get_prime() {
    is.resize(maxn, 1);
    min_prm.resize(maxn);
    is[0] = is[1] = 0;

    for (int i = 2; i < maxn; i++) {
        if (is[i]) {
            prm.push_back(i);
            min_prm[i] = i;
        }
        int sz = prm.size();
        for (int j = 0; j < sz && i * prm[j] < maxn; j++) {
            is[i * prm[j]] = 0;
            if (i % prm[j] == 0) break;
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    get_prime();
    long long ans = accumulate(prm.begin(), prm.end(), 0LL);
    cout << ans << endl;
}