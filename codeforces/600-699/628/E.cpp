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

const int maxn = 3005;
char mp[maxn][maxn];

int n, m;

int left_[maxn][maxn], right_[maxn][maxn], anti_diagonal[maxn][maxn];

void init() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j] == 'z') {
                left_[i][j] = left_[i][j - 1] + 1;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) {
            if (mp[i][j] == 'z') {
                right_[i][j] = right_[i][j + 1] + 1;
            }
        }
    }

    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j] == 'z') {
                anti_diagonal[i][j] = anti_diagonal[i + 1][j - 1] + 1;
            }
        }
    }
}

const int maxm = 3005;
int sum[maxm * 16];  // todo:
int son[maxm * 16][2];
int ncnt;
int root[maxm];

void push_up(int rt) {
    sum[rt] = sum[son[rt][0]] + sum[son[rt][1]];
}

void build(int l, int r, int now) {
    if (l == r) {
        sum[now] = 0;
        return;
    }
    int m = l + r >> 1;
    son[now][0] = ++ncnt;
    son[now][1] = ++ncnt;
    build(l, m, son[now][0]);
    build(m + 1, r, son[now][1]);
    push_up(now);
}

void update(int L, int val, int l, int r, int now_rt, int pre_rt) {
    if (l == r) {
        sum[now_rt] = val;
        return;
    }
    int m = l + r >> 1;
    if (L <= m) {
        son[now_rt][1] = son[pre_rt][1];
        son[now_rt][0] = ++ncnt;
        update(L, val, l, m, son[now_rt][0], son[pre_rt][0]);
    } else {
        son[now_rt][0] = son[pre_rt][0];
        son[now_rt][1] = ++ncnt;
        update(L, val, m + 1, r, son[now_rt][1], son[pre_rt][1]);
    }
    push_up(now_rt);
}

int query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) {
        return sum[rt];
    }
    int m = l + r >> 1;
    int res = 0;
    if (L <= m) {
        res += query(L, R, l, m, son[rt][0]);
    }
    if (R > m) {
        res += query(L, R, m + 1, r, son[rt][1]);
    }
    return res;
}

long long ans;

typedef pair<int, int> pii;
void work() {
    for (int i = 2; i <= n + m; i++) {
        int mix = max(1, i - m);
        int mxx = min(n, i - 1);
        vector<pii> V;
        for (int x = mix; x <= mxx; x++) {
            int y = i - x;
            if (mp[x][y] != 'z') {
                continue;
            }
            int val = right_[x][y] + y - 1;
            V.push_back({val, x});
        }
        if (V.size() == 0) {
            continue;
        }
        sort(V.begin(), V.end());

        ncnt = 0;
        root[0] = ++ncnt;
        build(1, n, root[0]);
        int lxt_rt = root[0];
        for (auto it : V) {
            root[it.first] = ++ncnt;
            update(it.second, 1, 1, n, root[it.first], lxt_rt);
            lxt_rt = root[it.first];
        }
        // 询问
        int mx_rt = root[V.back().first];
        for (int x = mix; x <= mxx; x++) {
            int y = i - x;
            if (mp[x][y] != 'z') continue;
            int left_val = left_[x][y];
            int anti_val = anti_diagonal[x][y];
            int the_mi = min(left_val, anti_val);
            int L = x;
            int R = x + the_mi - 1;
            int all_val = query(L, R, 1, n, mx_rt);

            int idx = lower_bound(V.begin(), V.end(), make_pair(y, 0)) - V.begin();
            if (idx == 0) {
                ans += all_val;
            } else {
                idx--;
                int rt = root[V[idx].first];
                int mi_val = query(L, R, 1, n, rt);
                ans += all_val - mi_val;
            }
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif

    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", mp[i] + 1);
    }
    init();
    work();
    printf("%lld\n", ans);
    return 0;
}