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

const int maxn = 2e5 + 7, maxm = maxn * 240;

int mrk[maxm], ch[maxm][2], mn[maxm], mx[maxm], cnt;
int create(int L, int R) {
    int t = ++cnt;
    mn[t] = L;
    mx[t] = R;
    return t;
}

void mark(int& x, int v) {
    mrk[x] += v;
    mn[x] += v;
    mx[x] += v;
}

void pushdown(int x, int l, int r) {
    if (l == r) return;
    int mid = l + r >> 1;
    if (!ch[x][0]) ch[x][0] = create(l, mid);
    if (!ch[x][1]) ch[x][1] = create(mid + 1, r);
    mark(ch[x][0], mrk[x]);
    mark(ch[x][1], mrk[x]);
    mrk[x] = 0;
}

void upd(int x) {
    mn[x] = min(mn[ch[x][0]], mn[ch[x][1]]);
    mx[x] = max(mx[ch[x][0]], mx[ch[x][1]]);
}

void mark(int x, int l, int r, int L, int R, int v) {
    if (l >= L && r <= R) return mark(x, v);
    pushdown(x, l, r);
    int mid = l + r >> 1;
    if (L <= mid) mark(ch[x][0], l, mid, L, R, v);
    if (R > mid) mark(ch[x][1], mid + 1, r, L, R, v);
    upd(x);
}

int qL(int x, int l, int r, int v) {
    if (l == r) return l;
    pushdown(x, l, r);
    int mid = l + r >> 1;
    if (mn[ch[x][1]] <= v) return qL(ch[x][1], mid + 1, r, v);
    return qL(ch[x][0], l, mid, v);
}

int qR(int x, int l, int r, int v) {
    if (l == r) return l;
    pushdown(x, l, r);
    int mid = l + r >> 1;
    if (mx[ch[x][0]] >= v) return qR(ch[x][0], l, mid, v);
    return qR(ch[x][1], mid + 1, r, v);
}

int qry(int x, int l, int r, int t) {
    // debug(x, l, r, t);
    if (!x) return t;
    if (l == r) return mn[x];
    pushdown(x, l, r);
    int mid = l + r >> 1;
    if (t <= mid) return qry(ch[x][0], l, mid, t);
    return qry(ch[x][1], mid + 1, r, t);
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    create(0, 1e9);
    const int mod = 1e9 + 1;

    int lastans = 0;
    for (int n = 1; n <= N; n++) {
        int T;
        cin >> T;
        // debug(mn[1], mx[1]);
        if (mn[1] < T) {
            mark(1, 0, 1e9, 0, qL(1, 0, 1e9, T - 1), 1);
        }
        if (mx[1] > T) {
            mark(1, 0, 1e9, qR(1, 0, 1e9, T + 1), 1e9, -1);
        }
        int k;
        cin >> k;
        while (k--) {
            int x;
            cin >> x;
            x = (x + lastans) % mod;
            lastans = qry(1, 0, 1e9, x);
            cout << lastans << '\n';
        }
    }
    return 0;
}