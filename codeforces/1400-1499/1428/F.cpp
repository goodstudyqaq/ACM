#include <bits/stdc++.h>

using namespace std;

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string& s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string)s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template <size_t N>
string to_string(bitset<N> v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto& x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_out() {
    cerr << endl;
}

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

const int maxn = 5e5 + 5;
int mi[maxn << 2], mx[maxn << 2];

void build(int l, int r, int rt) {
    mi[rt] = 1e9;
    mx[rt] = -1e9;
    if (l == r) return;
    int m = l + r >> 1;
    build(lson);
    build(rson);
}

void update(int L, int val, int l, int r, int rt) {
    if (l == r) {
        mi[rt] = min(mi[rt], val);
        mx[rt] = max(mx[rt], val);
        return;
    }
    int m = l + r >> 1;
    if (L <= m) {
        update(L, val, lson);
    } else {
        update(L, val, rson);
    }
    mi[rt] = min(mi[rt << 1], mi[rt << 1 | 1]);
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
}
typedef pair<int, int> pii;

pii query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) {
        return {mi[rt], mx[rt]};
    }
    int res_mi = 1e9, res_mx = -1e9;
    int m = l + r >> 1;
    if (L <= m) {
        auto it = query(L, R, lson);
        res_mi = min(res_mi, it.first);
        res_mx = max(res_mx, it.second);
    }
    if (R > m) {
        auto it = query(L, R, rson);
        res_mi = min(res_mi, it.first);
        res_mx = max(res_mx, it.second);
    }
    return {res_mi, res_mx};
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    string s;
    cin >> s;
    long long ans = 0, ans2 = 0;

    int now = 0;
    while (now < n) {
        int go = now;
        while (go < n && s[go] == '0') go++;

        int go2 = go;
        while (go2 < n && s[go2] == '1') go2++;

        // [go, go2) 都是 1
        int one_len = go2 - go;
        if (one_len > 2) {
            for (int i = one_len - 2; i >= 1; i--) {
                ans = ans + 1LL * i * (one_len - 1 - i);
            }
        }
        now = go2;
    }

    now = 0;
    build(1, n, 1);
    vector<int> val(n);
    while (now < n) {
        int go = now;
        while (go < n && s[go] == '0') go++;
        int go2 = go;
        while (go2 < n && s[go2] == '1') go2++;
        debug(go, go2);
        int one_len = go2 - go;
        if (one_len) {
            for (int i = 1; i <= one_len; i++) {
                auto it = query(i, n, 1, n, 1);
                int loc = it.second;  // 等于它的最大的位置
                if (loc != -1e9)
                    loc = loc - i + 1 + 1;
                else
                    loc = 0;
                if (i == one_len) {
                    val[go] = go - loc + 1;
                } else {
                    ans += 1LL * (go - loc + 1) * i;
                }
            }
            update(one_len, go2 - 1, 1, n, 1);
        }
        now = go2;
    }
    debug(ans);

    build(1, n, 1);
    now = n - 1;
    while (now >= 0) {
        debug(now);
        int go = now;
        while (go >= 0 && s[go] == '0') go--;
        int go2 = go;
        while (go2 >= 0 && s[go2] == '1') go2--;
        // (go2, go]
        int one_len = go - go2;
        if (one_len) {
            for (int i = 1; i <= one_len; i++) {
                auto it = query(i + 1, n, 1, n, 1);
                int loc = it.first;
                if (loc != 1e9) {
                    loc = loc + i - 1;
                } else {
                    loc = n - 1;
                }
                if (i == one_len) {
                    ans2 += 1LL * val[go2 + 1] * (loc - go + 1) * one_len;
                } else {
                    ans += 1LL * (loc - go + 1) * i;
                }
            }
            update(one_len, go2 + 1, 1, n, 1);
        }
        now = go2;
    }
    debug(ans, ans2);
    cout << ans + ans2 << endl;
    return 0;
}