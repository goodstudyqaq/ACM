#include <bits/stdc++.h>

using namespace std;

template <typename a, typename b>
string to_string(pair<a, b> p);

template <typename a, typename b, typename c>
string to_string(tuple<a, b, c> p);

template <typename a, typename b, typename c, typename d>
string to_string(tuple<a, b, c, d> p);

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

template <size_t n>
string to_string(bitset<n> v) {
    string res = "";
    for (size_t i = 0; i < n; i++) {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template <typename a>
string to_string(a v) {
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

template <typename a, typename b>
string to_string(pair<a, b> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename a, typename b, typename c>
string to_string(tuple<a, b, c> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename a, typename b, typename c, typename d>
string to_string(tuple<a, b, c, d> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_out() {
    cerr << endl;
}

template <typename head, typename... tail>
void debug_out(head h, tail... t) {
    cerr << " " << to_string(h);
    debug_out(t...);
}

#ifdef local
#define debug(...) cerr << "[" << #__va_args__ << "]:", debug_out(__va_args__)
#else
#define debug(...) 42
#endif

#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define isprime(x) (((x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))

#define maxn 100      // pre-calc max n for phi(m, n)
#define maxm 100010   // pre-calc max m for phi(m, n)
#define maxp 666666   // max primes counter
#define max 10000010  // max prime
namespace pcf {
long long dp[maxn][maxm];
unsigned int ar[(max >> 6) + 5] = {0};
int len = 0, primes[maxp], counter[max];

void sieve() {
    setbit(ar, 0), setbit(ar, 1);
    for (int i = 3; (i * i) < max; i++, i++) {
        if (!chkbit(ar, i)) {
            int k = i << 1;
            for (int j = (i * i); j < max; j += k) setbit(ar, j);
        }
    }

    for (int i = 1; i < max; i++) {
        counter[i] = counter[i - 1];
        if (isprime(i)) primes[len++] = i, counter[i]++;
    }
}

void init() {
    sieve();
    for (int n = 0; n < maxn; n++) {
        for (int m = 0; m < maxm; m++) {
            if (!n)
                dp[n][m] = m;
            else
                dp[n][m] = dp[n - 1][m] - dp[n - 1][m / primes[n - 1]];
        }
    }
}

long long phi(long long m, int n) {
    if (n == 0) return m;
    if (primes[n - 1] >= m) return 1;
    if (m < maxm && n < maxn) return dp[n][m];
    return phi(m, n - 1) - phi(m / primes[n - 1], n - 1);
}

long long lehmer(long long m) {
    if (m < max) return counter[m];

    long long w, res = 0;
    int i, a, s, c, x, y;
    s = sqrt(0.9 + m), y = c = cbrt(0.9 + m);
    a = counter[y], res = phi(m, a) + a - 1;
    for (i = a; primes[i] <= s; i++) res = res - lehmer(m / primes[i]) + lehmer(primes[i]) - 1;
    return res;
}
}  // namespace pcf

long long solve(long long n) {
    int i, j, k, l;
    long long x, y, res = 0;

    for (i = 0; i < pcf::len; i++) {
        x = pcf::primes[i], y = n / x;
        if ((x * x) > n) break;
        res += (pcf::lehmer(y) - pcf::lehmer(x));
    }

    for (i = 0; i < pcf::len; i++) {
        x = pcf::primes[i];
        if ((x * x * x) > n) break;
        res++;
    }

    return res;
}
int main() {
#ifdef local
    freopen("./data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    pcf::init();
    long long n;
    cin >> n;
    cout << solve(n) << endl;
    return 0;
}