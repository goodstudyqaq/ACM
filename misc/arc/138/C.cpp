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
    typedef pair<int, int> pii;
    vector<pii> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i].first;
        A[i].second = i;
    }
    sort(A.begin(), A.end());

    long long ans = 0;
    for (int i = N / 2; i < N; i++) {
        ans += A[i].first;
    }
    vector<int> sum(N, -1);
    for (int i = 0; i < N / 2; i++) {
        sum[A[i].second] = 1;
    }
    for (int i = 1; i < N; i++) {
        sum[i] += sum[i - 1];
    }

    int idx = min_element(sum.begin(), sum.end()) - sum.begin();

    cout << (idx + 1) % N << ' ' << ans << endl;
    return 0;
}