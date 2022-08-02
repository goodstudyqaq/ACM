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

const int maxn = 1e6 + 5;
#define lowbit(x) x & -x
long long sum[maxn];

void add(int idx, long long val) {
    while (idx < maxn) {
        sum[idx] += val;
        idx += lowbit(idx);
    }
}

long long query(int idx) {
    long long res = 0;
    while (idx) {
        res += sum[idx];
        idx -= lowbit(idx);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    int n, m;
    cin >> n >> m;
    typedef pair< int, int > pii;

    vector< vector< pii > > a, b;

    const int limit = 1e6;
    a.resize(limit + 1);
    b.resize(limit + 1);
    long long ans = 1;
    for (int i = 1; i <= n; i++) {
        int y, x1, x2;
        cin >> y >> x1 >> x2;
        a[x1].push_back({y, 1});
        a[x2 + 1].push_back({y, -1});
        if (x1 == 0 && x2 == limit) ans++;
    }

    for (int i = 1; i <= m; i++) {
        int x, y1, y2;
        cin >> x >> y1 >> y2;
        b[x].push_back({y1, y2});
        if (y1 == 0 && y2 == limit) ans++;
    }

    for (int i = 0; i <= limit; i++) {
        for (auto it : a[i]) {
            add(it.first, it.second);
        }

        for (auto it : b[i]) {
            long long tmp = query(it.second);
            if (it.first) {
                tmp -= query(it.first - 1);
            }
            ans += tmp;
        }
    }
    cout << ans << endl;
    return 0;
}
