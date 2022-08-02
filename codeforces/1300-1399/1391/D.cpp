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

const int maxn = 1e6 + 5;
const int inf = 0x3f3f3f3f;
string s;
string V[5];

int n, m;
int dp[maxn][10];

bool check(int s1, int s2) {
	vector< int > v1, v2;
	for (int i = 0; i < n; i++) {
		v1.push_back(s1 % 2);
		s1 /= 2;
		v2.push_back(s2 % 2);
		s2 /= 2;
	}

	if (n == 2) {
		return (v1[0] + v1[1] + v2[0] + v2[1]) % 2;
	}
	if (n == 3) {
		return (v1[0] + v1[1] + v2[0] + v2[1]) % 2 && (v1[1] + v1[2] + v2[1] + v2[2]) % 2;
	}
	return false;
}

int work2(int idx, int status) {
	int res = 0;
	for (int i = 0; i < n; i++) {
		int now = V[i + 1][idx - 1] - '0';
		int snow = (status >> i) & 1;
		if (snow != now) {
			res++;
		}
	}
	return res;
}

vector< int > valid[10];
void work() {

	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < (1 << n); j++) {
			if (check(i, j)) {
				valid[i].push_back(j);
			}
		}
	}

	memset(dp, inf, sizeof(dp));
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < (1 << n); j++) {

			int tmp = work2(i, j);

			if (i == 1) {
				dp[i][j] = tmp;
			} else {
				for (auto k : valid[j]) {
					dp[i][j] = min(dp[i][j], dp[i - 1][k] + tmp);
				}
			}
			debug(i, j, dp[i][j]);
		}
	}

	int res = 1e9;
	for (int i = 0; i < (1 << n); i++) {
		res = min(res, dp[m][i]);
	}
	cout << res << endl;
}

int main() {
	freopen("data.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	int flag;
	if (n >= 4 && m >= 4) {
		flag = 0;
	} else {
		if (n < 4) {
			flag = 1;
		} else {
			flag = 2;
		}
	}

	for (int i = 1; i <= n; i++) {
		cin >> s;
		if (flag == 1) {
			V[i] = s;
		} else if (flag == 2) {
			for (int j = 0; j < s.size(); j++) {
				V[j + 1] += s[j];
			}
		}
	}

	if (flag == 0) {
		cout << -1 << endl;
		return 0;
	}

	if (min(n, m) == 1) {
		cout << 0 << endl;
		return 0;
	}

	if (flag == 2) {
		swap(n, m);
	}
	work();
}