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

vector<int> X;

struct Node {
    int x, d, t, p;
    int idx;
    bool operator<(const Node& b) const {
        return x < b.x;
    }
};

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

const int maxn = 3e5 + 5;
long long mi1[maxn << 2];
long long mi2[maxn << 2];
int mi1_idx[maxn << 2];
int mi2_idx[maxn << 2];

void build(int l, int r, int rt) {
    mi1[rt] = 1e15;
    mi2[rt] = 1e15;
    if (l == r) {
        return;
    }
    int m = l + r >> 1;
    build(lson);
    build(rson);
}

int update(int L, long long val, int idx, long long* mi, int* chose, int l, int r, int rt) {
    if (l == r) {
        if (mi[rt] > val) {
            mi[rt] = val;
            chose[rt] = idx;
            return -1;
        } else {
            return chose[rt];
        }
    }
    int m = l + r >> 1;
    int res;
    if (L <= m) {
        res = update(L, val, idx, mi, chose, lson);
    } else {
        res = update(L, val, idx, mi, chose, rson);
    }
    if (mi[rt << 1] < mi[rt << 1 | 1]) {
        mi[rt] = mi[rt << 1];
        chose[rt] = chose[rt << 1];
    } else {
        mi[rt] = mi[rt << 1 | 1];
        chose[rt] = chose[rt << 1 | 1];
    }
    return res;
}

typedef pair<long long, int> pii;
pii query(int L, int R, long long* mi, int* chose, int l, int r, int rt) {
    if (L <= l && r <= R) {
        return {mi[rt], chose[rt]};
    }
    int m = l + r >> 1;
    pii res = {1e15, 0};
    if (L <= m) {
        auto it = query(L, R, mi, chose, lson);
        if (res.first > it.first) {
            res.first = it.first;
            res.second = it.second;
        }
    }
    if (R > m) {
        auto it = query(L, R, mi, chose, rson);
        if (res.first > it.first) {
            res.first = it.first;
            res.second = it.second;
        }
    }
    return res;
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, L;
    cin >> n >> L;
    vector<Node> V;
    int v_cnt = 0;
    int x_cnt = 0;
    V.resize(n + 1);
    X.resize(3 * n + 2);

    for (int i = 1; i <= n; i++) {
        int x, d, t, p;
        cin >> x >> d >> t >> p;
        if (d <= t) {
            continue;
        }
        if (x - p < 0) {
            continue;
        }
        V[v_cnt++] = (Node){x, d, t, p, i};
        X[x_cnt++] = x;
        X[x_cnt++] = x - p;
        X[x_cnt++] = x + d;
    }
    V[v_cnt++] = (Node){L, 0, 0, 0, -1};

    X[x_cnt++] = 0;
    X[x_cnt++] = L;

    sort(X.begin(), X.begin() + x_cnt);
    x_cnt = unique(X.begin(), X.begin() + x_cnt) - X.begin();
    build(1, x_cnt, 1);
    update(1, 0, -1, mi1, mi1_idx, 1, x_cnt, 1);
    update(1, 0, -1, mi2, mi2_idx, 1, x_cnt, 1);

    sort(V.begin(), V.begin() + v_cnt);

    // 从哪个点来的
    // 用了哪个
    vector<int> lxt_idx(x_cnt + 1);
    vector<int> use(x_cnt + 1, -1);

    for (int i = 0; i < v_cnt; i++) {
        int x = V[i].x - V[i].p;
        int x_idx = lower_bound(X.begin(), X.begin() + x_cnt, x) - X.begin() + 1;
        auto it1 = query(1, x_idx, mi1, mi1_idx, 1, x_cnt, 1);
        long long val = it1.first + V[i].x + V[i].t;  // 从左边到 x + d 位置的速度

        auto it2 = query(x_idx, x_cnt, mi2, mi2_idx, 1, x_cnt, 1);
        long long val2;
        if (it2.first != 1e15) {
            val2 = it2.first - x + V[i].p + V[i].t;  // 从右边到 x + d 位置的速度
        } else {
            val2 = 1e15;
        }
        long long mi_val = min(val, val2);
        int flag;
        if (mi_val == val) {
            flag = 1;
        } else {
            flag = 2;
        }

        int x2 = V[i].x + V[i].d;
        int x2_idx = lower_bound(X.begin(), X.begin() + x_cnt, x2) - X.begin() + 1;

        val = mi_val - x2;
        val2 = mi_val + x2;

        int f1 = update(x2_idx, val, x2_idx, mi1, mi1_idx, 1, x_cnt, 1);
        int f2 = update(x2_idx, val2, x2_idx, mi2, mi2_idx, 1, x_cnt, 1);
        // debug(it1.first, it1.second, it2.first, it2.second);
        if (f1 == -1 && f2 == -1) {
            if (flag == 1) {
                lxt_idx[x2_idx] = it1.second;
            } else {
                lxt_idx[x2_idx] = it2.second;
            }
            use[x2_idx] = i;
        }
    }
    int now = L;
    int now_idx = lower_bound(X.begin(), X.begin() + x_cnt, now) - X.begin() + 1;
    auto it = query(1, now_idx, mi1, mi1_idx, 1, x_cnt, 1);
    debug(it.first, it.second);
    cout << it.first + now << endl;
    vector<int> ans;
    debug(now_idx, use[now_idx], lxt_idx[now_idx]);
    while (true) {
        // debug(now_idx);
        if (now_idx == -1) break;
        int the_use = use[now_idx];
        if (the_use == -1) break;
        if (V[the_use].idx != -1) {
            ans.push_back(V[the_use].idx);
        }
        now_idx = lxt_idx[now_idx];
    }
    cout << ans.size() << endl;
    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i] << ' ';
    }
    cout << endl;

    return 0;
}