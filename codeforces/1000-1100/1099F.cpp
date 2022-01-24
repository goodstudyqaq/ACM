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

#define lowbit(x) x & -x

const int maxn = 1e6 + 5;
void add(vector<long long>& sum, int idx, long long val) {
    while (idx < maxn) {
        sum[idx] += val;
        idx += lowbit(idx);
    }
}
long long query(vector<long long>& sum, int idx) {
    long long res = 0;
    while (idx) {
        res += sum[idx];
        idx -= lowbit(idx);
    }
    return res;
}

vector<long long> sum1, sum2;

vector<int> x, t, p, l;
vector<long long> num, mx_num;
typedef pair<int, int> pii;
vector<vector<pii>> V;

void Add(int have_num, int use_time) {
    add(sum1, use_time, have_num);
    add(sum2, use_time, 1LL * have_num * use_time);
}

long long Query(long long have_time) {
    int l = 1, r = 1e6;
    int ans = -1;
    // 找到第一个所需要的时间大于 have_time 的
    while (l <= r) {
        int mid = l + r >> 1;
        long long tmp = query(sum2, mid);
        if (tmp > have_time) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    if (ans == -1) {
        // 没有时间大于 have_time 取所有
        return query(sum1, 1e6);
    }
    long long tmp = query(sum1, ans - 1);
    long long tmp2 = query(sum2, ans - 1);
    have_time -= tmp2;
    return tmp + have_time / ans;
}

int n;
long long T;
void dfs(int u, long long use) {
    long long left = T - use;
    if (left <= 0) return;
    Add(x[u], t[u]);
    num[u] = Query(left);
    mx_num[u] = num[u];
    int chose_idx = -1;

    for (auto v : V[u]) {
        dfs(v.first, use + 1LL * v.second * 2);
        if (chose_idx == -1 || mx_num[chose_idx] < mx_num[v.first]) {
            chose_idx = v.first;
        }
    }

    for (auto v : V[u]) {
        if (chose_idx == v.first) continue;
        mx_num[u] = max(mx_num[u], mx_num[v.first]);
    }

    Add(-x[u], t[u]);
}
long long ans;

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    sum1.resize(maxn + 5);
    sum2.resize(maxn + 5);

    cin >> n >> T;
    x.resize(n + 1);
    t.resize(n + 1);
    p.resize(n + 1);
    l.resize(n + 1);
    num.resize(n + 1);
    mx_num.resize(n + 1);
    V.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }
    for (int i = 2; i <= n; i++) {
        cin >> p[i] >> l[i];
        V[p[i]].push_back({i, l[i]});
    }
    dfs(1, 0);
    long long ans = num[1];
    for (auto v : V[1]) {
        ans = max(ans, mx_num[v.first]);
    }
    cout << ans << endl;
    return 0;
}