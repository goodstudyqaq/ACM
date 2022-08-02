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
    int N;
    cin >> N;
    vector<int> A(N);
    unordered_map<int, int> M;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        M[A[i]]++;
    }
    const int maxn = 2e5;

    long long ans = 0;
    for (int i = 1; i <= maxn; i++) {
        for (int j = i; j <= maxn; j += i) {
            int tmp = j / i;
            ans += 1LL * M[tmp] * M[i] * M[j];
        }
    }
    cout << ans << endl;
    return 0;
}