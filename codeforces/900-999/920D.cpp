#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;

template < typename A, typename B >
string to_string(pair< A, B > p);

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p);

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p);

string to_string(const string& s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string)s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

string to_string(vector< bool > v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast< int >(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template < size_t N >
string to_string(bitset< N > v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast< char >('0' + v[i]);
    }
    return res;
}

template < typename A >
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

template < typename A, typename B >
string to_string(pair< A, B > p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p) {
    return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ")";
}

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p) {
    return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ", " + to_string(get< 3 >(p)) + ")";
}

void debug_out() {
    cerr << endl;
}

template < typename Head, typename... Tail >
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    int n, k, v;
    cin >> n >> k >> v;
    vector< int > a;
    a.resize(n + 1);
    int all = 0;
    bool f = false;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        all += a[i];
        if (a[i] == v) f = true;
    }
    if (f) {
        cout << "YES" << endl;
        return 0;
    }

    if (v == 0) {
        cout << "YES" << endl;
        cout << (a[1] - 1) / k + 1 << ' ' << 1 << ' ' << 2 << endl;
        return 0;
    }

    if (all < v) {
        cout << "NO" << endl;
        return 0;
    }

    if (v % k == 0) {
        cout << "YES" << endl;
        for (int i = 2; i <= n; i++) {
            cout << (a[i] - 1) / k + 1 << ' ' << i << ' ' << 1 << '\n';
        }
        cout << v / k << ' ' << 1 << ' ' << 2 << '\n';
        return 0;
    }

    vector< vector< int > > dp, path;
    dp.resize(n + 1, vector< int >(k, 0));
    path.resize(n + 1, vector< int >(k, -1));
    // dp[i][j] 考虑前 i 个余数为 j 是否能搞定
    int goal = v % k;
    int need_k = v / k;
    for (int i = 1; i <= n; i++) {
        if (dp[i - 1][a[i] % k] == 0) {
            dp[i][a[i] % k] = 1;
            path[i][a[i] % k] = i;
        }
        for (int j = 0; j < k; j++) {
            if (dp[i - 1][j]) {
                dp[i][j] = dp[i - 1][j];
                path[i][j] = path[i - 1][j];
            }
        }
        for (int j = 0; j < k; j++) {
            if (dp[i - 1][j] && dp[i][(j + a[i]) % k] == 0) {
                dp[i][(j + a[i]) % k] = 1;
                path[i][(j + a[i]) % k] = i;
            }
        }
    }
    debug(dp);
    debug(path);
    if (dp[n][goal] == 0) {
        cout << "NO" << endl;
        return 0;
    }

    // 找到满足 goal 的元素
    vector< int > V;
    vector< bool > vis(n + 1, 0);
    int now = goal;
    int now_d = n;
    while (path[now_d][now] != -1) {
        debug(now_d, now);
        int the_path = path[now_d][now];
        vis[the_path] = 1;
        V.push_back(the_path);
        now_d = the_path - 1;
        now = ((now - a[the_path] % k) % k + k) % k;
    }
    debug(V);

    // 把所有的都倒到 V[0]
    int have = a[V[0]];
    for (int i = 1; i < V.size(); i++) {
        int idx = V[i];
        have += a[idx];
    }
    if (have >= v) {
        cout << "YES" << endl;
        for (int i = 1; i < V.size(); i++) {
            int idx = V[i];
            int times = (a[idx] - 1) / k + 1;
            cout << times << ' ' << idx << ' ' << V[0] << '\n';
        }
        int need_delete = (have - v) / k;
        if (need_delete) {
            int other = V[0] + 1;
            if (other > n) other = 1;
            cout << need_delete << ' ' << V[0] << ' ' << other << '\n';
        }
        return 0;
    }
    int need = v - have;
    // 还需要 need

    int times = 0;
    all = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        all += a[i];
    }
    if (need <= all) {
        // 还可以
        cout << "YES" << endl;
        for (int i = 1; i < V.size(); i++) {
            int idx = V[i];
            int times = (a[idx] - 1) / k + 1;
            cout << times << ' ' << idx << ' ' << V[0] << '\n';
        }

        // 第一个没有选中的点
        int chose = -1;
        for (int i = 1; i <= n; i++) {
            if (vis[i] == 0) {
                if (chose == -1) {
                    chose = i;
                } else {
                    int times = (a[i] - 1) / k + 1;
                    cout << times << ' ' << i << ' ' << chose << '\n';
                }
            }
        }
        int need_times = need / k;
        cout << need_times << ' ' << chose << ' ' << V[0] << '\n';
        return 0;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
