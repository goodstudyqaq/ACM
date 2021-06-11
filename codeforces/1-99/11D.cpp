#include <bits/stdc++.h>

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
	return to_string(( string )s);
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

const int maxn = 20;
const int maxm = 1 << 20;
int g[maxn][maxn];
long long dp[maxm + 10][25];

int n, m;
int get_small(int status) {
	for (int i = 0; i < n; i++) {
		if ((status >> i) & 1) return i;
	}
	return -1;
}

int main() {
	scanf("%d %d", &n, &m);
	int u, v;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &u, &v);
		u--;
		v--;
		g[u][v] = g[v][u] = 1;
	}

	for (int i = 0; i < n; i++) {
		dp[1 << i][i] = 1;
	}

	long long res = 0;
	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < n; j++) {
			if (!dp[i][j]) continue;
			int small = get_small(i);

			for (int k = small; k < n; k++) {
				if (g[j][k]) {
					if ((i >> k) & 1) {
						if (k == small) {
							res += dp[i][j];
						}
					} else {
						dp[i + (1 << k)][k] += dp[i][j];
					}
				}
			}
		}
	}
	cout << (res - m) / 2 << endl;
}