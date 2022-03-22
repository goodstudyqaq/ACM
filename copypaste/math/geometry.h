#include <bits/stdc++.h>
using namespace std;

namespace Geometry {
using ll = long long;
using ld = long double;
struct Point {
    ll x, y;
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

vector<Point> graham(vector<Point> &a) {
    int n = a.size();
    vector<Point> h(n);

    sort(a.begin(), a.end());
    for (int i = 1; i < n; i++) {
        a[i] = a[i] - a[0];
    }
    sort(a.begin(), a.end(), cmp);
    int m = 0;
    for (int i = 0; i < n; i++) {
        while (m > 1 && (a[i] - h[m - 1]) * (a[i] - h[m - 2]) >= 0) m--;
        h[m++] = a[i];
    }
    h.resize(m);
    return h;
}

}  // namespace Geometry
