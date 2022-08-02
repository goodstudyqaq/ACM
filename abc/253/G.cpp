#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

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
    ll N, L, R;
    cin >> N >> L >> R;
    vector<int> p(N);
    for (int i = 0; i < N; i++) {
        p[i] = i;
    }

    ll now = 0;
    int now_idx = 0;

    while (now + N - now_idx - 1 < L) {
        now += N - now_idx - 1;
        now_idx++;
    }
    ll tmp = L - now;
    int Left = now_idx + tmp;

    ll now_step = L;
    debug(now_idx, Left);
    while (now_step <= R) {
        swap(p[now_idx], p[Left]);
        now_step++;
        Left++;
        if (Left == N) break;
    }
    debug(p);

    auto out = [&]() {
        for (int i = 0; i < N; i++) {
            cout << p[i] + 1 << ' ';
        }
        cout << endl;
    };

    if (now_step == R) {
        out();
        return 0;
    }

    now += N - now_idx - 1;
    now_idx++;
    int begin = now_idx;
    int offset = 0;
    debug(now, now_idx);

    while (now + N - now_idx - 1 < R) {
        offset++;
        now += N - now_idx - 1;
        now_idx++;
    }

    vector<int> new_p(N);

    for (int i = 0; i < begin; i++) {
        new_p[i] = p[i];
    }
    debug(begin, offset);
    vector<int> v;
    for (int i = begin; i < N; i++) {
        v.push_back(p[i]);
    }

    int sz = v.size();
    for (int i = begin; i < N; i++) {
        if (i < begin + offset) {
            new_p[i] = v[sz - (i - begin) - 1];
        } else {
            new_p[i] = v[i - begin - offset];
        }
    }

    // for (int i = begin; i < N; i++) {
    //     int v_idx = i - begin;
    //     new_p[i] = v[(v_idx + offset) % sz];
    // }
    debug(new_p);

    Left = now_idx + 1;
    debug(now_idx);
    debug(now);
    while (now < R) {
        swap(new_p[now_idx], new_p[Left]);
        now++;
        Left++;
        debug(new_p);
    }
    p = new_p;
    out();
}