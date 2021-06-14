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

const int maxn = 5e5 + 5;
int a[maxn];
int times[maxn];
typedef pair<long long, long long> pll;
pll node[maxn];
pll query[maxn];
int ans[maxn];

long long get_cost(int idx) {
    long long nxtval = node[idx + 1].first;
    long long now = node[idx].first;
    return (nxtval - now) * idx;
}

#define lowbit(x) x & -x
int sum[maxn];
void add(int idx, int val) {
    debug(idx);
    while (idx < maxn) {
        sum[idx] += val;
        idx += lowbit(idx);
    }
}

int query1(int idx) {
    int res = 0;
    while (idx) {
        res += sum[idx];
        idx -= lowbit(idx);
    }
    return res;
}

int n, m, q;
int work(int num) {
    int l = 1, r = m;
    int ans = -1;
    while (l <= r) {
        int mid = l + r >> 1;
        if (query1(mid) >= num) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

int main() {
    freopen("data.in", "r", stdin);
    scanf("%d %d %d", &n, &m, &q);
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        times[a[i]]++;
        mx = max(mx, times[a[i]]);
    }

    long long mx_cha = 0;
    for (int i = 1; i <= m; i++) {
        node[i] = {times[i], i};
    }

    sort(node + 1, node + 1 + m);

    long long k;
    for (int i = 1; i <= q; i++) {
        scanf("%lld", &k);
        query[i] = {k - n, i};
    }

    sort(query + 1, query + 1 + q);

    int now_idx = 1;
    add(node[now_idx].second, 1);
    long long have_cost = 0;
    for (int i = 1; i <= q; i++) {
        long long ask_val = query[i].first - have_cost;
        while (now_idx < m) {
            long long tmp = get_cost(now_idx);
            debug(now_idx, tmp);
            if (tmp < ask_val) {
                have_cost += tmp;
                ask_val -= tmp;
                now_idx++;
                add(node[now_idx].second, 1);
            } else {
                break;
            }
        }

        debug(i, now_idx, ask_val, have_cost);

        int chose_idx = (ask_val - 1) % now_idx + 1;
        debug(chose_idx);
        ans[query[i].second] = work(chose_idx);
    }

    for (int i = 1; i <= q; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}