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
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
long long rnd(long long x) { return rng() % x; }
int lg2(long long x) { return sizeof(long long) * 8 - 1 - __builtin_clzll(x); }

int ask(string s) {
    cout << s << endl;
    fflush(stdout);
    int res;
    cin >> res;
    return res;
}

void solve() {
    int n = 8;
    int LIMIT = 1 << n;
    set<int> S;
    vector<int> score(LIMIT);
    for (int i = 0; i < LIMIT; i++) {
        S.insert(i);
        score[i] = 1;
    }

    auto to_bit_string = [&](int s) {
        string res = "";
        for (int i = n - 1; i >= 0; i--) {
            if ((s >> i) & 1) {
                res += "1";
            } else {
                res += "0";
            }
        }
        debug(s, res);
        return res;
    };

    auto update = [&](int s, int one_num) {
        set<int> nxt;
        for (int i = 0; i < LIMIT; i++) {
            score[i] = 0;
        }
        vector<int> v;
        for (int i = 0; i < n; i++) {
            int tmp1 = (s >> i);
            int tmp2 = s & ((1 << i) - 1);
            int tmp = (tmp2 << (n - i)) + tmp1;
            v.push_back(tmp);
        }

        for (auto it : S) {
            for (auto it2 : v) {
                int tmp = it ^ it2;
                int one_cnt = __builtin_popcount(tmp);
                if (one_cnt == one_num) {
                    score[tmp]++;
                    nxt.insert(tmp);
                }
            }
        }
        S = nxt;
    };

    while (true) {
        debug(S);
        vector<int> v;
        int mx = -1;
        for (auto s : S) {
            if (score[s] > mx) {
                mx = score[s];
                v.clear();
                v.push_back(s);
            } else if (score[s] == mx) {
                v.push_back(s);
            }
        }
        int sz = v.size();
        int choose = rnd(sz);
        int s = v[choose];
        string q = to_bit_string(s);
        int num = ask(q);
        if (num == 0) break;
        update(s, num);
    }
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