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

template <typename T>
struct RMQ {
    int n = 0, levels = 0;
    vector<T> values;
    vector<vector<int>> range_high;

    RMQ(const vector<T>& _values = {}) {
        if (!_values.empty())
            build(_values);
    }

    static int largest_bit(int x) {
        return 31 - __builtin_clz(x);
    }

    int max_index(int a, int b) const {
        return values[a] > values[b] ? a : b;
    }

    void build(const vector<T>& _values) {
        values = _values;
        n = values.size();
        levels = largest_bit(n) + 1;
        range_high.resize(levels);

        for (int k = 0; k < levels; k++)
            range_high[k].resize(n - (1 << k) + 1);

        for (int i = 0; i < n; i++)
            range_high[0][i] = i;

        for (int k = 1; k < levels; k++)
            for (int i = 0; i <= n - (1 << k); i++)
                range_high[k][i] = max_index(range_high[k - 1][i], range_high[k - 1][i + (1 << (k - 1))]);
    }
    // [a, b)
    int rmq_index(int a, int b) const {
        assert(a < b);
        int level = largest_bit(b - a);
        return max_index(range_high[level][a], range_high[level][b - (1 << level)]);
    }

    T rmq_value(int a, int b) const {
        return values[rmq_index(a, b)];
    }
};

vector<long long> d, c;
vector<long long> diff;
RMQ<long long> diff_max, sum_max, sum_min;

vector<long long> sum;
long long ans;
// [l, r]
void work(int l, int r) {
    if (l == r) {
        ans = max(ans, c[l]);
        return;
    }
    int mid = diff_max.rmq_index(l + 1, r + 1);
    work(l, mid - 1);
    work(mid, r);
    int idx1 = sum_max.rmq_index(mid, r + 1);

    long long tmp;
    if (l == 0) {
        tmp = sum_min.rmq_index(l, mid);
        tmp = sum[tmp];
        if (tmp > 0) tmp = 0;
    } else {
        tmp = sum_min.rmq_index(l - 1, mid);
        tmp = sum[tmp];
    }
    long long tmp2 = sum[idx1] - tmp - diff[mid];
    ans = max(ans, tmp2);
    debug(l, r, ans, sum[idx1], tmp);
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, a;
    cin >> n >> a;
    d.resize(n);
    c.resize(n);
    diff.resize(n);
    sum.resize(n);
    vector<long long> sum2(n);
    sum2.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i] >> c[i];
        c[i] = a - c[i];
        sum[i] = c[i];
        if (i != 0) {
            sum[i] += sum[i - 1];
        }
        sum2[i] = -sum[i];
    }
    for (int i = 1; i < n; i++) {
        diff[i] = 1LL * (d[i] - d[i - 1]) * (d[i] - d[i - 1]);
    }
    diff_max.build(diff);
    sum_max.build(sum);
    sum_min.build(sum2);

    work(0, n - 1);
    cout << ans << endl;
    return 0;
}