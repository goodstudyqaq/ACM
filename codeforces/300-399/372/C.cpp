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

struct Node {
	int a, b, t;
};
const long long inf = 3e11 + 1;

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m, d;
	cin >> n >> m >> d;
	vector< Node > v(m + 1);
	long long sum = 0;

	for (int i = 1; i <= m; i++) {
		cin >> v[i].a >> v[i].b >> v[i].t;
		sum += v[i].b;
	}

	vector< vector< long long > > dp(2, vector< long long >(n + 1, inf));

	for (int i = 1; i <= n; i++) {
		dp[1][i] = abs(v[1].a - i);
		// debug(i, dp[1][i]);
	}

	for (int i = 2; i <= m; i++) {
		int now = i & 1;
		int last = now ^ 1;
		vector< int > q(n + 1);
		int head = 1, tail = 0;

		int cha = v[i].t - v[i - 1].t;
		// fill_n(dp[now].begin(), dp[now].end(), inf);
		for (int i = 1; i <= n; i++) {
			dp[now][i] = inf;
		}

		for (int j = 1; j <= n; j++) {
			while (head <= tail && 1LL * q[head] + 1LL * cha * d < 1LL * j) {
				head++;
			}

			while (head <= tail && dp[last][q[tail]] > dp[last][j]) {
				tail--;
			}
			q[++tail] = j;
			dp[now][j] = min(dp[now][j], dp[last][q[head]] + abs(v[i].a - j));
			// debug(i, j, q[head], dp[now][j]);
		}

		head = 1, tail = 0;
		for (int j = n; j >= 1; j--) {
			while (head <= tail && 1LL * q[head] - 1LL * cha * d > 1LL * j) {
				head++;
			}
			while (head <= tail && dp[last][q[tail]] > dp[last][j]) {
				tail--;
			}
			q[++tail] = j;
			dp[now][j] = min(dp[now][j], dp[last][q[head]] + abs(v[i].a - j));
			// debug(i, j, q[head], dp[now][j], head, tail, q[head]);
		}
		// for (int j = 1; j <= n; j++) {
		// 	debug(i, j, dp[now][j]);
		// }
	}

	long long ans = inf;
	for (int i = 1; i <= n; i++) {
		ans = min(ans, dp[m & 1][i]);
	}
	debug(sum, ans);
	cout << sum - ans << endl;
	return 0;
}