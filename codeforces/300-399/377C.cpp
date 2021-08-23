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

vector< int > s;
typedef pair< char, int > action;
vector< action > ac;
vector< vector< int > > dp;

int n;
int m;
int dfs(int status, int d) {
	if (dp[status][d] != -1e9) return dp[status][d];
	if (d == m) {
		int idx = -1;
		for (int i = 1; i <= m; i++) {
			if ((status >> (i - 1)) & 1) continue;
			idx = i;
			break;
		}
		if (ac[d].first == 'b') {
			return dp[status][d] = 0;
		} else {
			return dp[status][d] = s[idx];
		}
	}

	bool f = ac[d].second == ac[d + 1].second;
	// 相等取最大值， 不相等取最小值

	if (ac[d].first == 'b') {
		long long res = -1e8;
		for (int i = 1; i <= m; i++) {
			if ((status >> (i - 1)) & 1) continue;
			long long tmp = dfs(status + (1 << (i - 1)), d + 1);
			if (f) {
				res = max(res, tmp);
			} else {
				res = max(res, -tmp);
			}
		}
		return dp[status][d] = res;
	} else {
		for (int i = 1; i <= m; i++) {
			if ((status >> (i - 1)) & 1) continue;
			long long tmp = dfs(status + (1 << (i - 1)), d + 1);
			long long tmp2 = s[i];
			if (f) {
				return dp[status][d] = tmp2 + tmp;
			} else {
				return dp[status][d] = tmp2 - tmp;
			}
		}
	}
	return 0;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	s.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
	}
	cin >> m;
	ac.resize(m + 1);
	for (int i = 1; i <= m; i++) {
		cin >> ac[i].first >> ac[i].second;
	}

	sort(s.begin() + 1, s.begin() + 1 + n, greater< int >());
	dp.resize(1 << m, vector< int >(m + 1, -1e9));

	int f = 1;
	if (ac[1].second == 2) f = -1;
	cout << f * dfs(0, 1) << endl;

	return 0;
}