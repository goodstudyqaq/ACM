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
vector<string> bit{"a", "b", "c", "ab", "bc"};
bool have(string& s1, string s2) {
    int now = 0;
    for (int i = 0; i < s1.size(); i++) {
        if (s1[i] == s2[now]) {
            now++;
            if (now == s2.size()) return true;
        }
    }
    return false;
}

int get_conv(int s1, int s2) {
    vector<string> v1, v2;
    for (int i = 0; i < 5; i++) {
        if ((s1 >> i) & 1) {
            v1.push_back(bit[i]);
        }
        if ((s2 >> i) & 1) {
            v2.push_back(bit[i]);
        }
    }
    v1.push_back("");
    v2.push_back("");
    int status = 0;
    for (int i = 0; i < v1.size(); i++) {
        for (int j = 0; j < v2.size(); j++) {
            string s = v1[i] + v2[j];
            if (have(s, "abc")) {
                return -1;
            }
            for (int k = 0; k < 5; k++) {
                if (have(s, bit[k])) {
                    status |= (1 << k);
                }
            }
        }
    }
    return status;
}

vector<vector<int>> conv;
void init() {
    int LIMIT = 1 << 5;
    conv.resize(LIMIT, vector<int>(LIMIT));
    for (int i = 0; i < LIMIT; i++) {
        for (int j = 0; j < LIMIT; j++) {
            conv[i][j] = get_conv(i, j);
        }
    }
}

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 5;
const int maxm = 32;
const int inf = 1e6;
int mi[maxn << 2][maxm];  // 区间只有这些状态的子序列最少需要删多少字符
string s;

void push_up(int rt) {
    int left_son = rt << 1;
    int right_son = rt << 1 | 1;

    for (int i = 0; i < maxm; i++) {
        mi[rt][i] = inf;
    }

    for (int i = 0; i < maxm; i++) {
        for (int j = 0; j < maxm; j++) {
            if (conv[i][j] != -1) {
                int c = conv[i][j];
                mi[rt][c] = min(mi[rt][c], mi[left_son][i] + mi[right_son][j]);
            }
        }
    }
}

void build(int l, int r, int rt) {
    for (int i = 0; i < maxm; i++) {
        mi[rt][i] = inf;
    }

    if (l == r) {
        int tmp = s[l - 1] - 'a';
        mi[rt][1 << tmp] = 0;
        mi[rt][0] = 1;
        return;
    }
    int m = l + r >> 1;
    build(lson);
    build(rson);
    push_up(rt);
}

void update(int L, int val, int l, int r, int rt) {
    if (l == r) {
        for (int i = 0; i < maxm; i++) {
            mi[rt][i] = inf;
        }
        mi[rt][1 << val] = 0;
        mi[rt][0] = 1;
        return;
    }
    int m = l + r >> 1;
    if (L <= m) {
        update(L, val, lson);
    } else {
        update(L, val, rson);
    }
    push_up(rt);
}

int query() {
    int res = inf;
    for (int i = 0; i < maxm; i++) {
        res = min(res, mi[1][i]);
    }
    return res;
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    int n, q;
    cin >> n >> q;
    cin >> s;
    build(1, n, 1);

    while (q--) {
        int idx;
        char c;
        cin >> idx >> c;
        update(idx, c - 'a', 1, n, 1);
        cout << query() << '\n';
    }
    return 0;
}