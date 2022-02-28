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

string to_string(const string &s) {
    return '"' + s + '"';
}

string to_string(const char *s) {
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
    for (const auto &x : v) {
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
typedef long long ll;
typedef long double ld;

struct Point {
    long long x, y;
    Point() : x(), y() {}
    Point(ll _x, ll _y) : x(_x), y(_y) {}

    Point operator+(const Point &a) const {
        return Point(x + a.x, y + a.y);
    }
    Point operator-(const Point &a) const {
        return Point(x - a.x, y - a.y);
    }
    ll operator*(const Point &a) const {
        return x * a.y - y * a.x;
    }

    double len() const {
        return sqrtl((ld)x * x + (ld)y * y);
    }

    bool operator<(const Point &a) const {
        if (x != a.x) return x < a.x;
        return y < a.y;
    }
};

bool cmp(const Point &v, const Point &u) {
    ll x = v * u;
    if (x != 0) return x > 0;
    return v.len() < u.len();
}

const int maxn = 100100;
int n;
Point a[maxn], h[maxn];
int m;

void graham() {
    sort(a, a + n, cmp);
    for (int i = 0; i < n; i++) {
        while (m > 1 && (a[i] - h[m - 1]) * (a[i] - h[m - 2]) >= 0) m--;
        h[m++] = a[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    cin >> n;
    long long x, y;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        a[i] = Point(x, y - x * x);
    }
    sort(a, a + n);
    for (int i = 1; i < n; i++) {
        a[i] = a[i] - a[0];
    }
    a[0] = Point(0, 0);
    graham();
    cout << m - 1 << endl;
    return 0;
}
