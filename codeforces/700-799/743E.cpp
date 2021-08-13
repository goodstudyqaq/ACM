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

vector< int > cnt;
vector< int > a;
vector< vector< int > > nxt;
int ans;

int n;

int run2(int idx, int dir) {
	if (idx == -1) return -1;
	if (nxt[idx][dir] == -1) return -1;
	return nxt[idx][dir] + 1;
}

int run(int idx, int dir, int times) {
	for (int i = 1; i <= times; i++) {
		idx = run2(idx, dir);
		if (idx == -1) return -1;
	}
	return idx;
}

bool check(int c) {
	int LIMIT = 1 << 8;
	vector< vector< int > > dp(LIMIT, vector< int >(9, n + 2));

	dp[0][0] = 1;

	for (int i = 0; i < LIMIT; i++) {
		for (int j = 0; j <= 8; j++) {
			if (dp[i][j] > n) continue;

			for (int k = 1; k <= 8; k++) {
				if ((i >> (k - 1)) & 1) continue;
				int go_s = i + (1 << (k - 1));
				int idx1 = run(dp[i][j], k, c);
				int idx2 = run2(idx1, k);
				if (idx1 != -1 && j + 1 <= 8) {
					dp[go_s][j + 1] = min(dp[go_s][j + 1], idx1);
				}
				if (idx2 != -1) {
					dp[go_s][j] = min(dp[go_s][j], idx2);
				}
			}
		}
	}

	bool flag = false;
	for (int i = 0; i <= 8; i++) {
		if (dp[LIMIT - 1][i] <= n + 1)
			flag = true;
		else
			continue;
		// debug(i, dp[LIMIT - 1][i]);
		ans = max(ans, c * 8 + 8 - i);
	}
	return flag;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	a.resize(n + 1);
	cnt.resize(9, 0);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		cnt[a[i]]++;
	}
	nxt.resize(n + 2, vector< int >(9, -1));
	for (int i = n; i >= 1; i--) {
		for (int j = 1; j <= 8; j++) {
			nxt[i][j] = nxt[i + 1][j];
		}
		nxt[i][a[i]] = i;
	}

	int mi = 125;
	for (int i = 1; i <= 8; i++) {
		mi = min(mi, cnt[i]);
	}
	if (mi == 0) {
		int res = 0;
		for (int i = 1; i <= 8; i++) {
			if (cnt[i] > 0) res++;
		}
		cout << res << endl;
		return 0;
	}

	int l = 1, r = mi;
	while (l <= r) {
		int mid = l + r >> 1;
		if (check(mid)) {
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	cout << ans << endl;
	return 0;
}