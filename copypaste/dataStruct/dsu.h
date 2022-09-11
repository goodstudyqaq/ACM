#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct DSU {
    std::vector<int> f, g;
    DSU(int n) : f(n), g(n) { std::iota(f.begin(), f.end(), 0); }
    std::array<int, 2> leader(int x) {
        if (f[x] == x) {
            return {x, 0};
        }
        auto [y, z] = leader(f[x]);
        f[x] = y;
        g[x] ^= z;
        return {f[x], g[x]};
    }
    bool merge(int a, int b, int z) {
        auto [x, u] = leader(a);
        auto [y, v] = leader(b);
        if (x == y) {
            return (u ^ v ^ z) == 0;
        }
        f[x] = y;
        g[x] = u ^ v ^ z;
        return true;
    }
};

struct DSU2 {
    std::vector<int> f;
    DSU2(int n) : f(n) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        if (f[x] == x) {
            return x;
        }
        int y = leader(f[x]);
        f[x] = y;
        return f[x];
    }
    bool merge(int a, int b) {
        auto x = leader(a);
        auto y = leader(b);
        if (x == y) {
            return false;
        }
        f[x] = y;
        return true;
    }
};