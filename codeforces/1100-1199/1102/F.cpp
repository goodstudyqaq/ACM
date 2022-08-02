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
const int inf = 1e9 + 1;

vector< vector< int > > a;
vector< vector< int > > mi1, mi2;

int n, m;
void init() {
	mi1.resize(n), mi2.resize(n);
	for (int i = 0; i < n; i++) {
		mi1[i].resize(n), mi2[i].resize(n);
		for (int j = 0; j < n; j++) {
			int mi = inf;
			for (int k = 0; k < m; k++) {
				mi = min(mi, abs(a[i][k] - a[j][k]));
			}
			mi1[i][j] = mi;
			mi = inf;
			for (int k = 0; k < m - 1; k++) {
				mi = min(mi, abs(a[j][k] - a[i][k + 1]));
			}
			mi2[i][j] = mi;
		}
	}
}

int cal(int idx) {
	vector< vector< int > > dp(1 << n, vector< int >(n, -1));
	dp[1 << idx][idx] = inf;
	int LIMIT = 1 << n;
	for (int i = 0; i < LIMIT; i++) {
		for (int j = 0; j < n; j++) {

			if (dp[i][j] == -1) continue;
			for (int k = 0; k < n; k++) {
				if ((i >> k) & 1) {
					continue;
				}
				dp[i + (1 << k)][k] = max(dp[i + (1 << k)][k], min(mi1[j][k], dp[i][j]));
			}
		}
	}

	int res = 0;
	for (int i = 0; i < n; i++) {
		res = max(res, min(dp[LIMIT - 1][i], mi2[idx][i]));
	}
	return res;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	a.resize(n);

	for (int i = 0; i < n; i++) {
		a[i].resize(m);
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	init();

	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans = max(ans, cal(i));
	}
	cout << ans << endl;
}