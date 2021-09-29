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
#define rg register
const int maxn = 1e7 + 5, maxm = 1e3 + 5;
int n, m, cnt, fa[maxn];
char s[maxm][maxm];
int zhao(rg int xx) {
    if (fa[xx] == xx)
        return xx;
    else
        return fa[xx] = zhao(fa[xx]);
}
void work1() {
    fprintf(stderr, "This program is used to generate undirected connected graphs with n nodes, m edges and K weights.\n");
    fprintf(stderr, "The program generates 100 input files by default.\n");
    fprintf(stderr, "For each input file, you must enter three parameters, N, m, and K.\n");
    fprintf(stderr, "Please make sure that 0<=n<=10000000 0<=m<=10000000 m>=n-1.\n");
    fprintf(stderr, "N is the number of nodes in the graph, M is the number of edges in the graph\n");
    fprintf(stderr, "and K is some parameters in the graph. If you do not want to output K.\n");
    fprintf(stderr, "Please delete the code yourself.\n");
    default_random_engine engine(time(NULL));
    srand(time(NULL));
    for (rg int i = 1; i <= 100; i++) {
        rg int cntt[9];
        memset(cntt, 0, sizeof(cntt));
        rg int Num = -1, now = i;
        while (now) {
            cntt[++Num] = now % 10;
            now /= 10;
        }
        s[i][0] = 'd', s[i][1] = 'a', s[i][2] = 't', s[i][3] = 'a';
        for (rg int j = 4; j <= Num + 4; j++) {
            s[i][j] = cntt[Num + 4 - j] + '0';
        }
        s[i][Num + 5] = '.', s[i][Num + 6] = 'i', s[i][Num + 7] = 'n';
    }
    for (rg int kk = 1; kk <= 5; kk++) {
        long long now = 0;
        if (kk >= 2) fprintf(stderr, "Last num:%d is OK\n.", kk - 1);
        fprintf(stderr, "Now the %dth set of data is generated.\n", kk);
        fprintf(stderr, "please enter n m k\n");
        fprintf(stderr, "And then waiting....\n");
        freopen(s[kk], "w", stdout);
        cnt = 0;
        rg int jl = 0, n, m, k;
        n = rand() % 100000 + 1;
        int limit = min(1LL * n * (n - 1) / 2, 100000LL);
        int tmp = limit - (n - 1);
        m = rand() % tmp + 1;
        m = m + (n - 1);
        int s = rand() % n + 1;
        int t1 = rand() % n + 1;
        int t2 = rand() % n + 1;
        fprintf(stderr, "%d %d %d %d %d\n", n, m, s, t1, t2);

        uniform_int_distribution<> dis(1, 0x3f3f3f3f);
        printf("%d %d %d %d %d\n", n, m, s, t1, t2);
        if (m < n - 1) {
            fprintf(stderr, "Wrong!m must be bigger than n-1.\n");
            fprintf(stderr, "The %dth data is not generated.\n", kk);
            continue;
        }
        if (m < 0 || m > 10000000) {
            fprintf(stderr, "Wrong!m is too big or too small.\n");
            fprintf(stderr, "The %dth data is not generated.\n", kk);
            continue;
        }
        if (n < 0 || n > 10000000) {
            fprintf(stderr, "Wrong!n is too big or too small.\n");
            fprintf(stderr, "The %dth data is not generated.\n", kk);
            continue;
        }
        for (rg int i = 1; i <= n; i++) fa[i] = i;
        while (cnt < n - 1) {
            now++;
            if (now >= 10000000000) {
                fprintf(stderr, "Too large to build\n");
                jl = 1;
                break;
            }
            rg int x = dis(engine) % n + 1, y = dis(engine) % n + 1, x1 = zhao(x), y1 = zhao(y), z = 1LL * rand() % 100000 + 1;
            if (x1 != y1) {
                fa[x1] = y1, cnt++;
                printf("%d %d %d\n", x, y, z);
            }
        }
        if (jl) {
            fprintf(stderr, "The %dth data is not generated.\n", kk);
            continue;
        }
        m = m - (n - 1);
        for (rg int i = 1; i <= m; i++) {
            rg int x = dis(engine) % n + 1, y = dis(engine) % n + 1, z = 1LL * rand() * rand() % 10000000 + 1;
            printf("%d %d %d\n", x, y, z);
        }
    }
}

int main() {
    // freopen("data.in", "w", stdout);
    work1();
}