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
	int p, l, len;
};
vector< Node > nodes;

vector< vector< int > > go, cost;
vector< int > stk;
vector< int > dp;
int scnt = 0;
int get_idx(int idx) {
	// scnt 不可能等于 0
	int right = nodes[idx].len;
	int l = 0, r = scnt - 1;
	int ans = -1;
	while (l <= r) {
		int mid = l + r >> 1;
		int tmp = stk[mid];
		if (nodes[tmp].p <= right) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	if (ans == -1) return ans;
	ans = stk[ans];
	return ans;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;

	nodes.resize(n + 1);
	go.resize(n + 1, vector< int >(18, 0));
	cost.resize(n + 1, vector< int >(18, 0));
	stk.resize(n + 1);
	dp.resize(n + 1);

	for (int i = 1; i <= n; i++) {
		cin >> nodes[i].p >> nodes[i].l;
		nodes[i].len = nodes[i].p + nodes[i].l;
	}
	go[n][0] = n;
	cost[n][0] = 0;
	stk[scnt++] = n;
	dp[n] = n;

	for (int i = n - 1; i >= 1; i--) {
		int idx = get_idx(i);
		// dp[i] = i 能到的最远的点
		if (idx == -1) {
			dp[i] = i;
			idx = i;
		} else {
			dp[i] = dp[idx];
		}

		if (dp[i] != n) {
			go[i][0] = dp[i] + 1;
			cost[i][0] = nodes[dp[i] + 1].p - max(nodes[idx].len, nodes[i].len);
			cost[i][0] = min(cost[i][0], cost[idx][0]);
		} else {
			go[i][0] = n;
			cost[i][0] = 0;
		}
		debug(i, dp[i], cost[i][0], idx);
		while (scnt > 0 && nodes[i].len >= nodes[stk[scnt - 1]].len) scnt--;
		stk[scnt++] = i;
		// debug(i, dp[i], go[i][0], cost[i][0]);
	}

	for (int j = 1; j < 18; j++) {
		for (int i = 1; i <= n; i++) {
			int to = go[i][j - 1];
			go[i][j] = go[to][j - 1];
			cost[i][j] = cost[i][j - 1] + cost[to][j - 1];
		}
	}

	int q;
	cin >> q;
	while (q--) {
		int x, y;
		cin >> x >> y;
		int res = 0;
		int now = x;
		for (int j = 17; j >= 0; j--) {
			int tmp = go[now][j];
			int tmp2 = dp[tmp];
			if (tmp >= y) {
				continue;
			}
			res += cost[now][j];
			now = tmp;
		}
		// 判断 now 能否直接到
		if (dp[now] < y)
			res += cost[now][0];
		cout << res << '\n';
	}
	return 0;
}