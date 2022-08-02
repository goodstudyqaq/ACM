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

vector<vector<int> > G;
const int inf = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    int n, m;
    cin >> n >> m;
    G.resize(n * 2, vector<int>(n * 2, inf));
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        G[a][b] = min(G[a][b], c);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (G[i][j] != inf) {
                int ct = G[i][j];
                for (int k = 0; k < n; k++) {
                    G[i][k] = min(G[i][k], (k - j + n) % n + ct);
                }
            }
        }
    }
    // 0 到 n - 1 正常点
    // n 到 n + n - 1 虚点
    for (int i = n; i < n + n; i++) {
        for (int j = 0; j < n; j++) {
            G[i][j] = G[i - n][j];
        }
    }
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         debug(i, j, G[i][j]);
    //     }
    // }
    for (int t = 1; t <= 6; t++)
        for (int k = 0; k < n; k++) {
            for (int i = n; i < n + n; i++) {
                int ct = G[i][k];
                if (ct == inf) continue;
                for (int j = 0; j < n; j++) {
                    // 到 k 点时时间已经为 ct, 所以 G[k][j] 表示的花费时 k 到 (j + ct) % n 的花费
                    int ct2 = G[k][j];
                    int idx = (j + ct) % n;
                    G[i][idx] = min(G[i][idx], ct + ct2);
                }
            }
        }
    for (int i = n; i < n + n; i++) {
        G[i][i - n] = 0;
        for (int j = 0; j < n; j++) {
            cout << G[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}