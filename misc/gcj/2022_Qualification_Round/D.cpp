#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios(){
        // cin.tie(nullptr);
        // ios::sync_with_stdio(false);
        // cout << fixed << setprecision(10);
    };
} fast_ios_;

template <class T>
auto vect(const T& v, int n) { return vector<T>(n, v); }
template <class T, class... D>
auto vect(const T& v, int n, D... m) {
    return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}

template <typename T>
static constexpr T inf = numeric_limits<T>::max() / 2;
mt19937_64 mrand(random_device{}());
long long rnd(long long x) { return mrand() % x; }
int lg2(long long x) { return sizeof(long long) * 8 - 1 - __builtin_clzll(x); }
typedef pair<int, int> pii;
void solve() {
    int N, K;
    cin >> N >> K;
    int begin, degree;
    cin >> begin >> degree;
    vector<int> d(N + 1, 0);
    d[begin] = degree;

    auto ask = [&](char it, int num = 0) -> pii {
        cout << it;
        if (num != 0) {
            cout << ' ' << num;
        }
        cout << endl;
        fflush(stdout);
        int idx, degree;
        cin >> idx >> degree;
        return {idx, degree};
    };

    auto out = [&](long long ans) {
        cout << "E " << ans << endl;
        fflush(stdout);
    };

    if (N <= K - 1) {
        long long ans = 0;
        for (int i = 1; i <= N; i++) {
            if (d[i] != 0) {
                pii res = ask('T', i);
                d[i] = res.second;
            }
            ans += d[i];
        }
        out(ans / 2);
        return;
    }

    vector<int> d2(N + 1, 0);
    while (K) {
        int idx = rnd(N) + 1;
        pii res = ask('T', idx);
        d[idx] = res.second;
        K--;
        if (K == 0) break;

        pii res2 = ask('W');
        d2[res2.first] = res2.second;
        K--;
    }

    int no = 0;
    long long sum = 0;
    long long ans = 0;
    int cnt = 0;
    for (int i = 1; i <= N; i++) {
        if (d[i] == 0 && d2[i] == 0) {
            no++;
        } else if (d2[i]) {
            ans += d2[i];
        } else {
            cnt++;
            sum += d[i];
            ans += d[i];
        }
    }

    long long cal = sum / cnt * no;
    ans += cal;
    out(ans / 2);
}

int main() {
#ifdef LOCAL
    // freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}