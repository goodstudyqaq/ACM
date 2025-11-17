#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;
template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;

    Fenwick(int n_ = 0) {
        init(n_);
    }

    void init(int n_) {
        n = n_;
        a.assign(n, T{});
    }

    void add(int x, const T& v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }

    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }

    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }

    int select(const T& k) {
        int x = 0;
        T cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

struct Max {
    int x = 0;
};

Max operator+(const Max& a, const Max& b) {
    return {std::max(a.x, b.x)};
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> vec(n);
    for (int i = 1; i <= n; i++) {
        int x;
        std::cin >> x;
        x--;
        vec[x].push_back(i);
    }

    Fenwick<Max> fen(n + 1);
    for (int x = n - 1; x >= 0; x--) {
        int res = fen.sum(n + 1).x;

        for (auto i : vec[x]) {
            fen.add(i, {fen.sum(i).x + 1});
        }

        fen.add(0, {res});
    }

    std::cout << n - fen.sum(n + 1).x << "\n";
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}